/******************************************************************************
* FILE: mpi_p2p_block_integ.cpp
* DESCRIPTION:
*   Integration with MPI Blocking Communications
* AUTHOR: Tae-Hyuk (Ted) Ahn
* LAST REVISED: 02/20/2020
******************************************************************************/
#include <iostream>
#include <math.h>
#include <mpi.h>
#define MASTER 0

void other_work(int rank);
float integral(float ai, float h, int n);

using namespace std;

int main(int argc, char **argv)
{
  int nprocs, rank, tag, n;
  float pi, a, b, h, ai, my_integral, integral_sum;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  pi = acos(-1.0);  /* = 3.14159... */
  a = 0.;           /* lower limit of integration */
  b = pi*1./2.;     /* upper limit of integration */
  n = 500;          /* number of increment within each process */
  tag = 123;        /* set the tag to identify this particular job */
  h = (b-a)/n/nprocs;    /* length of increment */

  ai = a + rank*n*h;  /* lower limit of integration for partition rank */
  my_integral = integral(ai, h, n);    /* 0<=rank<=p-1 */

  cout << "Process " << rank << " has the partial result of " << my_integral << endl;

  // Type code to be done

	if (rank == MASTER){

		integral_sum = my_integral;
		
		for (int i = 1; i < nprocs; i++) {
			MPI_Recv(&my_integral, 1, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			integral_sum += my_integral;
		}

		cout << "Total integral = " << integral_sum << endl;
	} else {
		MPI_Send(&my_integral, 1, MPI_FLOAT, MASTER, tag, MPI_COMM_WORLD);
	}

  MPI_Finalize();
}

void other_work(int rank)
{
  cout << "More work on process " << rank << endl;
}

float integral(float ai, float h, int n)
{
  int j;
  float aij, integ;

  integ = 0.0;               /* initialize */
  for (j=0; j<n; j++) {      /* sum integrals */
    aij = ai + (j+0.5)*h;    /* mid-point */
    integ += cos(aij)*h;
  }
  return integ;
}

