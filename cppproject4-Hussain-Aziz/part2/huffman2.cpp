// Please add your name below
// Name: Hussain Aziz Saif
//
// FILE: huffman2.cpp
// This file implements Huffman coding and decoding.

#include <fstream>
#include <list>
#include <string>
#include <cassert>
#include <cctype>
#include <stack>
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
		//-----------------------------------------------
		// Include implementation from part 1: 
		
		node_list.sort(comp_prob);

		node* firstSmallest = *(node_list.begin());
		node* secondSmallest = *(++node_list.begin());

		node_list.remove(firstSmallest);
		node_list.remove(secondSmallest);

		node* newNode = new node(firstSmallest, secondSmallest);

		node_list.push_back(newNode);
	}
		
///////////////////   Generate Huffman Codes ////////////////////////

	//-----------------------------------------------
	// Include implementation from part 1: 
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
			codeArray[(int)toupper(left->letter) - ((int)'A')] = left->code;
		}
		else
		{
			nodeToVisit.push(left);
		}
		
		if(right->is_leaf())
		{
			codeArray[(int)toupper(right->letter) - ((int)'A')] = right->code;
		}
		else
		{
			nodeToVisit.push(right);
		}
	}

	//print out all the codes
	for(int i = 0; i < 26; i++)
	{
		cout << (char) (i + ((int)'A')) << ": " << codeArray[i] << endl;
	}
	
/////////////////////////   Encode Input File   ////////////////////////////////

	// Open the text file for reading
	string textfilename = "input.txt";
	ifstream textfile;
	textfile.open(textfilename.c_str(), ifstream::in);

	assert(textfile);

	// Open the file for writing encoded text
	string encodedfilename = "encoded.txt";
	fstream encodedfile;
	encodedfile.open(encodedfilename.c_str(), fstream::out | fstream::in | fstream::trunc);

	assert(encodedfile);
	
	if (encodedfile.is_open())
	{
		// Input and encode each character from the input file one by one
		// and output them to the output file
		while (!textfile.eof()) 
		{
			// Read the character and convert it to uppercase
			char c;
			textfile.get(c);
			c = toupper(c);
			if (( c >= 'A') && (c <= 'Z'))
			{      
				//-----------------------------------------------
				// TODO: find the code string s for character c  
				string s = codeArray[(int)c - (int)'A'];
				
				if (!s.empty())
					encodedfile << s;
				else 
				{
					cout << "Error: cannot find the code for " << c << endl;
					return 0;
				}
			}
			else 
			{
				encodedfile << c;
			}
		}
	} 
	else
	{
		cout << "Error: output file cannot be opened!\n";
		textfile.close();
		return 0;
	}

	// Close the text file
	textfile.close();

//////////////////////// Decode the Encoded File ///////////////////////////

	// Reset the encoded text file for reading
	encodedfile.clear();
	encodedfile.seekg(0, ios::beg);

	// Open the file for writing decoded text
	string decodedfilename = "decoded.txt";
	ofstream decodedfile;
	decodedfile.open(decodedfilename.c_str(), ofstream::out);

	assert(decodedfile);

	if (decodedfile.is_open())
	{
		while (!encodedfile.eof())
		{             
			char c;
			encodedfile.get(c);
			
			if ((c != '0') && (c != '1'))
			{
				decodedfile << c;
				continue;
			}
			
			//-----------------------------------------------
			// TODO: Using the Huffman tree, keep reading or 
			// 		 converting the code to the matching character 
			//		 and print to decodedfile   
			
			//the if check above garuntees it be 0 or 1
			node* workingRoot = c == '0' ? root->left : root->right;

			while(true)
			{
				if (workingRoot->is_leaf())
				{
					decodedfile << workingRoot->letter;
					break;
				}
				else
				{
					encodedfile.get(c);
					workingRoot = c == '0' ? workingRoot->left : workingRoot->right;
				}
			}			
		}
	}
	else 
	{
		cout << "output decoded file cannot be opened!\n";
		encodedfile.close();
		return 0;
	}

	// Close the input and output files for decoding
	encodedfile.close();
	decodedfile.close();

	//---------------------------------------------------------------------
	//  TODO: Delete all the node objects    
	// ------
	// 	Please call clean(root), where root is the root node of the huffman tree

	clean(root);
    
	return 0;
}
