//Hossein Alishah
//Comp 620 - Fall 2021
//Project 1. Design and implementation a parallel search algorithm using MPI
// to compile the project use following command line:
//mpicc project1-MPI.c
//and for running:
//mpirun -np 2 ./a.out


#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv){
    int n=500;
    
    //impleneting a sample array with the n size
    int arr[n], b[n];
    for(int i=0;i<n;i++)
        {
            arr[i]=i+1;
        }
    //element to search
    int key=333;
  
    //initialize MPI environment
    MPI_Init(&argc, &argv);
    int rank,size;
    //Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Get the ranks processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    MPI_Scatter(&arr,n/2,MPI_INT,&b,n/2,MPI_INT,0,MPI_COMM_WORLD);
   
    if(rank==0)
        {
            double start=MPI_Wtime();
            int index1 = 0;
            for(int i=0; i<n/2; i++){
                if(b[i]==key){
                    index1 = i;
                }
            }
            //printing elements of array
            if (index1 != 0){
                printf("\nthe key is %d\n",key);
                printf("\nthe size of array is %d\n\n",n);
                printf("\nNumber found on processor:  %d\t on the position:  %d\n\n",rank,index1);
                printf("Array is\n");
               for( int i =0; i<n; i++){
                   printf("%d ",arr[i]);
                   printf(",");}
            }
            double end=MPI_Wtime();
            printf("\nExecution time of Processor %d is %f\n\n", rank, (end-start)*1000);
            }
    else if(rank==1)
        {
            double start=MPI_Wtime();
            int index = 0;
            for(int i=0; i<n/2; i++){
                if(b[i]==key){
                    index = i+n/2;}
            }
            //printing elements of array
           if (index != 0){
               printf("\nthe key is %d\n",key);
               printf("\nthe size of array is %d\n\n",n);
               printf("\nNumber found on processor:  %d\t on the position:  %d\n\n",rank,index);
                printf("Array is\n");
               for( int i =0; i<n; i++){
                   printf("%d ",arr[i]);
                   printf(",");
               }
                printf("\n\n");
            }
            
            double end=MPI_Wtime();
            printf("\nExecution time of Processor %d is %f\n\n", rank, (end-start)*1000);
        }
    }

