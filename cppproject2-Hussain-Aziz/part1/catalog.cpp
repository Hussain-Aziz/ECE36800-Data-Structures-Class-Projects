// Please add your name below
// Name: Hussain Aziz Saif

// FILE: catalog.cpp
//  This file reads from a booklist text file, prints the catalog,
//  then print a book's information given user input book id

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cassert>
#include "book.h"
#include "booklist1.h"

using namespace std;

// PROTOTYPE for functions used by main()
void fill_catalog(booklist& books, string bookfilename);


int main( )
{
	booklist catalog; 

	// Fill the catalog with books information
	fill_catalog(catalog, "booklist.txt");

	// Print the catalog
	cout << "Welcome to BookSea\n";
	catalog.list_books();

	// Test search_by_id
	char choice;
	cout << "Test search by book id? [y/n] ";
	cin >> choice;
	while (choice == 'y' || choice == 'Y')
	{
		// enter book id
		unsigned int bookid;
		cout << "Please enter a book id: ";
		cin >> bookid;
	
		book* bookfound = catalog.search_by_id(bookid);
	
		if (bookfound!=NULL) {
			cout << "Book found: \n";
			bookfound->print_info();
			
			cout << "Remove from the list? [y/n] ";
			cin >> choice;
			if (choice == 'y' || choice == 'Y')
			{
				// test remove_book
				if (catalog.remove_book(bookid)) {
					cout << "This book is successfully removed\n";
					cout << "Updated catalog: \n";
					catalog.list_books();
				}
				else
				{
					cout << "Cannot remove this book from catalog.\n";
					break;
				}
			}
		}
		else {
			cout << "Book not found!\n";
		}
		
		cout << "Search another book by id? [y/n] ";
		cin >> choice;
	} 
	
	return 0;
}

// Creates the default book catalog
void fill_catalog(booklist& books, string bookfilename)
{
	// Open the booklist file for read
	ifstream bookfile;
	bookfile.open(bookfilename.c_str(), ifstream::in);

	assert(bookfile);

	while (!bookfile.eof())
	{
		//-------------------------------------
		// TO-DO: read one line at a time, 
		//		  create a book node,
		// 		  and add into the booklist

		//create variables to hold data
		unsigned int id, copies;
		string title;
		double price;

		//read the data in the order put in the file
		bookfile >> id;
		bookfile.ignore();
		std::getline(bookfile, title, '\t');
		bookfile >> price;
		bookfile >> copies;

		//add book to booklist
		books.add_book(new book(id, title, price, copies));
	};

	// close the booklist file
	bookfile.close();
}
