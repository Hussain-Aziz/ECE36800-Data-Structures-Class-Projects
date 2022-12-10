// Please add your name below
// Name: Hussain Aziz Saif

// FILE: sort.cpp
// Implementation of sorting functions.

#include "sort.h"
#include <cstdlib>
using namespace std;

static
void swap(string & s1, string & s2)
{
	string temp;
	temp = s1;
	s1 = s2;
	s2 = temp;
}

//////////////// Bubble Sort ////////////////////////////
void bubblesort(string data[ ], size_t n)
{
	size_t k = 0;
	bool switched = true;
	while (k < n-1 && switched) 
	{
		switched = false;
		k++;
		for (size_t i = 0; i < n-k; ++i) 
		{
			if (data[i] > data[i+1]) 
			{ 
				swap(data[i], data[i+1]);
				switched = true;
			}
		}
	}
}

//////////////// Selection Sort /////////////////////////
void selectionsort(string data[], size_t n)
{
	for(size_t i = 0; i < n; i++)
	{
		size_t smallest_data = i;
		for(size_t j = i; j < n; j++)
		{
			if (data[j] < data[smallest_data])
			{
				smallest_data = j;
			}
		}

		if (smallest_data != i)
		{
			swap(data[i], data[smallest_data]);
		}
	}
}

//////////////// Insertion Sort /////////////////////////
void insertionsort(string data[], size_t n)
{
	for(size_t i = 1; i < n; i++)
	{
		size_t j = i;
		while(j > 0)
		{
			if (data[j] > data[j - 1]) break;
			
			swap(data[j], data[j-1]);
			j--;
		}
	}
}

//////////////// Shell Sort ////////////////////////////
static
void InsertionSortInterleaved(string data[], int n, int gap_value, int gap);

void shellsort(string data[], size_t n)
{
    for (size_t gap = n / 2; gap > 0; gap /= 2)
    {
        for (size_t i = 0; i < gap; ++i)
        {
            InsertionSortInterleaved(data, n, i, gap);
        }
    }
}
static
void InsertionSortInterleaved(string data[], int n, int gap_value, int gap)
{
    for (int i = gap_value; i < n; i += gap)
    {
        int j = i;
        while (j - gap >= 0)
        {
            if (data[j] > data[j - gap]) break;

            swap(data[j], data[j - gap]);
            j -= gap;
        }
    }
}

////////////////// Quick Sort ///////////////////////////
static
size_t partition(string data[], size_t n);

void quicksort(string data[], size_t n)
{
    if (n > 0)
    {
        size_t pivot_index; // Array index for the pivot element
        size_t n1;          // Number of elements before the pivot element
        size_t n2;          // Number of elements after the pivot element

        // Partition the array, and set the pivot index
        pivot_index = partition(data, n);

        // compute the sizes of the subarrays
        n1 = pivot_index + 1;
        n2 = n - n1;

        // Recursive calls to sort the subarrays
        quicksort(data, pivot_index);
        quicksort((data + n1), n2);
    }
}

static
size_t partition(string data[], size_t n)
{
    //only the necessary array is passed, so midpoint is size/2
    string pivot = data[n / 2];
    int i = 0;
    int j = n;

    while (true)
    {
        while (data[i] < pivot) i++;
        while (data[j] > pivot) j--;

        if (i >= j)
        {
            return j;
        }
        
        swap(data[i], data[j]);
        i++;
        j--;
    }
    return -1; //shouldn't reach here
}


////////////////// (Top-Down) Merge Sort /////////////////
static
void merge(string data[], size_t n1, size_t n2);

void mergesort(string data[], size_t n)
{
	if (n > 1)
	{
		// Compute the sizes of the subarrays
		size_t n1 = n / 2;
		size_t n2 = n - n1;

		// Sort two subarrays
		mergesort(data, n1);
		mergesort(data + n1, n2);

		// Merge the two sorted halves
		merge(data, n1, n2);
	}
}
// Precondition: data is an array with n1+n2 elements, where 
// the first n1 elements and the last n2 elements are sorted, respectively. 
// Postcondition: The elements of data array have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].
static
void merge(string data[], size_t n1, size_t n2)
{
	size_t n = n1 + n2;
	string* temp = new string[n];

	size_t index_left = 0;
	size_t index_right = n1;
	size_t temp_index = 0;

	while (index_left < n1 && index_right < n)
	{
		if (data[index_left] <= data[index_right])
		{
			temp[temp_index++] = data[index_left++];
		}
		else
		{
			temp[temp_index++] = data[index_right++];
		}
	}

	//copy the remaining elements
	while (index_left < n1)
	{
		temp[temp_index++] = data[index_left++];
	}

	while (index_right < n)
	{
		temp[temp_index++] = data[index_right++];
	}

	for(size_t i = 0; i <temp_index; i++)
	{
		data[i] = temp[i];
	}
	delete[] temp;
}
