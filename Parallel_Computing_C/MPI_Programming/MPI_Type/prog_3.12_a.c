/* ******************************************************************
RING

mpicc -g -Wall -o prog_3.12_a prog_3.12_a.c
mpiexec -n 16 ./prog_3.12_a

Wang Guanzheng, 2020.12.18 11：33
****************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "timer.h"


const int MAX_CONTRIB = 20;
int Global_Sum_Rp(int x, int my_rank, int comm_sz, MPI_Comm comm);
int Global_Sum_Bf(int x, int my_rank, int comm_sz, MPI_Comm comm);

int main(void){
	int	comm_sz;
	int my_rank;
    double start, finish, elapsed, t;

	MPI_Init(NULL, NULL);
    MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_size(comm, &comm_sz);
	MPI_Comm_rank(comm, &my_rank);

    // srandom(my_rank);
    // int x = random() / MAX_CONTRIB;
    int x = my_rank;
    int sum;
    int* value;
    value = malloc(comm_sz*sizeof(int));
    MPI_Gather(&x, 1, MPI_INT, value, 1, MPI_INT, 0, comm); 

    if (my_rank == 0){
        printf("The original values: \n");
        for (int i=0; i<comm_sz; i++){
            printf("%d ", value[i]);
        }
        printf("\n");
    }
    MPI_Barrier(comm);
    GET_TIME(start);
    sum = Global_Sum_Rp(x, my_rank, comm_sz, comm);
    GET_TIME(finish);
    elapsed = finish - start;
    MPI_Reduce(&elapsed, &t, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
    if (my_rank == 0){
        printf("The RP sum is %d and takes %.15e seconds. \n", sum, t);
    }

    MPI_Barrier(comm);
    GET_TIME(start);
    sum = Global_Sum_Bf(x, my_rank, comm_sz, comm);
    GET_TIME(finish);
    elapsed = finish - start;
    MPI_Reduce(&elapsed, &t, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
    if (my_rank == 0){
        printf("The BF sum is %d and takes %.15e seconds. \n", sum, t);
    }
    free(value);

	MPI_Finalize();
}


int Global_Sum_Rp(int x, int my_rank, int comm_sz, MPI_Comm comm){
    int sum = x;
    int temp;
    for (int i=1; i<comm_sz; i++){
        MPI_Sendrecv(&x, 1, MPI_INT, (my_rank+1)%comm_sz, 0, &temp, 
                    1, MPI_INT, (my_rank + comm_sz -1)%comm_sz, 0, comm, MPI_STATUS_IGNORE);
        x = temp;
        sum += x;
    }
    return sum;
}

int Global_Sum_Bf(int x, int my_rank, int comm_sz, MPI_Comm comm){
    int temp, sum = x;
    int partner;
    unsigned mask = 1;

    while(mask < comm_sz){
        partner = my_rank ^ mask;
        MPI_Sendrecv(&sum, 1, MPI_INT, partner, 0,
                     &temp, 1, MPI_INT, partner, 0, 
                     comm, MPI_STATUS_IGNORE);
        sum += temp;
        mask <<= 1;
    }
    return sum;
}



