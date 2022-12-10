// FILE: booklist1.h 
// CLASS PROVIDED: booklist
//
// CONSTRUCTOR and DESCTRUCTOR:
//	booklist( )
//		Initialize a booklist as an empty list
//
//	~booklist()
//		Empty the booklist and release its memory 
//
// CONSTANT MEMBER FUNCTIONS:
//	void list_books() const
//		Print information of the books in the list
//
//	book* search_by_id(unsigned int id) const
//		Search in booklist, find the book with given id
//	 	Return the book pointer with matching id; otherwise return NULL
//
// MODIFICATION MEMBER FUNCTIONS:
//	void add_book(const book* b)
//		Add a book node to the booklist
//
//  bool remove_book(unsigned int id)
//		Remove a book from the booklist
//  	Return true if found; otherwise return false


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
	
	// MODIFICATION MEMBER FUNCTIONS
	void add_book(book* b);
	bool remove_book(unsigned int id);

private:
	node* head;
};

#endif
