// book.cpp: implementation of the book class.

#include <iostream>
#include <iomanip>
#include "book.h"

// Constructor
book::book(unsigned int bookid, string booktitle, double bookprice, unsigned int bookcopies)
{
	id = bookid;
	title = booktitle;
	price = bookprice;
	copies = bookcopies;
}

// Set the information for the book
void book::set_info(unsigned int bookid, string booktitle, double bookprice, unsigned int bookcopies)
{	
	id = bookid;
	title = booktitle;
	price = bookprice;
	copies = bookcopies;
}

// Print out the information for the book
void book::print_info() const 
{
	// Set output to fixed point, right justified, precision 2
	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::right, ios::adjustfield);
	cout.precision(2);

	// Set width of next output to 2 characters with blank space fillers
	cout.fill(' ');
	cout.width(2);

	// Print the book ID number
	cout << id;

	// Lift the width requirement and print a period
	cout.width(0);
	cout.setf(ios::left, ios::adjustfield);
	cout << ". ";

	// Set width to 50 and output the book's title
	cout.width(50);
	cout << title;
	
	// Output the price, copies, and sale status with same formatting technique as above
	cout.width(0);
	cout << "$";
	
	// Print price with width of 7
	cout.width(7);
	cout << price;
	
	// Print copies with width of 8
	cout.width(8);
	cout << copies;
	
	cout.width(0);
	cout << endl;
}
