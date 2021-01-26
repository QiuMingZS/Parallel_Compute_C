#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
pthread_mutex_t mutex;

int n = 100000;
int flag = 0;
double sum= 0;

void* get_sum(void* rank);

int main(int argc, char* argv[]){
    long        thread;                 /* use long in case of 64-bit system */
    pthread_t*  thread_handles;

    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc(thread_count*sizeof(pthread_t));

    /* mutex initialize */
    pthread_mutex_init(&mutex, NULL);

    /* fork threads */
    for (thread=0; thread<thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, get_sum, (void*) thread);
    }

    /* This will be executed by the main thread */
    printf("The estimated value of pi is: %f\n", 4*sum);

    /* join threads */
    for (thread=0; thread<thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    /* mutex destroy */
    pthread_mutex_destroy(&mutex);

    /* free useless resources */
    free(thread_handles);
    return 0;
}   /* main */

void* get_sum(void* rank){
    long my_rank = (long) rank;
    double factor;
    double local_sum = 0.0;
    long long i;
    long long local_n = n/thread_count;
    long long local_first_i = local_n*my_rank;
    long long local_last_i = local_first_i + local_n;

    if (local_first_i % 2 == 0){
        factor = 1.0;
    } else {
        factor = -1.0;
    }

    for (i=local_first_i; i<local_last_i; i++){
        local_sum += factor/(2*i + 1);
        factor = - factor;
    }

    /* critical section protected by mutex lock */
    pthread_mutex_lock(&mutex);
    sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL; 
}   /* get_sum */
