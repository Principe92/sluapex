#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void merge(int array[], int leftIndex, int middleIndex, int rightIndex);
void mergesort(int array[], int leftIndex, int rightIndex);
void get_numbers(int array[], int n);
void printArray(int array[], int size);

int main(int argc, char *argv[])
{
    // Get size of array
    int array_size = 0;

    while (true)
    {
        cout << "Please enter size of array to sort: ";
        cin >> array_size;

        if (array_size > 0)
        {
            break;
        }
    }

    int array[array_size];

    get_numbers(array, array_size);

    cout << "Given array is: \n";
    printArray(array, array_size);

    mergesort(array, 0, array_size - 1);

    cout << "\nSorted array is: \n";
    printArray(array, array_size);

    return 0;
}

void merge(int array[], int leftIndex, int middleIndex, int rightIndex)
{
    int leftArraySize = middleIndex - leftIndex + 1;
    int rightArraySize = rightIndex - middleIndex;

    int left[leftArraySize], right[rightArraySize];

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
}

void mergesort(int array[], int leftIndex, int rightIndex)
{
    if (leftIndex >= rightIndex)
    {
        return;
    }

    int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
    mergesort(array, leftIndex, middleIndex);
    mergesort(array, middleIndex + 1, rightIndex);
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
