#include <iostream>
#include <iomanip>
#include <mpi.h>
#include <time.h>
#include <cmath>
#define MASTER 0
#define SEED 35791246

using namespace std;

int main(int argc, char **argv)
{
	int nprocs, rank, npoints, circle_count=0, num, val;
	double x, y, pi, stime, etime;

	// MPI Init and rank
	MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == MASTER)
		stime = MPI_Wtime(); // start time

	// Get number of points
	npoints = 10000000;
	if (argc >= 2)
		npoints = atoi(argv[1]);

	// Calculate number of points for each rank
	num = npoints/nprocs;
	int rem = npoints % nprocs;

	if (rem != 0 && rank == MASTER){
		num += rem; // Master will take the remainder
	}
	// You should consider npoints is not divided nprocs
	
	srand( (unsigned)time( NULL ) );
	
	for (int i=0; i<num; i++) {
		x = (2 * ((double) rand()/RAND_MAX)) - 1.0;
		y = (2 * ((double) rand()/RAND_MAX)) - 1.0;

		bool in_circle = (pow(x, 2) + pow(y, 2)) <= 1.0;

		if (in_circle) {
			circle_count++;
		}
	}

		

	// Random numbers and count the points of inside of the circle
	srand(SEED+rank);   // Give rand() a seed value
	// Your code

	if (rank == MASTER) // I am MASTER
	{
		// Your code
		MPI_Status status;
		val = 0;

		for (int i=1; i<nprocs; i++){
			MPI_Recv(&val, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			circle_count += val;
		}
		
		pi = 4.0 * circle_count/npoints;

		etime = MPI_Wtime(); // end time
		cout << "  " << setw(10) << "npoints"
			<< "  " << setw(10) << "pi"
			<< "  " << setw(10) << "nprocs"
			<< "  " << setw(30) << "elapsed wall-clock time" << "\n";
		cout << "  " << setw(10) << npoints
			<< "  " << setw(10) << pi
			<< "  " << setw(10) << nprocs
			<< "  " << setw(30) << etime-stime << "\n";
	}
	else  // I am WORKER
	{
		MPI_Send(&circle_count, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
	}
	// MPI finalize
	MPI_Finalize();
}
