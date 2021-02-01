# point to point communication
# using 2 process to show

from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

tr_buff = np.zeros(1)   # to store data to transfer or receive

if rank == 0:
    tr_buff[0] = 1
    print('Process %d: I\'ll send number %d to Process 1' % (rank, tr_buff[0]))
    comm.Send(tr_buff, dest=1)

if rank == 1:
    comm.Recv(tr_buff, source=0)
    print('Process %d: I\'ve received %d from Process 0' % (rank, tr_buff[0]))
