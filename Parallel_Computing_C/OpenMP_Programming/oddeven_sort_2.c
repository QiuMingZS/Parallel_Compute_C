#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]){
    int thread_count = strtol(argv[1], NULL, 10);
    double tmp;
    int n = 10;
    double a[10];
    printf("Please input 10 numbers for sorting...\n");
    for (int i=0; i<10; i++){
        scanf("%lf", &a[i]);
    }
    
    int i, phase;
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
    for (int i=0; i<10; i++){
        printf("%lf ", a[i]);
    }
    printf("\n");
    return 0;
}

