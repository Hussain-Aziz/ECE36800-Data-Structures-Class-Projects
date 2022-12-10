// Please add your name below
// Name: Hussain Aziz Saif

// FILE: table1.cpp
// CLASS IMPLEMENTED: ChainTable and QuadTable (see table1.h for documentation)

#include <iostream>
#include "table1.h" 

void ChainTable::insert(string key)
{
	//-----------------------------------------------
	// TO-DO: insert key into the chained hash table 
	// ------
	//   1. use hashcode function to calculate bucket index i
	//	 2. check if key is already in the list at datatable[i];
	//	    - if yes, do nothing 
	//	    - if no, insert key into the list, increment total_records
	
	unsigned int index = Table::hashcode(key);
	if (datatable[index].empty())
	{
		datatable[index] = list<string>();
	}

	bool alreadyPresent = false;
	for(list<string>::iterator it = datatable[index].begin(); it != datatable[index].end(); it++)
	{
		if ((*it) == key)
		{
			alreadyPresent = true;
		}
	}

	if (!alreadyPresent)
	{
		datatable[index].push_back(key);
		total_records++;
	}
}

// visually print table contents 
void ChainTable::print()
{
	cout << "ChainTable content: \n";
	if (total_records==0) 
	{
		cout << "\t Empty!\n";
		return;
	}

	for (unsigned int i=0; i<TABLE_SIZE; i++)
	{	    
		if (datatable[i].empty()) 
			continue;

		cout << "\t Entry " << i << ": "; 
		for (list<string>::iterator it = datatable[i].begin(); it != datatable[i].end(); it++)
		{
			cout << (*it) << " -> ";
		}
		cout << "NULL\n";
	}
}

//////////////////////////////////////////////////
void QuadTable::insert(string key)
{
	//--------------------------------------------------------------
	// TO-DO: insert key into the hash table using quadratic probing
	// ------
	//   1. if hash table is full, do nothing and return
	//	 2. use hashcode function to calculate array index i
	//	 3. check if datatable[i] is empty
	//	    - if yes, insert key at datatable[i]
	//	    - if no, use quadratic probing until an empty location is found
	//		  insert key at that location
	//	 4. increment total_records
	//	 Note if key is already in the table, do nothing
	
	if (full())
	{
		return;
	}

	unsigned int origninalIndex = Table::hashcode(key);
	
	unsigned int collisions = 0;

	bool added = false;
	while(!added)
	{
		//calculate the index using c = i^2
		unsigned int index = (origninalIndex + (collisions * collisions)) % TABLE_SIZE;
		if (!datatable[index].empty())
		{
			if (datatable[index] == key)
			{
				added = true;
			}
			else
			{
				collisions++;
			}
		}
		else //if it is empty
		{
			datatable[index] = key;
			total_records++;
			added = true;
		}
	}

}

// visually print table contents 
void QuadTable::print()
{
	cout << "QuadTable content: \n";
	if (total_records==0) 
	{
		cout << "\t Empty!\n";
		return;
	}

	for (unsigned int i=0; i<TABLE_SIZE; i++)
	{	    
		if (datatable[i].empty()) 
			continue;

		cout << "\t Entry " << i << ": "; 
		cout << datatable[i] << endl;
	}
}