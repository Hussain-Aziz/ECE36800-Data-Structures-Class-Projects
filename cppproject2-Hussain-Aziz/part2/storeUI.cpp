// Please add your name below
// Name: Hussain Aziz Saif

// storeUI.cpp: A user interactive program for the bookstore
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cassert>
#include "book.h"
#include "booklist2.h"

using namespace std;

// PROTOTYPES for functions used by main
void fill_catalog(booklist& books, string bookfilename);
void print_menu();
char get_choice( );
void checkout(const booklist& books);

int main( )
{
	booklist catalog; // a book catalog for the book store
	booklist cart; // a list of books in the cart

	// Fill the list of books with the default catalog of books
	fill_catalog(catalog, "booklist.txt");

	// Print the menu
	cout << "Welcome to BookSea\n";
	print_menu();

	// Read in choice until the user inputs 'Q' or 'q'
	char choice;
	do
	{
		choice = toupper(get_choice());
		switch (choice)
		{
			// Perform the command entered by the user
			case 'L':
			{
				// List the books in the catalog
				catalog.list_books();
				
				// Print the menu
				print_menu();
				
				break;
			}
			case 'A':   
			{
				// Get the book ID of the book to be added
				unsigned int add_book_id;
				cout << "Book ID? ";
				cin >> add_book_id;
				assert(add_book_id>0);

				// Get the number of copies
				unsigned int addcopies;
				cout << "How many copies? ";
				cin >> addcopies;
				assert(addcopies>0);

				//----------------------------------------------------------
				// TO-DO: Search the book in the catalog and add to the cart
				// ------
				// Make sure to handle the following cases:
				//  1. if id not found in catalog
				//  2. If id found in catalog, but not enough copies
				//  3. If id found in catalog, update both cart and catalog
				//	   	In addition, if all copies are added to the cart, then 
				//		the book should be removed from the catalog
				
				book* searchedbook = catalog.search_by_id(add_book_id);

				if (searchedbook == NULL)
				{
					cout << "Book with id " << add_book_id << " not found in catalog." << endl;
					print_menu();
					break;
				}
				
				bool sucessfulRemove = catalog.remove_book_copies(add_book_id, addcopies);

				if (sucessfulRemove)
				{
					if (!cart.add_book_copies(add_book_id, addcopies))
					{
						cart.add_book(new book(searchedbook->get_id(), searchedbook->get_title(), searchedbook->get_price(), addcopies));
					}
				}
				else
				{
					cout << "You have requested more books than there are available." << endl;
					print_menu();
					break;
				}

				// Print the cart content
				cout << "\nItems in cart:" << endl;
				cart.list_books();

				// Print the menu
				print_menu();
				
				break;
			}
			case 'R':   
			{
				// Get the book ID of the book to be removed
				unsigned int remove_book_id;
				cout << "Book ID? ";
				cin >> remove_book_id;
				assert(remove_book_id>0);
                
				// Get the number of copies
				unsigned int removecopies;
				cout << "How many copies? ";
				cin >> removecopies;
				assert(removecopies>0);
				
				//----------------------------------------------------------
				// TO-DO: Search book in the cart and return to the catalog
				// ------
				// Make sure to address the following cases:
				//  1. if id not found in cart
				//  2. If id found in cart, but not enough copies
				//  3. If id found in cart, update both cart and catalog
				//	   	In addition, if all copies are removed from the cart, then 
				//		the book should be removed from the cart;
				//		Also, if catalog does not already have the corresponding 
				//		book entry, a new book record (node) should be added
				
				book* searchedbook = cart.search_by_id(remove_book_id);

				if (searchedbook == NULL)
				{
					cout << "Book with id " << remove_book_id << " not found in cart." << endl;
					print_menu();
					break;
				}

				bool sucessfulRemove = cart.remove_book_copies(remove_book_id, removecopies);

				if (sucessfulRemove)
				{
					if (!catalog.add_book_copies(remove_book_id, removecopies))
					{
						catalog.add_book(new book(searchedbook->get_id(), searchedbook->get_title(), searchedbook->get_price(), removecopies));
					}
				}
				else
				{
					cout << "You have removed more books than there are available." << endl;
					print_menu();
					break;
				}
				
				

				// Print the cart content
				cout << "\nItems in cart:" << endl;
				cart.list_books();
				
				// Print the menu
				print_menu();
				
				break;
			}
			case 'C':
			{
				// Check out and show the total price and savings
				checkout(cart);
				return 0;
			}
			case 'Q':
			{
				cout << "Goodbye!" << endl;
				break;
			}
			default:
				cout << choice << " is not a valid input." << endl;
		}
	} while (choice != 'Q');

	return 0;
}


// Read from book list and create book catalog
void fill_catalog(booklist& books, string bookfilename)
{
	// Open the booklist file for reading
	ifstream bookfile;
	bookfile.open(bookfilename.c_str(), ifstream::in);

	assert(bookfile);

	while (!bookfile.eof())
	{
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

// Print menu options
void print_menu() 
{
	// Display the menu of commands 
	cout << "=========================" << endl;
	cout << "Menu:" << endl;
	cout << "[L]ist all books" << endl;
	cout << "[A]dd a book to cart" << endl;
	cout << "[R]emove a book from cart" << endl;
	cout << "[C]heckout" << endl;
	cout << "[Q]uit" << endl;
	cout << "=========================" << endl;
}

// Read the command choice of the user
char get_choice( ) 
{
	// Get input command and return the input character
	char command;
	cout << "\nCommand: ";
	cin >> command;
	return command;
}

// Calculate and display the total cost and savings of the books in cart
void checkout(const booklist& books) 
{
	// Output the items in the cart
	cout << "Items in cart:";
	books.list_books();

	// Add up the total price and sale savings
	double total_price = books.calculate_total_price();

	cout << "Total price: $" << total_price << endl;
	cout << "Thanks for shopping with BookSea!" << endl;
	cout << "Goodbye!" << endl;
}