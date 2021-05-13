# include <iostream>
# include <cstdlib>	// has exit(), etc.
# include <ctime>
# include "mpi.h"	// MPI header file

using namespace std;

int main (int argc, char **argv)
{
    int nprocs, rank;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
}