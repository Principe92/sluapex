#include <iostream>
#include <iomanip>
#include <cstdlib> // has exit(), etc.
#include <ctime>
#include "mpi.h" // MPI header file
#define MASTER 0

using namespace std;

int main(int argc, char **argv)
{
    int nprocs, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 4;
    if (argc >= 2)
    {
        n = atoi(argv[1]);
    }

    int A[n][n], B[n][n], C[n][n];
    int Apart[n], Bpart[n], Cpart[n] = {0};

    if (rank == MASTER)
    {
        // fill(A[0], A[0] + n*n, 1);
        // fill(B[0], B[0] + n*n, 1);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = i * n + j;
                B[i][j] = i * n + j;
            }
        }

        cout << "A: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << A[i][j] << " ";
            cout << endl;
        }
        cout << endl;

        cout << "B: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << B[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    MPI_Scatter(&A, n, MPI_INT, &Apart, n, MPI_INT, MASTER, MPI_COMM_WORLD);

    MPI_Bcast(&B, n*n, MPI_INT, MASTER, MPI_COMM_WORLD);

    //fill(Cpart[0], Cpart[0] + n, 0);
    cout << "Processor: " << rank << " has: " << endl;
    for (int i = 0; i < n; i++)
    	cout << Apart[i] << " ";
    cout << endl << endl;

    cout << "Processor: " << rank << " result is: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Cpart[i] += Apart[j] * B[j][i];
        }

	cout << Cpart[i] << " ";
    }
    cout << endl << endl;

    MPI_Gather(&Cpart, n, MPI_INT, &C, n, MPI_INT, MASTER, MPI_COMM_WORLD);

    if (rank == MASTER)
    {
	    cout << "C: " << endl;
	    for (int i = 0; i < n; i++)
	    {
		    for (int j = 0; j < n; j++)
			    cout << C[i][j] << " ";
		    cout << endl;
	    }
	    cout << endl;
    }

    MPI_Finalize();

    return 0;
}
