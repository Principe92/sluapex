#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
using namespace std;

void merge(int *array, int leftIndex, int middleIndex, int rightIndex);
void mergesort(int *array, int leftIndex, int rightIndex);
void get_numbers(int *array, int n);
void printArray(int *array, int size);

int main(int argc, char *argv[])
{
    // Get size of array
    int array_size = 0;
    double start, end;

    while (true)
    {
        cout << "Please enter size of array to sort: ";
        cin >> array_size;

        if (array_size > 0)
        {
            break;
        }
    }

    omp_sched_t kind;
	int chunk_size;

	omp_get_schedule(&kind, &chunk_size);
    int num_procs = omp_get_num_procs();
	int num_threads = omp_get_max_threads();

    cout << "Number of processors available = " << num_procs << "\n";
    cout << "Number of threads =              " << num_threads << "\n\n";

    int *array = new int[array_size];

    get_numbers(array, array_size);

    cout << "Given array is: \n";
    //printArray(array, array_size);

    start = omp_get_wtime();
    mergesort(array, 0, array_size - 1);
    end = omp_get_wtime();

    cout << "\nSorted array is: \n";
    //printArray(array, array_size);

    cout << "  " << setw(8) << "N"
		<< "  " << setw(18) << "Number of processor"
		<< "  " << setw(18) << "Number of threads"
		<< "  " << setw(18) << "Chunk size"
		<< "  " << setw(30) << "Elapsed wall clock time (sec)"
		<< "\n";

	cout << "  " << setw(8) << array_size
		<< "  " << setw(18) << num_procs
		<< "  " << setw(18) << num_threads
		<< "  " << setw(18) << chunk_size
		<< "  " << setw(30) << end - start << "\n";

    return 0;
}

void merge(int *array, int leftIndex, int middleIndex, int rightIndex)
{
    int leftArraySize = middleIndex - leftIndex + 1;
    int rightArraySize = rightIndex - middleIndex;

    int *left = new int[leftArraySize];
    int *right = new int[rightArraySize];

    for (int i = 0; i < leftArraySize; i++)
    {
        left[i] = array[leftIndex + i];
    }

    for (int j = 0; j < rightArraySize; j++)
    {
        right[j] = array[middleIndex + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = leftIndex;

    while (i < leftArraySize && j < rightArraySize)
    {
        if (left[i] <= right[j])
        {
            array[k] = left[i];
            i++;
        }
        else
        {
            array[k] = right[j];
            j++;
        }

        k++;
    }

    while (i < leftArraySize)
    {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < rightArraySize)
    {
        array[k] = right[j];
        j++;
        k++;
    }

    delete[] left;
    delete[] right;
}

void mergesort(int array[], int leftIndex, int rightIndex)
{
    if (leftIndex >= rightIndex)
    {
        return;
    }

    int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

#pragma omp parallel sections
    {
#pragma omp section
        {
            mergesort(array, leftIndex, middleIndex);
        }

#pragma omp section
        {
            mergesort(array, middleIndex + 1, rightIndex);
        }
    }

    merge(array, leftIndex, middleIndex, rightIndex);
}

void get_numbers(int nums[], int n)
{
    /* initialize random seed: */
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        int num = rand() % 100 + 1;
        nums[i] = num;
    }
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";

    cout << endl;
}
