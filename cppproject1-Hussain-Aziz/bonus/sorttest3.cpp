// Please add your name below
// Name: Hussain Aziz Saif

// FILE: sorttest3.cpp
//  This file reads a word list file, 
//  sorts the words, tests if the words are sorted, 
//  and prints the words in a new file. 

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <vector>

using namespace std;

// PROTOTYPE for functions used by main()
bool check_ordered(string data[], size_t n);
void swap(string & s1, string & s2);
void quicksort(string data[], size_t n);
void BucketSort(string data[], int size);

int main(int argc, char** argv)
{
	string inputfilename; // input filename
	cout << "Please specify the file with data to be sorted: ";
	getline(cin, inputfilename);

	ifstream inputfile(inputfilename); // file stream for input text file

	assert(inputfile);	// assert no file open errors
	
	int numItems; //store number of items in the text file
	inputfile >> numItems; //get the number of items in text file

	//create a new dynamic string array
	string* sortItems = new string[numItems];

	//populate the array
	for (size_t i = 0; i < numItems; i++)
	{
		inputfile >> sortItems[i];
	}
	
	inputfile.close(); // close the input file
	
	// Record the start time
    clock_t nStart = clock();
	//sort the array using bubblesort
	BucketSort(sortItems, numItems);
	
 	// Record the end time
    clock_t nEnd = clock();

    // Print out total execution time for sorting
    cout << "Time elapsed: " << (nEnd - nStart) * 1.0 / CLOCKS_PER_SEC * 1000 << " msec.\n";


	if (!check_ordered(sortItems, numItems)) return 1; // Check if words array is sorted	
		
	cout << "Please specify a file name to hold the sorted data: ";
	string outputfilename;  // output filename
	getline(cin, outputfilename); 
	ofstream outputfile(outputfilename); // file stream for output text file
	
	//write the sorted words into the file
	for (size_t i = 0; i < numItems; i++)
	{
		outputfile << sortItems[i] << endl;
	}
	
	outputfile.close(); // close the output file

	//free up the space used by the dynamic array
	delete[] sortItems;

	return 0;
}

static 
size_t getLocationInArray(char character);

void BucketSort(string data[], int size)
{
    if (size < 1) return;


    // Record the start time
    clock_t nStart = clock();

    vector<string> buckets[52];//create 52 string vectors

    // Put each number in a bucket
    for(size_t i = 0; i < size; i++)
    {
        size_t index = getLocationInArray(data[i].at(0));
        buckets[index].push_back(data[i]);
    }

    size_t filledIndex = 0;

    // Sort each bucket
    for(size_t i = 0; i < 52; i++)
    {
        if (buckets[i].empty()) continue;

        //std::sort(buckets[i].begin(), buckets[i].end());
        quicksort(buckets[i].data(), buckets[i].size() - 1);

        for(size_t j = 0; j < buckets[i].size(); j++)
        {
            data[filledIndex++] = buckets[i][j];
        }
    }
}

static
size_t getLocationInArray(char character)
{
    int ascii = (int)character;

    if (ascii >= 65 && ascii <= 90)
    {
        return ascii - 65;
    }
    if (ascii >= 97 && ascii <= 122)
    {
        return ascii - 65 - 6; //from the 6 characters in between
    }
    return 0;
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

// Check whether a string array is sorted and print result
bool check_ordered(string data[], size_t n)
{
	//loop from 0 to n-1 (because the last comparison we need to compare with index + 1 so n-1 to make that valid)
	for (size_t i = 0; i < n - 1; i++)
	{
		//if the next string in the array proceeds it, return false to show the order is incorrect
		if (data[i] > data[i+1])
		{
			return false;
		}
	}
	
	//if we have reached this point it means all the strings are in order so we return true
	return true;
}

//////////////// Swap ////////////////////////////
void swap(string & s1, string & s2)
{
	string temp;
	temp = s1;
	s1 = s2;
	s2 = temp;
}