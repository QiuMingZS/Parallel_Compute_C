#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;

void* Hello(void* rank);

int main(int argc, char* argv[]){
    long        thread;         // use long in case of 64-bit system
    pthread_t*  thread_handles;

    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc(thread_count*sizeof(pthread_t));

    // fork threads
    for (thread=0; thread<thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread);
    }

    // This will be executed by the main thread
    printf("Hello from main thread.\n");

    // join threads
    for (thread=0; thread<thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    // free useless resources
    free(thread_handles);
    return 0;
}   /* main */

void* Hello(void* rank){
    long my_rank = (long) rank;
    printf("Hello from thread %ld of %d.\n", my_rank, thread_count);
    return NULL;
}

