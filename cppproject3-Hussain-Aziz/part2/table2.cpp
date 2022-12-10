// Please add your name below
// Name: Hussain Aziz Saif

// FILE: table2.cpp
// CLASS IMPLEMENTED: ChainTable and QuadTable (see table2.h for documentation)

#include <iostream>
#include "table2.h" 

void ChainTable::insert(string key)
{
	//--------------------------------------------------------------
	// TO-DO: insert key into the chained hash table 
	// ------
	//   Modify from the implementation from part 1
	//   1. use hashcode function to calculate bucket index i
	//	 2. check if key is already in the list at datatable[i];
	//	    - if yes, increment the count by 1 
	//	    - if no, create a Record object from key and insert into 
	//				the list, increment total_records
	
	unsigned int index = Table::hashcode(key);
	if (datatable[index].empty())
	{
		datatable[index] = list<Record>();
	}

	bool alreadyPresent = false;
	for(list<Record>::iterator it = datatable[index].begin(); it != datatable[index].end(); it++)
	{
		if (it->key == key)
		{
			it->count++; //increment count
			alreadyPresent = true;
		}
	}

	if (!alreadyPresent)
	{
		datatable[index].push_back(Record(key, 1)); //start the count at 1
		total_records++;
	}
	
	
	
	
	
}

// print the Record with the highest count
void ChainTable::print_max()
{
	//-------------------------------------------------------------
	// TO-DO: go through the hash table, 
	//		find the record with the highest count, 
	//		and print out the information.
	// ------
	//   You can use ChainTable::print() from part 1 as a reference
	
	cout << "The most frequent record is ";
	if (total_records==0) 
	{
		cout << "\t None!\n";
		return;
	}

	Record mostFrequentRecord;

	for (unsigned int i=0; i<TABLE_SIZE; i++)
	{	    
		if (datatable[i].empty()) 
			continue;

		for (list<Record>::iterator it = datatable[i].begin(); it != datatable[i].end(); it++)
		{
			if (it->count > mostFrequentRecord.count)
			{
				mostFrequentRecord = *it;
			}
		}
	}

	cout << "\"" << mostFrequentRecord.key << "\"" << " which occured " << mostFrequentRecord.count << " times" << endl;
}

//////////////////////////////////////////////////
void QuadTable::insert(string key)
{
	//--------------------------------------------------------------
	// TO-DO: insert key into the hash table using quadratic probing
	// ------
	//   Modify from the implementation from part 1
	//	 1. use hashcode function to calculate array index i
	//	 2. check if datatable[i] is empty
	//	    - if yes, create a Record object from key and sotre at datatable[i]
	//	    - if no, use quadratic probing with probe function c(i)=i^2,
	//		  if key is found, increment count; 
	//		  if key is not found, then look for an empty location,
	//		     insert key at that location, set count = 1, increment total_records
	//	 4. if datatable is full and key is new, do nothing and return

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
		if (!(datatable[index].count == 0 && datatable[index].key == "")) //checks for not empty record
		{
			if (datatable[index].key == key)
			{
				datatable[index].count++;
				added = true;
			}
			else
			{
				collisions++;
			}
		}
		else //if it is empty
		{
			datatable[index] = Record(key, 1);
			total_records++;
			added = true;
		}
	}
}

// print the Record with the highest count
void QuadTable::print_max()
{
	//-------------------------------------------------------------
	// TO-DO: go through the hash table, 
	//		find the record with the highest count, 
	//		and print out the information.
	// ------
	//   You can use QuadTable::print() from part 1 as a reference

	cout << "The most frequent record is ";
	if (total_records==0) 
	{
		cout << "\t None!\n";
		return;
	}

	Record mostFrequentRecord;

	for (unsigned int i=0; i<TABLE_SIZE; i++)
	{    
		if (datatable[i].count == 0 && datatable[i].key == "") 
			continue;

		if (datatable[i].count > mostFrequentRecord.count)
		{
			mostFrequentRecord = datatable[i];
		}
	}

	cout << "\"" << mostFrequentRecord.key << "\"" << " which occured " << mostFrequentRecord.count << " times" << endl;
}