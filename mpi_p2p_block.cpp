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
        cout << "Hello from process rank " << rank << endl;

        int val = 0;
        if (rank == MASTER) {
                val = 100;
                for (int dest_rank = 1; dest_rank < nprocs; dest_rank++) {
                        MPI_Send(&val, 1, MPI_INT, dest_rank, 0, MPI_COMM_WORLD);
                }
                cout << "Process rank " << rank << " has a value of " << val << endl;
        }
        else {
                MPI_Status status;
                MPI_Recv(&val, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                cout << "Process rank " << rank << " got a value of " << val << endl;
                val = val + rank;
                cout << "Process rank " << rank << " has updated the value to be " << val << endl;
        }

        MPI_Finalize();

}
