#include <iostream>
#include <iomanip>
#include <cstdlib> // has exit(), etc.
#include <ctime>
#include "mpi.h" // MPI header file
#include <time.h>
#define MASTER 0

using namespace std;

int main(int argc, char **argv)
{
    int nprocs, rank;
    double stime, etime;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == MASTER)
        stime = MPI_Wtime(); // start time

    int n = 4;
    if (argc >= 2)
    {
        n = atoi(argv[1]);
    }

    int rows = 1;

    if (n > nprocs)
    {
        rows = (n / nprocs) + 1;
    }

    int A[n][n], B[n][n], C[n][n];
    int Apart[rows][n], Cpart[rows][n] = {0};

    if (rank == MASTER)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = 1;
                B[i][j] = 1;
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

    MPI_Scatter(&A, rows * n, MPI_INT, &Apart, rows * n, MPI_INT, MASTER, MPI_COMM_WORLD);

    MPI_Bcast(&B, n * n, MPI_INT, MASTER, MPI_COMM_WORLD);

    for (int k = 0; k < rows; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Cpart[k][i] += Apart[k][j] * B[j][i];
            }
        }
    }

    MPI_Gather(&Cpart, rows * n, MPI_INT, &C, rows * n, MPI_INT, MASTER, MPI_COMM_WORLD);

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

        etime = MPI_Wtime(); // end time
        cout << "  " << setw(10) << "N"
             << "  " << setw(10) << "nprocs"
             << "  " << setw(30) << "elapsed wall-clock time"
             << "\n";
        cout << "  " << setw(10) << n
             << "  " << setw(10) << nprocs
             << "  " << setw(30) << etime - stime << "\n";
    }

    MPI_Finalize();

    return 0;
}
