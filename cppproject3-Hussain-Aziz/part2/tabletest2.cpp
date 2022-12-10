// FILE: tabletest2.cpp
// A simple test program for the ChainTable and QuadTable classes.

#include <iostream>    // Provide cin, cout
#include <fstream>	   // Provide ifstream
#include <cassert>	   // Provice assert
#include <string>	   // Provide string
#include <sstream>	   // Provide stringstream
#include <algorithm>   // Provide transform function
#include "table2.h"    // Provide the ChainTable and QuadTable classes
using namespace std;

// Read the command choice of the user
char get_choice( ) 
{
	// Get input command and return the input character
	char choice;
	cout << "\nPlease select type of hash table: [C/Q: Chaining or Quadratic] ";
	cin >> choice;
	cout << endl;
	return choice;
}

int main()
{
	string inputfilename; // input filename
	cout << "Please specify the file with keys to be inserted: ";
	getline(cin, inputfilename);
	ifstream keyfile(inputfilename); // file stream for keyword file
	
	assert(keyfile);	// assert no file open errors
			
	char choice = toupper(get_choice( ));
	switch (choice)
	{
		case 'C':
		{
			// Select chained hash table
			ChainTable keytable;
			while (!keyfile.eof()) {
				string nextline;
				getline(keyfile, nextline); // Read next line 
				stringstream ss(nextline);
				string keyword;
				while (ss >> keyword) // read one word a time
				{
					// convert to all lower case, then insert into hash table
					transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
					keytable.insert(keyword); 
				}
			}
			keyfile.close(); // close keyword file 

			cout << "There are " << keytable.get_total( ) << " records in the table.\n"; 
			
			keytable.print_max();		// print the most frequent word and its count
				
			break;
		}
		case 'Q':   
		{
			// Select quadratic probing hash table
			QuadTable keytable;
			while (!keyfile.eof()) {
				string nextline;
				getline(keyfile, nextline); // Read next line 
				stringstream ss(nextline);
				string keyword;
				while (ss >> keyword) // read one word a time
				{
					// convert to all lower case, then insert into hash table
					transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
					keytable.insert(keyword); 
				}
			}
			keyfile.close(); // close keyword file 
	
			cout << "There are " << keytable.get_total( ) << " records in the table.\n"; 
			
			keytable.print_max();		// print the most frequent word and its count

			break;
		}
		default:
			cout << choice << " is not a valid input." << endl;
			return 0;
	}	
	
	return 0;
}