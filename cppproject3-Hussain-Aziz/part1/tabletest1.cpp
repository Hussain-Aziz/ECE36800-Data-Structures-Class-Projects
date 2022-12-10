// FILE: tabletest1.cpp
// A simple test program for the ChainTable and QuadTable classes.

#include <iostream>    // Provide cin, cout
#include <fstream>	   // Provide ifstream
#include <cassert>	   // Provide assert
#include <string>	   // Provide string
#include "table1.h"    // Provide the ChainTable and QuadTable classes
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
		
	string keyword;
	char choice = toupper(get_choice( ));
	switch (choice)
	{
		case 'C':
		{
			// Select chained hash table
			ChainTable keytable;
			while (!keyfile.eof()) {
				string keyword;
				keyfile >> keyword; // Read next keyword 
		
				keytable.insert(keyword); // Insert keyword into hash table
			}
			keyfile.close(); // close keyword file 

			cout << "There are " << keytable.get_total( ) << " records in the table.\n"; 
			
			keytable.print();		// print table content
				
			break;
		}
		case 'Q':   
		{
			// Select quadratic probing hash table
			QuadTable keytable;
			while (!keyfile.eof()) {
				string keyword;
				keyfile >> keyword; // Read next keyword 
		
				keytable.insert(keyword); // Insert keyword into hash table
			}
			keyfile.close(); // close keyword file 
	
			cout << "There are " << keytable.get_total( ) << " records in the table.\n"; 
			
			keytable.print();		// print table content

			break;
		}
		default:
			cout << choice << " is not a valid input." << endl;
			return 0;
	}	
	
	return 0;
}