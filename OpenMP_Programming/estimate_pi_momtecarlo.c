#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void estimate(int n, long long int* total_count);

int main(int argc, char* argv[]){
    int thread_count = strtol(argv[1], NULL, 10);
    long long int total_num = 900000;
    long long int total_count = 0;
    double PI;
    double x, y;
#   pragma omp parallel for num_threads(thread_count) \
        reduction(+:total_count)
    for (long long int i=0; i<total_num; i++){
		x = (double) rand()/RAND_MAX;
		y = (double) rand()/RAND_MAX;
		if (x*x + y*y < 1){
			total_count += 1;
		}
	}
    PI = 4 * (double) total_count / total_num;
    printf("PI estimated: %lf\n", PI);
    return 0;
}
