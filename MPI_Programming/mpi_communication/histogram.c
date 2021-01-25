/* ***********************************************************************
In terminal, run: 
mpicc -g -Wall -o hist histogram.c 
mpiexec -n 4 ./hist
*********************************************************************** */
#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void){
	double local_data[5];
	int temp_data[5];
	int local_bin[5] = {0,0,0,0,0};
	int	comm_sz;
	int my_rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0){
		double data[20] = {1.3, 2.9, 0.4, 0.3, 1.3,
					   	   4.4, 1.7, 0.4, 3.2, 0.3,
						   4.9, 2.4, 3.1, 4.4, 3.9,
						   0.4, 4.2, 4.5, 4.9, 0.9};
		for (int i=1; i<4; i++){
			MPI_Send(&data[i*5], 5, MPI_DOUBLE, i, my_rank, MPI_COMM_WORLD);
		}
		for (int i=0; i<5; i++){
			local_data[i] = data[i];
		}
	} else {
		MPI_Recv(local_data, 5, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	for (int i=0; i<5; i++){
		if (local_data[i] <= 1){
			local_bin[0] += 1;
		} else if (local_data[i] <= 2){
			local_bin[1] += 1;
		} else if (local_data[i] <= 3){
			local_bin[2] += 1;
		} else if (local_data[i] <= 4){
			local_bin[3] += 1;
		} else{
			local_bin[4] += 1;
		}

	}
	
	if (my_rank%2 != 0){
		MPI_Send(local_bin, 5, MPI_INT, my_rank-1, my_rank, MPI_COMM_WORLD);
	} else {
		MPI_Recv(temp_data, 5, MPI_INT, my_rank+1, my_rank+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for (int i=0; i<5; i++){
			local_bin[i] += temp_data[i];
		}
		if (my_rank/2%2 != 0){
			MPI_Send(local_bin, 5, MPI_INT, my_rank-2, my_rank, MPI_COMM_WORLD);
		} else {
			MPI_Recv(temp_data, 5, MPI_INT, my_rank+2, my_rank+2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for (int i=0; i<5; i++){
				local_bin[i] += temp_data[i];
			}

			// Plot the Histgram
			printf("Histgram: \n");
			for (int i=0; i<5; i++){
				printf("%d|-------------\n", i);
				printf(" |");
				for (int j=0; j<local_bin[i]; j++){
					printf("#");
				}
				printf("\n");
			}
			printf("5|-------------\n");
		}
	}

	MPI_Finalize();
	return 0;
}
