#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void estimate(int n, long long int* total_count);

int main(int argc, char* argv[]){
    int thread_count = strtol(argv[1], NULL, 10);
    long long int total_num = 9000000000000000000;
    long long int local_num = total_num / thread_count;
    long long int total_count = 0;
    double PI;
#   pragma omp parallel num_threads(thread_count)
    estimate(local_num, &total_count);

    PI = (double) total_count / total_num;
    printf("PI estimated: %lf\n", PI);
    return 0;
}


void estimate(int n, long long int* total_count){
    int my_rank = omp_get_thread_num();
    int local_count;
    double x, y;
    srand(my_rank);
	for (long long int i=0; i<n; i++){
		x = (double) rand()/RAND_MAX;
		y = (double) rand()/RAND_MAX;
		if (x*x + y*y < 1){
			local_count += 1;
		}
	}
#   pragma omp critical
    *total_count += local_count;
}