//Hossein alishah
// Comp 620- Fall 2021
// to run this multiplication we need 8 free slots on processor,
//so, each processor calculate on row of the final matrix
// to compile on mac use the following command line:
//mpicc matrix.c
// to run on mac use the following command line:
//mpirun -np 8 ./a.out
//mpirun --oversubscribe -np 8 ./a.out


#define N 8
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stddef.h>
#include "mpi.h"


void print_matrix(char *prompt, int arr[N][N], int r, int s);

int main(int argc, char *argv[])
{
    int i, j, k, rank, size, tag = 99, blksz, sum = 0;
    // 8 by 8 matrix
    int a[N][N]= {{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8}, {1,2,3,4,5,6,7,8}, {1,2,3,4,5,6,7,8}, {1,2,3,4,5,6,7,8}};
    // 8 by 8 matrix
    int b[N][N]= {{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8}, {1,2,3,4,5,6,7,8}, {1,2,3,4,5,6,7,8}, {1,2,3,4,5,6,7,8}};
    // the matrix that will have the results of the multiplication
    int c[N][N];
    // scatter send a copy of matrrix a to aa
    int aa[N],cc[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //scatter rows of first matrix to different processes
    MPI_Scatter(a, N*N/size, MPI_INT, aa, N*N/size, MPI_INT,0,MPI_COMM_WORLD);

    //broadcast second matrix to all processes
    MPI_Bcast(b, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    //perform vector multiplication by all processes
    for (i = 0; i < N; i++)
        {
                for (j = 0; j < N; j++)
                {
                        sum = sum + aa[j] * b[j][i];  //MISTAKE_WAS_HERE
                }
                cc[i] = sum;
                sum = 0;
            }
    
    //we are gather all process to the process with the rank=0, so to access the
    //result of multiplication, we need to just get the c[][] from ran=0
    MPI_Gather(cc, N*N/size, MPI_INT, c, N*N/size, MPI_INT, 0, MPI_COMM_WORLD);
    

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    
    //because of gattering all calculation on C on processor rank=0,
    //we print only C from processor rank=0
    if (rank == 0)
        print_matrix("C = ", c, rank, size);

}

// this function print all elements of a N by N matrix
void print_matrix(char *prompt, int arr[N][N], int r, int s)
{
    int i, j;

    printf ("\n\n%s\n", prompt);
    for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                    printf(" %d", arr[i][j]);
            }
            printf ("\n");
    }
    printf ("\n\n");
    printf("processor rank is  %d\n", r);
    printf("processor size is  %d\n", s);
    printf ("\n\n");
}

