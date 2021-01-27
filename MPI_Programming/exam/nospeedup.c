/* ******************************************************************
File name: nospeedup.c
Author: Guanzheng Wang
Last Modified: 2020.01.26 15:58

Instructions: 
    compile: gcc -g -Wall -o nospeedup.o nospeedup.c
    execute: ./nospeedup.o

others:
    matrix rank: from 1024 to 4096
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

    while(matrix_rank <= 4096){
        x = malloc(matrix_rank*matrix_rank*sizeof(double));
        A = malloc(matrix_rank*matrix_rank*sizeof(double));
        y = malloc(matrix_rank*matrix_rank*sizeof(double));
        for (int i=0; i<matrix_rank*matrix_rank; i++){
            A[i] = 1;
            x[i] = 2;
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
    for (int i=0; i<matrix_rank; i++){
        for (int j=0; j<matrix_rank; j++){
            y[i*matrix_rank + j] = 0.0;
            for (int k = 0; k < matrix_rank; k++){
                y[i*matrix_rank + j] += x[i*matrix_rank+k]*y[j + i*matrix_rank];
            }
            
        }
    }
}