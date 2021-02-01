## introduction
Take a look at the mpi_trap related files:
 - mpi_trap_origin.c:
 calculate the integration of specified function

 - mpi_trap_p2p.c:
 Based on the origin file, this file adds the time record function, using point-to-point communication

 - mpi_trap_reduce.c
 Different with mpi_trap_p2p.c, this file uses MPI_Reduce to calculate the sum

 The three files above can help you to know about the time comsumption of defferent algrithms.
