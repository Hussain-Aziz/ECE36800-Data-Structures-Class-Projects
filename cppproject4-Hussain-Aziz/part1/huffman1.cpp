// Please add your name below
// Name: Hussain Aziz Saif

// FILE: huffman1.cpp
//   This file reads the probabilities of 26 English characters and 
//   build a Huffman tree and the corresponding Huffman code for each character.

#include <fstream>
#include <list>
#include <stack>
#include <string>
#include <cassert>
#include "node.h"

int main()
{
//////////////////////   Read Probability Data   /////////////////////

	// Open the probability file for reading
	string probfilename = "probability.txt";
	ifstream probfile;
	probfile.open(probfilename.c_str(), ifstream::in);

	assert(probfile);

	// Read in letters and associated probabilities, create a list of nodes
	list<node*> node_list;
	for (unsigned int n=0; !probfile.eof(); n++)
	{
		char c;
		double p;
		probfile >> c >> p;
		node* newnode = new node(toupper(c), p);
		node_list.push_back(newnode);
	}

	// Close the probability file
	probfile.close();
	
///////////////////   Construct Huffman Coding Tree ////////////////////

	while (node_list.size() > 1) 
	{		
		//---------------------------------------------------------------------
		//  TODO: Repeat the following
		// ------
		//  - Sort node_list in ascending order of probability, can be done by: 
		//					node_list.sort(comp_prob);
		//	- Extract the two nodes with the lowest probabilities, 
		//	  remove them from node_list, merge them to create a new node,
		//	  and insert the new node back into the list.
		
		node_list.sort(comp_prob);

		node* firstSmallest = *(node_list.begin());
		node* secondSmallest = *(++node_list.begin());

		node_list.remove(firstSmallest);
		node_list.remove(secondSmallest);

		node* newNode = new node(firstSmallest, secondSmallest);

		node_list.push_back(newNode);
	}
	
///////////////////   Generate Huffman Codes ////////////////////////

	//---------------------------------------------------------------------
	//  TODO: Traverse the huffman tree to generate the huffman coding table    
	// ------
	// 	- Please create a string array, e.g., string codearray[26], 
	//	    to store the code string of each English character
	//  - Please also print out the code for each letter here
	
	string codeArray[26];

	node* root = *(node_list.begin()); // garunteed to be root because in previous while loop we looped until size == 1
	root->code = "";

	//visit all node using pre order traversal
	stack<node*> nodeToVisit;
	nodeToVisit.push(root);
	
	while(!nodeToVisit.empty())
	{
		node* workingRoot = nodeToVisit.top();
		nodeToVisit.pop();

		node* left = workingRoot->left;
		node* right = workingRoot->right;

		left->code = workingRoot->code + "0";
		right->code = workingRoot->code + "1";

		if (left->is_leaf())
		{
			codeArray[(int)left->letter - ((int)'A')] = left->code;
		}
		else
		{
			nodeToVisit.push(left);
		}
		
		if(right->is_leaf())
		{
			codeArray[(int)right->letter - ((int)'A')] = right->code;
		}
		else
		{
			nodeToVisit.push(right);
		}
	}

	for(int i = 0; i < 26; i++)
	{
		cout << (char) (i + ((int)'A')) << ": " << codeArray[i] << endl;
	}

	//---------------------------------------------------------------------
	//  TODO: Delete all the node objects    
	// ------
	// 	Please call clean(root), where root is the root node of the huffman tree

	clean(root);

	return 0;
}
