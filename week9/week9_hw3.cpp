#include <iostream>
#include <cstdlib>     // has exit(), etc.
#include <ctime>
#include <mpi.h>
#define MASTER 0

using namespace std;

int main(int argc, char **argv)
{
	// Just simply set N(4) X M(4) matrix and M(4) X 1 vector
	int N=4, M=4; 
	int A[N][M], Apart[M], B[M], X[N]; 
	int Xpart = 0, root=0;
	int nprocs, rank;

	// MPI init
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Initialize matrix
	if (rank == MASTER) {
		int val = 1;
		int rem = 0;
		int i,j;

		for (i = 0; i < M; i++) {
			B[i] = i + 1;

			for (j = 0; j < N; j++) {
				A[i][j] = val++;
			}
		}
	} 

	// MPI Scatter the A Matrix

	MPI_Scatter(&A, N, MPI_INT, &Apart, N, MPI_INT, MASTER, MPI_COMM_WORLD);

	// Broadcast the B vector

	MPI_Bcast(&B, M, MPI_INT, MASTER, MPI_COMM_WORLD);

	// Calculate Xpart

	for (int i = 0; i < N; i++) {
		Xpart += Apart[i] * B[i];
	}

	// MPI Gather

	MPI_Gather(&Xpart, 1, MPI_INT, &X, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

	// Print results

	if (rank == MASTER) {
		for(int i=0; i<N; i++) {
			cout << "X[" << i << "]=" << X[i] << endl;
		} 
	}   

	MPI_Finalize();  // MPI finalize

	return 0;     // Exit 

}
