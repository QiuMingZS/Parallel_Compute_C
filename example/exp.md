reduce
```bash
running-mars@runningmars-P7xxTM1:~/Parallel_Compute_C/example$ mpicc -g -Wall -o trap mpi_trap1.c 
running-mars@runningmars-P7xxTM1:~/Parallel_Compute_C/example$ mpiexec -n 16  ./trap
Enter a, b, and n
0 1 100000000
With n = 100000000 trapezoids, our estimate
of the integral from 0.000000 to 1.000000 = 3.333333333333338e-01
MPI_Reduce time: 1.025999881676398e-05
```

```bash
running-mars@runningmars-P7xxTM1:~/Parallel_Compute_C/example$ mpicc -g -Wall -o trap mpi_trap2.c 
running-mars@runningmars-P7xxTM1:~/Parallel_Compute_C/example$ mpiexec -n 16  ./trap
Enter a, b, and n
0 1 100000000
With n = 100000000 trapezoids, our estimate
of the integral from 0.000000 to 1.000000 = 3.333333333333338e-01
MPI_Reduce time: 1.607715699901746e-02
```