// Please add your name below
// Name: Hussain Aziz Saif

// FILE: sorttest1.cpp
//  This file reads a word list file, 
//  sorts the words, tests if the words are sorted, 
//  and prints the words in a new file. 

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

// PROTOTYPE for functions used by main()
bool check_ordered(string data[], size_t n);
void bubblesort(string data[ ], size_t n);

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
	
	//sort the array using bubblesort
	bubblesort(sortItems, numItems);
	
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

//////////////// Bubble Sort ////////////////////////////
void swap(string & s1, string & s2)
{
	string temp;
	temp = s1;
	s1 = s2;
	s2 = temp;
}

void bubblesort(string data[ ], size_t n)
// Using bubble sort to sort elements of data in ascending order 
// i.e., data[0] <= data[1] <= ... <= data[n-1]
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