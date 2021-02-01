import numpy as np
import sys
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

integral = np.zeros(1)
receive_buff = np.zeros(1)

# get parameters from command-line
start = float(sys.argv[1])
end = float(sys.argv[2])
piece = int(sys.argv[3])


# objective function
def f(x):
    return x**2


# integral calculate in a small range
def integrate_range(start, end, piece):
    integral = -(f(start) + f(end))/2.0
    for x in np.linspace(start, end, piece + 1):
        integral += f(x)
    integral = integral * (end - start)/piece
    return integral


# divide the integral into pieces for processes
width = (end - start) / piece
local_piece = piece/size        # pieces of a process
local_start = start + rank*local_piece*width
local_end = local_start + local_piece*width

integral[0] = integrate_range(local_start, local_end, local_piece)

# process 0 collects all results and sum
comm.Reduce(integral, receive_buff, op=MPI.SUM, root=0)

if rank == 0:
    print('With %d pieces, the estimation the integral of function y = x^2 from x = %f to x = %f is: %f.'
          % (piece, start, end, receive_buff))






