// Please add your name below
// Name: Hussain Aziz Saif

// FILE: sorttest2.cpp
// This file tests and compares different sorting algorithms

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include "sort.h"

using namespace std;

// PROTOTYPES for functions used by main
void print_menu( ); 
char get_user_command( ); 
bool check_ordered(string data[], size_t n);

int main()
{
	string inputfilename; // input filename
	cout << "Please specify the file with data to be sorted: ";
	//cin.ignore();
	getline(cin, inputfilename);

	ifstream inputfile(inputfilename); // file stream for input text file

	assert(inputfile);	// assert no file open errors
	
	//	- Read the words into the words array
	size_t numItems; //store number of items in the text file
	inputfile >> numItems; //get the number of items in text file

	//create a new dynamic string array
	string* sortItems = new string[numItems];

	//populate the array
	for (size_t i = 0; i < numItems; i++)
	{
		inputfile >> sortItems[i];
	}
	
	inputfile.close(); // close the input file
	
	print_menu( ); // print menu
	char choice = get_user_command( ); // get user selection
	
	// Record the start time
	clock_t nStart = clock();

	// call sort function based on user selection
	switch (choice)
    {
		case '1': 
			bubblesort(sortItems, numItems);
			break;
		case '2':
			selectionsort(sortItems, numItems);
			break;
        case '3': 
			insertionsort(sortItems, numItems);
            break;
        case '4': 
			shellsort(sortItems, numItems);
            break;
        case '5': 
			quicksort(sortItems, numItems - 1);
            break;
		case '6': 
			mergesort(sortItems, numItems);
			break;
        default:  
			cerr << choice << " is invalid. Sorry." << endl;
			return 1;
    }
	
	// Record the end time
	clock_t nEnd = clock();

	// Print out total execution time for sorting
	cout << "Time elapsed: " << (nEnd-nStart)*1.0/CLOCKS_PER_SEC*1000 << " msec.\n";
	
		
	if (!check_ordered(sortItems, numItems)) return 1; // Check if words array is sorted	
	
	cout << "Please specify a file name to hold the sorted data: ";
	string outputfilename;  // output filename
	cin.ignore();
	getline(cin, outputfilename); 
	ofstream outputfile(outputfilename); // file stream for output text file
 	
	// print all words, one a line, to the output file
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

// Print menu choices to cout
void print_menu( )
{
	cout << endl; // Print blank line before the menu
	cout << "The following choices are available: " << endl;
	cout << " 1   Run bubblesort" << endl;
	cout << " 2   Run selectionsort" << endl;
	cout << " 3   Run insertionsort" << endl;
	cout << " 4   Run shellsort" << endl;
	cout << " 5   Run quicksort" << endl;
	cout << " 6   Run mergesort" << endl;
}

// Get user menu selection from cin
char get_user_command( )
{
	char command;

	cout << "Enter choice: ";
	cin >> command; // Input of characters skips blanks and newline character

	return command;
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
