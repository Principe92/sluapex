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
    int nprocs, rank, m, circle_count = 0, chunk_size, val;
    double x, y, pi, stime, etime;

    double n[] = {1e6, 5e6, 1e7, 5e7};

    // MPI Init and rank
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == MASTER)
        stime = MPI_Wtime(); // start time

    // Get number of points
    m = 100;
    if (argc >= 2)
        m = atoi(argv[1]);

    int result_list[m];
    double iteration_list[m] = {0};
    int results[nprocs - 1][m] = {{0}};

    srand(SEED + rank); // Give rand() a seed value

    if (rank == MASTER)
    {
        // Generate iteration list
        for (int i = 0; i < m; i++)
        {
            iteration_list[i] = n[(rand() % 4)];
        }

        // Send the list to the other processors
        for (int i = 1; i < nprocs; i++)
        {
            MPI_Send(&iteration_list, m, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
        }
    }
    else
    {
        // Wait for iteration list
        MPI_Status status;
        MPI_Recv(&iteration_list, m, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }

    // Run each iteration
    for (int m_index = 0; m_index < m; m_index++)
    {
        circle_count = 0;

        double niter = iteration_list[m_index];

        // Calculate number of points for each rank
        chunk_size = niter / nprocs;
        int rem = chunk_size % nprocs;

        if (rem != 0 && rank == MASTER)
        {
            chunk_size += rem; // Master will take the remainder
        }

        srand((unsigned)time(NULL));

        for (int i = 0; i < chunk_size; i++)
        {
            x = (2 * ((double)rand() / RAND_MAX)) - 1.0;
            y = (2 * ((double)rand() / RAND_MAX)) - 1.0;

            bool in_circle = (pow(x, 2) + pow(y, 2)) <= 1.0;

            if (in_circle)
            {
                circle_count++;
            }
        }

        result_list[m_index] = circle_count;
    }

    if (rank == MASTER) // I am MASTER
    {
        // Your code
        MPI_Status status;
        val = 0;

        for (int i = 1; i < nprocs; i++)
        {
            int rank_index = i - 1;
            MPI_Recv(&results[rank_index], m, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            // Add to master result
            for (int j = 0; j < m; j++)
            {
                result_list[j] += results[rank_index][j];
            }
        }

        // Calculate pi
        for (int i = 0; i < m; i++)
        {
            pi += (4.0 * result_list[i] / iteration_list[i])/m;
        }

        etime = MPI_Wtime(); // end time
        cout << "  " << setw(10) << "m"
             << "  " << setw(10) << "pi"
             << "  " << setw(10) << "nprocs"
             << "  " << setw(30) << "elapsed wall-clock time"
             << "\n";
        cout << "  " << setw(10) << m
             << "  " << setw(10) << pi
             << "  " << setw(10) << nprocs
             << "  " << setw(30) << etime - stime << "\n";
    }
    else // I am WORKER
    {
        MPI_Send(&result_list, m, MPI_INT, 0, rank, MPI_COMM_WORLD);
    }
    // MPI finalize
    MPI_Finalize();
}
