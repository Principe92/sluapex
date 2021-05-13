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
    int nprocs, rank, m, circle_count = 0, chunk_size;
    double x, y, pi, stime, etime, val;

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

    double iteration_list[m] = {0};

    srand(SEED + rank); // Give rand() a seed value

    int offset;
    int itr_chunk = m / nprocs;
    int itr_rem = itr_chunk % nprocs;

    int itr = itr_chunk;
    if (itr_rem != 0 && rank == MASTER)
    {
        itr += itr_rem; // Master will take the remainder of iterations
    }

    double result_list[itr];
    double results[nprocs - 1][itr] = {{0}};

    if (rank == MASTER)
    {
        // Generate iteration list
        for (int i = 0; i < m; i++)
        {
            iteration_list[i] = n[(rand() % 4)];
        }

        // Send the iteration lists to the other processors
        for (int i = 1; i < nprocs; i++)
        {
            offset = i * itr_chunk;

            if (itr_rem != 0)
            {
                offset += itr_rem; // Master will handle from 0 -> itr_chunk + itr_rem
            }

            MPI_Send(&iteration_list[offset], itr_chunk, MPI_DOUBLE, i, i, MPI_COMM_WORLD);
        }
    }
    else
    {
        // Wait for iteration list
        MPI_Status status;
        MPI_Recv(&iteration_list, itr_chunk, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    }

    // Run each iteration
    for (int m_index = 0; m_index < itr; m_index++)
    {
        circle_count = 0;

        chunk_size = iteration_list[m_index];

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

        // Calculate pi
        pi = (4.0 * circle_count / chunk_size);

        result_list[m_index] = pi;
    }

    if (rank == MASTER) // I am MASTER
    {
        // Your code
        MPI_Status status;
        val = 0;

        for (int i = 1; i < nprocs; i++)
        {
            int rank_index = i - 1;
            MPI_Recv(&results[rank_index], (itr-itr_rem), MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            for (int j = 0; j < (itr-itr_rem); j++)
            {
                val += results[rank_index][j];
            }
        }

        // Include master
        for (int i = 0; i < itr; i++)
        {
            val += result_list[i] / m;
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
        MPI_Send(&result_list, itr, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
    }
    // MPI finalize
    MPI_Finalize();
}
