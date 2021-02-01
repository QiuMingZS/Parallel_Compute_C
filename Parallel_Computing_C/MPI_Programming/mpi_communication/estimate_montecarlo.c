#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(void){

	int	comm_sz;
	int my_rank;
	long long int exp_time;
	long long int exp_time_master;
	long long int exp_time_others;
	long long int local_count = 0;
	long long int total_count = 0;
	double x;
	double y;
	double PI;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		exp_time = 1000000000;
		exp_time_others = exp_time / comm_sz;
		exp_time_master = exp_time_others + exp_time % comm_sz;
	} 
	MPI_Bcast(&exp_time_others, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
	if (my_rank == 0){
		exp_time_others = exp_time_master;
	}
	srand(my_rank);
	for (long long int i=0; i<exp_time_others; i++){
		x = (double) rand()/RAND_MAX;
		y = (double) rand()/RAND_MAX;
		if (x*x + y*y < 1){
			local_count += 1;
		}
	}
	MPI_Reduce(&local_count, &total_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	if (my_rank == 0){
		PI = (double) 4 * total_count / exp_time;
		printf("PI: %0.9f\n", PI);
	}	
	MPI_Finalize();
	return 0;
}
