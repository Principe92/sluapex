import time
from numba import jit
from mpi4py import MPI

@jit
def loop(num_steps, begin, end):
    step = 1.0/num_steps
    sum = 0
    for i in range(begin, end):
        x = (i + 0.5) * step
        sum = sum + 4.0/(1.0 + x*x)
    return sum

def Pi(num_steps):
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    begin = time.time()
    num_steps_chunk = num_steps/size
    local_sum = loop(num_steps, rank*num_steps_chunk, (rank+1)*num_steps_chunk)
    sum = comm.reduce(local_sum, op=MPI.SUM, root=0) 
    end = time.time()

    if rank == 0:
        pi = sum/num_steps
        elapsed = end-begin
        print("Pi with %d steps is %f in %f secs" %(num_steps, pi, elapsed))


if __name__ == '__main__':
    Pi(1000000000)

