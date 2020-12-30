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
        scanf("%lf ", a[i]);
    }
    
    
    for (int phase = 0; phase < n; phase++){
        if (phase % 2 == 0)
#           pragma omp parallel for num_threads(thread_count) \
                default(none) shared(a, n) private(i, tnp)
            for (int i=1; i<n; i+=2){
                if (a[i-1] > a[i]){
                    tmp = a[i-1];
                    a[i-1] = a[i];
                    a[i] = tmp;
                }
            }
            else
#           pragma omp parallel for num_threads(thread_count) \
                default(none) shared(a, n) private(i, tnp)
            for (int i=1; i<n-1; i+=2){
                if (a[i] > a[i+1]){
                    tmp = a[i+1];
                    a[i+1] = a[i];
                    a[i] = tmp;
                }
            }
            
    }

    return 0;
}

