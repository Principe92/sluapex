#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <omp.h>
#include <algorithm>
#define RUN_MODE 0

using namespace std;

	template <size_t nt>
void sqrt_matrix(int mode, double (&a)[nt][nt], double (&b)[nt][nt], double (&c)[nt][nt], int size)
{

	int i, j, k;

	#pragma omp parallel for collapse(3) private(i,j,k)
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			for (k = 0; k < size; k++)
			{
				#pragma omp atomic
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}


int main(int argc, char *argv[])
{
	int mode, num_procs, num_threads, n;
	double start, end;
	omp_sched_t kind;
	int chunk_size;

	omp_get_schedule(&kind, &chunk_size);
	num_procs = omp_get_num_procs();
	num_threads = omp_get_max_threads();

	string schedule;

	switch(kind)
	{
		case omp_sched_static:
			schedule = "static";
			break;
		case omp_sched_dynamic:
			schedule = "dynamic";
			break;
		case omp_sched_guided:
			schedule = "guided";
			break;
		case omp_sched_auto:
			schedule = "auto";
			break;
		default:
			schedule = "other";
			break;
	}

	cout << "  Number of processors available = " << num_procs << "\n";
	cout << "  Number of threads =              " << num_threads << "\n\n";

	// Get mode from the user
	while (true)
	{
		cout << "Please enter mode: (run: 0, validation: 1): ";
		cin >> mode;

		if (mode == 1 || mode == 0)
		{
			break;
		}
	}

	if (mode == RUN_MODE)
	{
		n = 1000;
		static double a[1000][1000];
		static double b[1000][1000];
		static double c[1000][1000];

		fill(a[0], a[0] + n*n, 1.0);
		fill(b[0], b[0] + n*n, 1.0);
		fill(c[0], c[0] + n*n, 0);

		start = omp_get_wtime();

		sqrt_matrix(mode, a, b, c, n);

		end = omp_get_wtime();
	}
	else
	{
		n = 5;
		double a[5][5];
		double b[5][5];
		double c[5][5];

		fill(a[0], a[0] + n*n, 2.0);
		fill(b[0], b[0] + n*n, 3.0);
		fill(c[0], c[0] + n*n, 0);

		start = omp_get_wtime();

		sqrt_matrix(mode, a, b, c, n);

		end = omp_get_wtime();

		cout << "\nC: \n";
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << c[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}

	cout << "  " << setw(8) << "N"
		<< "  " << setw(18) << "Number of processor"
		<< "  " << setw(18) << "Number of threads"
		<< "  " << setw(18) << "Schedule"
		<< "  " << setw(18) << "Chunk size"
		<< "  " << setw(30) << "Elapsed wall clock time (sec)"
		<< "\n";

	cout << "  " << setw(8) << n
		<< "  " << setw(18) << num_procs
		<< "  " << setw(18) << num_threads
		<< "  " << setw(18) << schedule
		<< "  " << setw(18) << chunk_size
		<< "  " << setw(30) << end - start << "\n";
}
