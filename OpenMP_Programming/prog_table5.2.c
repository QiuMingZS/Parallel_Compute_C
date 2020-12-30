#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "timer.h"

int main(int argc, char* argv[]){
    int thread_count = strtol(argv[1], NULL, 10);
    double tmp;
    int n = 20000;
    double a[20000];
    for (int j=0; j<n; j++){
        a[j] = 1 - j/20000.0;
    }
    int i, phase;
    double start, finish, elapsed;
    GET_TIME(start);
#   pragma omp parallel num_threads(thread_count) \
        default(none) shared(a, n) private(i, tmp, phase)
    for (phase = 0; phase < n; phase++){
        if (phase % 2 == 0)
#           pragma omp for
            for (i=1; i<n; i+=2){
                if (a[i-1] > a[i]){
                    tmp = a[i-1];
                    a[i-1] = a[i];
                    a[i] = tmp;
                }
            }
        else
#           pragma omp for
            for (i=1; i<n-1; i+=2){
                if (a[i] > a[i+1]){
                    tmp = a[i+1];
                    a[i+1] = a[i];
                    a[i] = tmp;
                }
            }
            
    }
    GET_TIME(finish);
    elapsed = finish - start;
    printf("Time takes %lf seconds\n", elapsed);
    return 0;
}

