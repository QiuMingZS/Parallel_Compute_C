/* ******************************************************************
speedup.c

comm_sz: from 1 to 16
matrix rank: from 1024 to 16384
****************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
void matmul(double* A, double* x, double* y, int matrix_rank);

int main(void){
    int matrix_rank = 1024;

    // Matrix Multiplication Calculation
    double* A = NULL;
    double* x = NULL;
    double* y = NULL;

    // Time Spending
    double start, finish, elapsed;

    while(matrix_rank <= 16384){
        x = malloc(matrix_rank*sizeof(double));
        A = malloc(matrix_rank*matrix_rank*sizeof(double));
        y = malloc(matrix_rank*sizeof(double));
        for (int i=0; i<matrix_rank*matrix_rank; i++){
            A[i] = 1;
            if (i % matrix_rank == 0){
                x[i/matrix_rank] = 1;
            }
        }
        GET_TIME(start);
        matmul(A, x, y, matrix_rank);
        GET_TIME(finish);
        elapsed = finish - start; // seconds
        printf("Matrix rank: %d\tTime: %.15e seconds\n", matrix_rank, elapsed);
        matrix_rank = matrix_rank * 2;
    }
	return 0;
}

void matmul(
        double* A, 
        double* x, 
        double* y, 
        int matrix_rank){
    double temp = 0.0;
    int row_count = 0;
    for (int i=0; i<matrix_rank*matrix_rank; i++){
        temp += A[i] * x[i%matrix_rank];
        if ((i+1)%matrix_rank == 0){
            y[row_count] = temp;
            temp = 0.0;
            row_count += 1;
        }
    }
}