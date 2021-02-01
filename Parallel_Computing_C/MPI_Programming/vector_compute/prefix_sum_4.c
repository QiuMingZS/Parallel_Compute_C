/* ******************************************************************
Using MPI_Scan to get the prefix sums

Wang Guanzheng, 2020.12.20 07:37
****************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void get_input(int* num, int* local_num, double* vector, int comm_sz, int my_rank, MPI_Comm comm);
void local_prefix(double* vector, int* num);

int main(void){
	int	comm_sz;
	int my_rank;
    int* num = NULL;
    int* local_num = NULL;
    double* vector = NULL;
    double* result = NULL;
    double* local_vector = NULL;
    double temp;

    MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm comm = MPI_COMM_WORLD;

    local_num = malloc(sizeof(int));
    num = malloc(sizeof(int));
    
    if (my_rank == 0){
        vector = malloc(num[0]*sizeof(double));
        result = malloc(num[0]*sizeof(double));
    }
    
    get_input(num, local_num, vector, comm_sz, my_rank, comm);
    MPI_Bcast(local_num, 1, MPI_INT, 0, comm);
    MPI_Bcast(num, 1, MPI_INT, 0, comm);
    local_vector = malloc(local_num[0]*sizeof(double));
    MPI_Scatter(vector, local_num[0], MPI_DOUBLE, local_vector, local_num[0], MPI_DOUBLE, 0, comm);
    local_prefix(local_vector , local_num);
    MPI_Scan(&local_vector[local_num[0]-1], &temp, 1, MPI_DOUBLE, MPI_SUM, comm);
    temp -= local_vector[local_num[0]-1];
    for (int i=0; i<local_num[0]; i++){
        local_vector[i] += temp;
    }
    MPI_Gather(local_vector, local_num[0], MPI_DOUBLE, result, local_num[0], MPI_DOUBLE, 0, comm);

    
    if (my_rank == 0){
        printf("The result is: \n");
        for (int i=0; i<num[0]; i++){
            printf("%f ", result[i]);
        }
        printf("\n");
    }
    

	MPI_Finalize();
	return 0;
}




void get_input(int* num, int* local_num, double* vector, int comm_sz, int my_rank, MPI_Comm comm){
    if (my_rank == 0){
        printf("Please input the number of the vector(divisable by comm_sz): \n");
        scanf("%d", num);
        local_num[0] = num[0] / comm_sz;
        printf("Please input the vector: \n");
        for (int i=0; i<num[0]; i++){
            scanf("%lf", &vector[i]);
        }
    }
}

void local_prefix(double* vector, int* num){
    for (int i=1; i<num[0]; i++){
        vector[i] += vector[i-1];
    }
}
