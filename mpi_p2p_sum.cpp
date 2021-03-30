#include <iostream>
#include <cstdlib>
#include <ctime>
#include <mpi.h>
#define MASTER 0

using namespace std;

int main(int argc, char **argv)
{
	int N = 1000;
	int nprocs, rank , tag=0;
	int tmp_sum = 0, partial_sum = 0, total_sum = 0;
	int startval = 0, endval = 0;

	// MPI iNIT
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Work
	startval = N*rank/nprocs + 1;
	endval = N*(rank+1)/nprocs;

	// Need to modify based on number of processors
	for (int i=startval; i <= endval; i++)
	{
		partial_sum += i;
	}

	// Collect partial sum from each worker
	if (rank == MASTER)
	{
		total_sum = partial_sum; // master should have it's own partial sum
		for (int worker_rank = 1; worker_rank < nprocs; worker_rank++)
		{
			MPI_Status status;
			MPI_Recv(&partial_sum, 1, MPI_INT, worker_rank, tag, MPI_COMM_WORLD, &status);
			total_sum += partial_sum; // master should add each partial sum from workers
		}

		cout << "The sum from 1 to " << N << " is: " << total_sum << endl;
	}
	
	else
	{
		MPI_Send(&partial_sum, 1, MPI_INT, MASTER, tag, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
