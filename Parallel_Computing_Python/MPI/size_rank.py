from mpi4py import MPI
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

if rank == 0:
    print('I\'m process %d, and there are %d process total.' % (rank, size))
else:
    print('Ok, I\'m process %d' % rank)
