#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "timer.h"

double f(int i);

int main(int argc, char* argv[]){
    int thread_count = strtol(argv[1], NULL, 10);
    int total_num = 500000;
    double sum = 0;
    double start, finish, elapsed;
    GET_TIME(start);
#   pragma omp parallel for num_threads(thread_count) \
        reduction(+:sum) schedule(runtime)
    for (int i=0; i<total_num; i++){
		sum += f(i);
    }
    GET_TIME(finish);
    elapsed = finish - start;
    printf("Time elapsed: %lf seconds. \n", elapsed);
    return 0;
}


double f(int i){
    int j;
    int start = i*(i+1)/2;
    int finish = start + i;
    double return_val = 0.0;

    for (j=start; j<=finish; j++){
        return_val += j + 0.001;
    }
    return return_val;
}
