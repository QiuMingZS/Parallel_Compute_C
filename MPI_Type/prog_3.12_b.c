/* ******************************************************************
RING

mpicc -g -Wall -o prog_3.12_b prog_3.12_b.c
mpiexec -n 16 ./prog_3.12_b

Wang Guanzheng, 2020.12.18 20:21
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
    int* global_sum;
    value = malloc(comm_sz*sizeof(int));
    global_sum = malloc(comm_sz*sizeof(int));
    MPI_Gather(&x, 1, MPI_INT, value, 1, MPI_INT, 0, comm); 

    if (my_rank == 0){
        printf("The original values: \n");
        for (int i=0; i<comm_sz; i++){
            printf("%d ", value[i]);
        }
        printf("\n");
    }
    sum = Global_Sum_Rp(x, my_rank, comm_sz, comm);
    MPI_Gather(&sum, 1, MPI_INT, global_sum, 1, MPI_INT, 0, comm);
    if (my_rank == 0){
        printf("The Prefix Sum is: \n");
        for (int i=0; i<comm_sz; i++){
            printf("%d ", global_sum[i]);
        }
        printf("\n");
    }
    free(value);

	MPI_Finalize();
}


int Global_Sum_Rp(int x, int my_rank, int comm_sz, MPI_Comm comm){
    int sum = x;

    int source = (my_rank + comm_sz - 1)%comm_sz;
    int dest = (my_rank + 1)%comm_sz;
    for (int i=1; i<comm_sz; i++){
        if (i > dest) x = 0;
        MPI_Sendrecv_replace(&x, 1, MPI_INT, dest, 0, source, 0, comm, MPI_STATUS_IGNORE);
        sum += x;
    }
    return sum;
}



