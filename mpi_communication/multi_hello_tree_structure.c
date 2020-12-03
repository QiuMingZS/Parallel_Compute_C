#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void){
	char greeting[MAX_STRING];
	int	comm_sz;
	int my_rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank % 2 == 1) {
        sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, my_rank-1, my_rank, MPI_COMM_WORLD);
    } else {
        if (my_rank == 0) {
            sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
            printf("%s\n", greeting);
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, my_rank+1, my_rank+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
            for (int i=0; i<2; i++) {
                MPI_Recv(greeting, MAX_STRING, MPI_CHAR, my_rank+2, my_rank+2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("%s\n", greeting);
            }
        } else {
            sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
		    MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, my_rank-2, my_rank, MPI_COMM_WORLD);
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, my_rank+1, my_rank+1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        	MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, my_rank-2, my_rank, MPI_COMM_WORLD);
        }
    }

	MPI_Finalize();
	return 0;
}
