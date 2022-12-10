// FILE: booklist2.h 
// CLASS PROVIDED: booklist
//
// CONSTRUCTOR and DESCTRUCTOR:
//	booklist( )
//		Initialize a booklist as an empty list
//
//	~booklist()
//		Empty the booklist and release the memory 
//
// CONSTANT MEMBER FUNCTIONS:
//	void list_books() const
//		Print information of the books in the list
//
//	book* search_by_id(unsigned int id) const
//		Search in booklist, find the book with given id
//	 	Return the book pointer with matching id; otherwise return NULL
//
//	double calculate_total_price() const
//		Calculate and return total price of the books in the booklist

// MODIFICATION MEMBER FUNCTIONS:
//	void add_book(const book* b)
//		Add a book node to the booklist. 
//
//  bool remove_book(unsigned int id)
//		Remove a book from the booklist
//  	Return true if found; otherwise return false
//
//	bool add_book_copies(unsigned int id, unsigned int copies)
//		Search in booklist, find the book with given id, and add copies
//		  return false if book with specified id cannot be found
//
//	bool remove_book_copies(unsigned int id, unsigned int copies)
//		Search in booklist, find the book with given id, and remove copies
//		  retrun false if book with specified id cannot be found; or
//	      the book with specified id is found but not enough copies to be removed

#ifndef BOOKLIST_H
#define BOOKLIST_H

#include "book.h"
using namespace std;

class node 
{
public:
	book* book_ptr;
	node* next_ptr;
	node(book* b) 
	{ 
		book_ptr = b; 
		next_ptr = NULL; 
	}
	~node()
	{
		delete book_ptr;
	}
};

class booklist
{
public:
	booklist(); // Constructor
	~booklist(); // Desctructor
   
	// CONSTANT MEMBER FUNCTIONS 
	void list_books() const;
	book* search_by_id(unsigned int bookid) const;
	double calculate_total_price() const;
 
	// MODIFICATION MEMBER FUNCTIONS
	void add_book(book* b);
	bool remove_book(unsigned int bookid);
	bool add_book_copies(unsigned int bookid, unsigned int copies);
	bool remove_book_copies(unsigned int bookid, unsigned int copies);
	
private:
	node* head;
};

#endif
