// FILE: book.h
// CLASS PROVIDED: book
//     A book has the following features:
//     id: a positive integer identification number
//     title: a string showing the book title
//     price: a real value showing the book price
//     copies: a positive integer showing the number of book copies
//
#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class book
{
private:
	unsigned int id;     // book id
	string title;	     // book title
	double price;	     // book price
	unsigned int copies; // number of copies

public:
	book() {}
	book(unsigned int n, string t, double p, unsigned int c);

	// MODIFICATION MEMBER FUNCTIONS
	void set_id(unsigned int n) { id = n; }
	void set_title(string t) { title = t; }
	void set_price(double p) { price = p; }
	void set_copies(unsigned int c) { copies = c; }
	void set_info(unsigned int n, string t, double p, unsigned int c); 

	// CONSTANT MEMBER FUNCTIONS
	unsigned int get_id( ) const { return id; }
	string get_title( ) const { return title; }
	double get_price( ) const { return price; }
	unsigned int get_copies( ) const { return copies; }
	void print_info() const; //print book information

};

#endif
