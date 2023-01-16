//Hossein Alishah
//Comp 620 - Fall 2021
//projecr 2: Design and implementation of a parallel sort algorithm using OpenMP


#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

void mergesort_parallel(int a[],int i,int j);
void merge_sorted(int a[], int p, int q, int r);
void mergesort_serial(int a[],int i,int j);

int main()
{
    printf("Enter the size of the data to be sorted (the maximum value is 100000, enter 0 to end) : ");
    int *a, num, i;
    scanf("%d",&num);

    a = (int *)malloc(sizeof(int) * num);
    
    for (i = 0; i < num; i++) {
        a[i] = rand() % 1000 + 1;
    }
        
    double start_time = omp_get_wtime();
    mergesort_parallel(a,0,num-1);
    double end_time = omp_get_wtime();
    double time_used = end_time - start_time;
    printf("\nParallel time: %f s\n\n\n", time_used);
    
    double start_time1 = omp_get_wtime();
    mergesort_serial(a,0,num-1);
    double end_time1 = omp_get_wtime();
    double time_used1 = end_time1 - start_time1;
    printf("\nSerial time: %f s\n\n\n", time_used1);
    
    printf("\nSorted array :\n");
    for(i=0;i<num;i++)
         printf("%d ",a[i]);
        
    return 0;
}
 
void mergesort_parallel(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        
        #pragma omp parallel sections
        {

            #pragma omp section
            {
                mergesort_parallel(a,i,mid);        //left recursion
            }

            #pragma omp section
            {
                mergesort_parallel(a,mid+1,j);    //right recursion
            }
        }

       // merge(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
        merge_sorted(a,i, mid, j);
    }
    
}

void mergesort_serial(int a[],int i,int j)
{
    int mid;

    if(i<j)
    {
        mid=(i+j)/2;
        mergesort_serial(a,i,mid);        //left recursion
        mergesort_serial(a,mid+1,j);    //right recursion
        merge_sorted(a,i, mid, j);   //merging of two sorted sub-arrays
    }
}
 

// Merge two subarrays L and M into arr
void merge_sorted(int a[], int p, int q, int r) {

  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = a[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = a[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      a[k] = L[i];
      i++;
    } else {
      a[k] = M[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    a[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    a[k] = M[j];
    j++;
    k++;
  }
}
