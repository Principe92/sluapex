#include <iostream>
#include <mpi.h>
#define MASTER 0
#define LEN_VAL 100

using namespace std;

int main(int argc, char **argv)
{
        int nprocs, rank;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        cout << "Hello from process rank " << rank << endl;

        int val[LEN_VAL] = {0};
	int chunk_size = LEN_VAL / nprocs;
	int offset = 0;

        if (rank == MASTER) {
		for (int i=0; i < LEN_VAL; i++)
			val[i] = i+1; // Stores numbers 1 to 100 in the array

		// For each process, sends value of array from offset + chunk_size
                for (int dest_rank = 1; dest_rank < nprocs; dest_rank++) {
			offset = dest_rank * chunk_size;
                        MPI_Send(&val[offset], chunk_size, MPI_INT, dest_rank, 0, MPI_COMM_WORLD);
                }
		
		for (int i=0; i<chunk_size; i++)
			cout << val[i] << " ";

		cout << endl;
        }
        else {
                MPI_Status status;
                MPI_Recv(&val, chunk_size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                cout << "Process rank " << rank << " has a value: ";

		for (int i=0; i <chunk_size; i++)
			cout << val[i] << " ";
		
		cout << endl;
        }

        MPI_Finalize();

}
