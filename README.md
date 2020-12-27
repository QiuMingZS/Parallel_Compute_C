# Parallel_Compute_C
using C  language to write parallel program

## Before Parallel Learning
Parallel Computing is based on Serial Computing. Before your start, some programing fundation is needed.

Here, we provide some code of C language, to help you start.

## About parallel programming 
In general, the parallel computing can be divided into kinds: distributed and shared memory. 
In distributed memory programming, we usually use MPI to write which has many functions of communication. While in shared memory programming, we usually use OpenMP. Different from MPI, OpenMP does not create many processes, it focks many threads. The threads can access the same memory, thus communication functions like send and receive are not neede in OpenMP.

In this project, these two type codes are seperated as you can see.

# Serial C program, compile and run like this:
```bash
gcc -o hello  hello_world.c
./hello
```

# Parallel C program with mpi, compile and run like this:
```bash
mpicc -g -Wall -o multi_hello multi_hello.c 
mpiexec -n 4 ./multi_hello
```