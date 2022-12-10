// FILE: table2.h
//
// ABSTRACT BASE CLASS: Table
// 	 1. The number of records in the Table is stored in total_records
//   2. The hashcode function returns a location in the table for the 
//      input key. It calls hash function in functional library.
//   3. insert and print are two virtual functions to be overridden
//      insert: Add a new record into the Table; 
//			    If key is already in the table, increment count
//      print_max: print the record with the highest count
//
// DERIVED CLASS: ChainTable
//   	The actual records are stored in a chained hash table.
//		datatable[i] stores a list of Records
//  
// DERIVED CLASS: QuadTable
//   	The actual records of the table are stored in an array.
//      datatable[i] stores one Record
//      

#ifndef TABLE_H
#define TABLE_H

#include <string>		// Provide string
#include <functional>   // Provide hash
#include <list> 		// Provide list
using namespace std;

class Table
{
public:
	// MEMBER CONSTANT
	static const unsigned int TABLE_SIZE = 5801; 

	Table() { total_records = 0; }
	virtual ~Table() { }

	unsigned int get_total() { return total_records; }

	virtual void insert(string key) =0;
	virtual void print_max() =0;
	
protected:
	unsigned int total_records;

	// HELPER FUNCTION
	unsigned int hashcode(string key) const
	{
		hash<string> thishash;
		return thishash(key) % TABLE_SIZE;
	}
};

class Record
{ 
public: 
	Record(string k="", unsigned int c=0) { key = k; count = c; }
	string key;
	unsigned int count;
};

class ChainTable : public Table
{
public:
	ChainTable() {}

	virtual void insert(string key);
	virtual void print_max();
	
private:
	list<Record> datatable[TABLE_SIZE];
};

class QuadTable : public Table
{
public:
	QuadTable() {}
	
	virtual void insert(string key);
	virtual void print_max();
	bool full() { return total_records == TABLE_SIZE; }
	
private:
	Record datatable[TABLE_SIZE];
};

#endif
