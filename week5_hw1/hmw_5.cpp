#include <iostream>
#include <math.h>
#include <iomanip>
#include <omp.h>

using namespace std;

double calc_pi(int rectangles) {

    double sum = 0;
    double h = 2.0 / rectangles;
    double x = 0;
    int i = 0;

    //#pragma omp parallel for reduction(+:sum) schedule(static) private(i, x)
    #pragma omp parallel for schedule(static) private(i, x)

    for (i=0; i<rectangles; i++) 
    {
        x = -1 + (i+0.5)*h;

        #pragma omp atomic
        sum += sqrt(1 - x*x)*h;
    }

    double pi = sum*2.0;

    return pi;
}

int main(int argc, char *argv[]) 
{
    double start, end;
    int n = 500000000;

    int num_threads = omp_get_max_threads();

    start = omp_get_wtime();  // start time check
    double pi = calc_pi(n);
    end = omp_get_wtime();    // end time check

    cout << "  " << setw(8) << "n"
	     << "  " << setw(18) << "threads"
         << "  " << setw(18) << "Pi"
         << "  " << setw(30) << "time" << "\n";

    cout << "  " << setw(8) << n
	     << "  " << setw(18) << num_threads
         << "  " << setw(18) << pi
         << "  " << setw(30) << end-start << "\n";
}
