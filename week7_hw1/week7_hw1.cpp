#include <iostream>
#include <iomanip>
#include <mpi.h>
#include <time.h>
#define MASTER 0

using namespace std;

int main(int argc, char **argv)
{
	int nprocs, rank, npoints, chunk_size;
	double dot, partial_dotprod = 0;
	double stime, etime;

	// MPI Init and rank
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == MASTER)
		stime = MPI_Wtime(); // start time

	// Get number of points
	npoints = 500000000;
	if (argc >= 2)
		npoints = atoi(argv[1]);

	chunk_size = npoints / nprocs;
	int rem = npoints % nprocs;

	if (rem != 0 && rank == MASTER)
	{
		chunk_size += rem; // Master will take the remainder
	}

	double x[chunk_size];
	double y[chunk_size];

	for (int i = 0; i < chunk_size; i++)
	{
		x[i] = 1.0;
		y[i] = 1.0;
	}

	for (int i = 0; i < chunk_size; i++)
	{
		partial_dotprod += x[i] * y[i];
	}

	if (rank == MASTER) // I am MASTER
	{
		// Your code
		MPI_Status status;
		double val = 0;

		for (int i = 1; i < nprocs; i++)
		{
			MPI_Recv(&val, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			dot += val;
		}

		dot += partial_dotprod;

		etime = MPI_Wtime(); // end time
		cout << "  " << setw(10) << "N"
			<< "  " << setw(10) << "dot product"
			<< "  " << setw(10) << "nproc"
			<< "  " << setw(30) << "elapsed wall-clock time"
			<< "\n";
		cout << "  " << setw(10) << npoints
			<< "  " << setw(10) << dot
			<< "  " << setw(10) << nprocs
			<< "  " << setw(30) << etime - stime << "\n";
	}
	else // I am WORKER
	{
		MPI_Send(&partial_dotprod, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}

