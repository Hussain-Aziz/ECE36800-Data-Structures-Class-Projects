// Please add your name below
// Name: Hussain Aziz Saif

// booklist2.cpp: implementation of the booklist class

#include <iostream>
#include "booklist2.h"

// constructor: initialize head
booklist::booklist() 
{ 
	head = NULL; 
}

// destructor: traverse booklist and release memory for each node
booklist::~booklist() 
{
	for ( node* p=head; p!=NULL;)  
	{
		node* next = p->next_ptr;
		delete p; 
		p = next;
	}
}

// print out information of books in booklist
void booklist::list_books() const
{
	// Set output to fixed point, left justified, precision 2
	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::left, ios::adjustfield);
	cout.precision(2);

	// Set width of the Book Title label to be 54 characters with blank space fillers
	// to give room for lengthy book titles
	cout.fill(' ');
	cout.width(54);

	cout << "Book Title";

	// Do not impose a width requirement on further outputs
	cout.width(0);
	cout << "Price   " << "Copies  " << endl;

	// Set the width of the underline of the Book Title to 54 characters with blank
	// space fillers to match the text labels
	cout.width(54);
	cout << "----------";

	// Do not impose a width requirement on further outputs
	cout.width(0);
	cout << "-----   " << "------  " << endl;

	//Traverse through the booklist and print the books
	node* probe = head;
	while ( probe != NULL )
	{
		probe->book_ptr->print_info();
		probe = probe->next_ptr;
	}
}


// Search in booklist, find the book with given id
//	 Return the book pointer with matching id; otherwise return NULL
book* booklist::search_by_id(unsigned int bookid) const
{
	node* currNode = head;

	//while loop through till the end of linked list
	while(currNode != NULL)
	{
		if (currNode->book_ptr->get_id() == bookid)
		{
			return currNode->book_ptr;
		}

		//if ids dont match, go to next node
		currNode = currNode->next_ptr;
	}
	//no book found
	return NULL;
}

// Calculate and return total price of the books in the booklist
double booklist::calculate_total_price() const
{	
	double price = 0;
	
	if (head != NULL) //if its empty list, dont add to price
	{
		node* currNode = head;
		//go through the whole list
		while(currNode->next_ptr != NULL)
		{
			price += currNode->book_ptr->get_price() * currNode->book_ptr->get_copies();
			currNode = currNode->next_ptr;
		}

		//add price of tail node	
		price += currNode->book_ptr->get_price() * currNode->book_ptr->get_copies();
	}
	
	return price;
	
}

// Add a new book to the booklist
void booklist::add_book(book* b) 
{
	node* newNode = new node(b);

	//if list is empty
	if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		node* currNode = head;

		//go until the last element of the list
		while(currNode->next_ptr != NULL)
		{
			currNode = currNode->next_ptr;
		}

		//make the last array point to this
		currNode->next_ptr = newNode;
	}
}

// Remove a book from the booklist
//   Return true if found; otherwise return false
bool booklist::remove_book(unsigned int bookid) 
{
	//check if list is empty
	if(head == NULL)
	{
		return false;
	}

	//if head is the matching node
	if (head->book_ptr->get_id() == bookid)
	{
		node* oldhead = head;
		head = head->next_ptr;
		delete oldhead;
		return true;
	}

	node* currNode = head;

	//while loop through till the end of linked list
	//we loop using next_ptr because we still want access to the node before the deletion one so we can reroute
	while(currNode->next_ptr != NULL)
	{
		if (currNode->next_ptr->book_ptr->get_id() == bookid)
		{
			//make previous from deletion go to the one after deletion
			node* nodeToDelete = currNode->next_ptr;
			currNode->next_ptr = currNode->next_ptr->next_ptr;
			delete nodeToDelete;
			return true;
		}

		//if ids dont match, go to next node
		currNode = currNode->next_ptr;
	}
	//none found return false
	return false;
}

// Search in booklist, find the book with given id, and add copies
//   return false if book with specified id cannot be found
bool booklist::add_book_copies(unsigned int bookid, unsigned int copies) 
{
	book* book = search_by_id(bookid);

	//book not found
	if(book == NULL)
	{
		return false;
	}

	book->set_copies(book->get_copies() + copies);

	return true;
}

// Search in booklist, find the book with given id, and remove copies
//   return false if book with specified id cannot be found; or
//   the book with specified id is found but not enough copies to be removed
bool booklist::remove_book_copies(unsigned int bookid, unsigned int copies)
{
	//-----------------------------------------------------
	// TO-DO: Remove copies from the book with specified bookid
	// -----
	//  You can call the search_by_id function
	//  Make sure to handle the following cases:
	//   1. If book is found and with more copies, then reduce copies
	//   2. If book is found and the exact number of copies, remove the book from the list
	//   3. If book is found and not enough copies, return false
	//   4. If not found, return false
	
	book* book = search_by_id(bookid);

	//book not found
	if(book == NULL)
	{
		return false;
	}

	//trying to remove more copies than there exist
	if(copies > book->get_copies())
	{
		return false;
	}

	//remove copies
	book->set_copies(book->get_copies() - copies);

	//if no more copies, remove from list
	if (book->get_copies() == 0)
	{
		remove_book(book->get_id());
	}

	return true;
}