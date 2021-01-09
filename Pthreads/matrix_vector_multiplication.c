#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;

// Data input
int row_num = 4;
int column_num = 8;
double A[4][8] = {{1, 2, 3, 4, 1, 2, 3, 4}, {5, 6, 7, 8, 5, 6, 7, 8}, {9, 10, 11, 12, 9, 10, 11, 12}, {13, 14, 15, 16, 13, 14, 15, 16}};
double x[8] = {1, 1, 1, 1, 1, 1, 1, 1};
double y[8];

void* matrix_vector_multiply(void* rank);

int main(int argc, char* argv[]){
    long        thread;         // use long in case of 64-bit system
    pthread_t*  thread_handles;

    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc(thread_count*sizeof(pthread_t));


    // fork threads
    for (thread=0; thread<thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, matrix_vector_multiply, (void*) thread);
    }

    // This will be executed by the main thread
    printf("The result of A*x is: \n");
    for (int i=0; i<row_num; i++){
        printf("%f\t", y[i]);
    }
    printf("\n");

    // join threads
    for (thread=0; thread<thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    // free useless resources
    free(thread_handles);
    return 0;
}   /* main */

void* matrix_vector_multiply(void* rank){
    long my_rank =(long) rank;
    int i, j;
    int local_row_num = row_num/thread_count;
    int lcoal_first_row = my_rank*local_row_num;
    int local_last_row =(my_rank+1)*local_row_num - 1;

    for (i=lcoal_first_row; i<=local_last_row; i++){
        y[i] = 0.0;
        for (j=0; j<column_num; j++){
            y[i] += A[i][j]*x[j];
        }
    }
    return NULL;
}   /* matrix_vector_multiply */
