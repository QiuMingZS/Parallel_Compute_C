/* ******************************************************************
speedup.c

comm_sz: from 1 to 16
matrix rank: from 1024 to 16384
****************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "timer.h"
void matmul(double* A, double* x, double* y, double* local_A, double* local_y, int matrix_rank, int comm_sz, MPI_Comm comm);

int main(void){
	int	comm_sz;
	int my_rank;
    int matrix_rank = 1024;

    // Matrix Multiplication Calculation
    double* A = NULL;
    double* x = NULL;
    double* y = NULL;
    double* local_A = NULL;
    double* local_y = NULL;

    // Time Spending
    double local_start, local_finish, local_elapsed, elapsed;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm comm = MPI_COMM_WORLD;

    while(matrix_rank <= 16384){
        x = malloc(matrix_rank*sizeof(double));
        if (my_rank == 0){
            A = malloc(matrix_rank*matrix_rank*sizeof(double));
            y = malloc(matrix_rank*sizeof(double));
            for (int i=0; i<matrix_rank*matrix_rank; i++){
                A[i] = 1;
                if (i % matrix_rank == 0){
                    x[i/matrix_rank] = 1;
                }
            }
        }
        MPI_Barrier(comm);
        GET_TIME(local_start);
        matmul(A, x, y, local_A, local_y, matrix_rank, comm_sz, comm);
        GET_TIME(local_finish);
        local_elapsed = local_finish - local_start; // seconds
        MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
        if (my_rank == 0){
            printf("Matrix rank: %d\tTime: %.15e seconds\n", matrix_rank, elapsed);
        }
        
        free(A);
        free(x);
        free(y);
        matrix_rank = matrix_rank * 2;
    }

	MPI_Finalize();
	return 0;
}

void matmul(
        double* A, 
        double* x, 
        double* y, 
        double* local_A, 
        double* local_y,
        int matrix_rank,
        int comm_sz,
        MPI_Comm comm){
    int local_row = matrix_rank / comm_sz;
    double temp = 0.0;
    int local_row_count = 0;
    local_A = malloc(matrix_rank*local_row*sizeof(double));
    local_y = malloc(local_row*sizeof(double));
    MPI_Scatter(A, matrix_rank*local_row, MPI_DOUBLE, local_A, matrix_rank*local_row, MPI_DOUBLE, 0, comm);
    MPI_Bcast(x, matrix_rank, MPI_DOUBLE, 0, comm);
    for (int i=0; i<matrix_rank*local_row; i++){
        temp += local_A[i] * x[i%matrix_rank];
        if ((i+1)%matrix_rank == 0){
            local_y[local_row_count] = temp;
            temp = 0.0;
            local_row_count += 1;
        }
    } 
    MPI_Gather(local_y, local_row, MPI_DOUBLE, y, local_row, MPI_DOUBLE, 0, comm);
    free(local_A);
    free(local_y);
}