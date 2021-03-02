#include <iostream>
#include <mpi.h>
#define MASTER 0

using namespace std;

int main(int argc, char **argv)
{
	int nprocs, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	cout << "Hello from process " << rank << endl;
	
	if (rank == MASTER)
		cout << "MASTER: number of total processes is: " << nprocs << endl;
	
	MPI_Finalize();
}
