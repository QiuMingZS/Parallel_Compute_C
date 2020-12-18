/* ******************************************************************
MPI_Type_index

mpicc -g -Wall -o prog_3.19 prog_3.19.c
mpiexec -n 2 ./prog_3.19

Wang Guanzheng, 2020.12.18 07:37
****************************************************************** */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

void Build_indexed_type(int n, MPI_Datatype* indexed_mpi_t_p);

int main(void){
	int	comm_sz;
	int my_rank;

	MPI_Init(NULL, NULL);
    MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_size(comm, &comm_sz);
	MPI_Comm_rank(comm, &my_rank);

    int n;
    double *loc_mat;
    MPI_Datatype indexed_mpi_t;

    if (my_rank == 0){
        printf("Please input the order of the matrix: \n");
        scanf("%d", &n);  
    }  
    MPI_Bcast(&n, 1, MPI_INT, 0, comm);
    loc_mat = malloc(n*n*sizeof(double));
    Build_indexed_type(n, &indexed_mpi_t);
    if (my_rank == 0){
        printf("Please input the data of the matrix: \n");
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                scanf("%lf", &loc_mat[i*n + j]);
            }
        }
        MPI_Send(loc_mat, 1, indexed_mpi_t, 1, 0, comm);

    }else{
        memset(loc_mat, 0, n*n*sizeof(double));
        MPI_Recv(loc_mat, 1, indexed_mpi_t, 0, 0, comm, MPI_STATUS_IGNORE);
        printf("The upper triangular part: \n");
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                printf("%f ", loc_mat[i*n + j]);
            }
            printf("\n");
        }
    }
	MPI_Finalize();
	return 0;
}


void Build_indexed_type(int n, MPI_Datatype* indexed_mpi_t_p){
    int i;
    int* array_of_block_lens;
    int* array_of_disps;

    array_of_block_lens = malloc(n*sizeof(int));
    array_of_disps = malloc(n*sizeof(int));

    for (int i=0; i<n; i++){
        array_of_block_lens[i] = n-i;
        array_of_disps[i] = i*(n+1);
    }

    MPI_Type_indexed(n, array_of_block_lens, array_of_disps, MPI_DOUBLE, indexed_mpi_t_p);
    MPI_Type_commit(indexed_mpi_t_p);

    free(array_of_block_lens);
    free(array_of_disps);
}