from mpi4py import MPI
import numpy

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

vector_length = 20

# get the data using root process(here, we set 0)
input_vector1 = numpy.linspace(0, 23, vector_length) if comm.rank == 0 else None
input_vector2 = numpy.linspace(4, 34, vector_length) if comm.rank == 0 else None

# initialization
dot_result = numpy.array([0.])
local_number = numpy.array([0.])

# test for compatibility
if rank == 0:
    if vector_length % size != 0:
        print('The vector can not be evenly divided to all processes!')
        comm.Abort()
    local_number = numpy.array([vector_length/size])

comm.Bcast(local_number, root=0)

# initialize vectors to do local dot product
local_input1 = numpy.zeros(int(local_number))
local_input2 = numpy.zeros(int(local_number))

# divide up vectors
comm.Scatter(input_vector1, local_input1, root=0)
comm.Scatter(input_vector2, local_input2, root=0)

# compute on each process
local_dot_result = numpy.array([numpy.dot(local_input1, local_input2)])

comm.Reduce(local_dot_result, dot_result, op=MPI.SUM)

if rank == 0:
    print('The dot product is: ', dot_result[0], ', computed in parallel.')




