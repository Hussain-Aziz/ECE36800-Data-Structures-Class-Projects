// Please add your name below
// Name: Hussain Aziz Saif
//
// FILE: huffman3.cpp
// This file implements Huffman coding and decoding.

#include <fstream>
#include <list>
#include <string>
#include <cassert>
#include <cctype>
#include <stack>
#include <map>
#include <sys/stat.h>
#include <bitset>
#include "node.h"

int main()
{
//////////////////////   Read ProbabilcharKeyy Data   /////////////////////

	//open input text file for reading
	string textfilename = "input.txt";
	ifstream textfile;
	textfile.open(textfilename.c_str(), ifstream::in);
	assert(textfile);

	// Read in all letters in the file, store them in a dictionary
	// where key is the letter and the value is the count
	// so we can find the probability of each occuring in the input
	map<char, int> charCounter;
	int totalChars = 0;
	for (unsigned int n = 0; !textfile.eof(); n++)
	{
		char c;
		textfile.get(c);

		//if found add to counter
		if (charCounter.find(c) != charCounter.end())
		{
			charCounter[c] = charCounter[c] + 1;
		}
		else
		{
			//create new entry in dictionary
			charCounter[c] = 1;
		}
		totalChars++;
	}

	// add the letters as a node .first returns the letter and .second returns the 
	// count of the char. we divide that by total letters to get probability
	list<node*> node_list;
	for(auto i = charCounter.begin(); i != charCounter.end(); i++)
	{
		node_list.push_back(new node((*i).first, (*i).second/(double)totalChars));
	}
	
///////////////////   Construct Huffman Coding Tree ////////////////////

	while (node_list.size() > 1) 
	{		
		node_list.sort(comp_prob);

		node* firstSmallest = *(node_list.begin());
		node* secondSmallest = *(++node_list.begin());

		node_list.remove(firstSmallest);
		node_list.remove(secondSmallest);

		node* newNode = new node(firstSmallest, secondSmallest);

		node_list.push_back(newNode);
	}
		
///////////////////   Generate Huffman Codes ////////////////////////

	// a dictionary to store the letter as key and the huffman code as the value
	map<char, string> codeArray;

	node* root = *(node_list.begin()); // garunteed to be root because in previous while loop we looped until size == 1
	root->code = "";

	//visit all node to add codes using pre order traversal
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
			codeArray[left->letter] = (left->code);
		}
		else
		{
			nodeToVisit.push(left);
		}
		
		if(right->is_leaf())
		{
			codeArray[right->letter] = (right->code);
		}
		else
		{
			nodeToVisit.push(right);
		}
	}

	//print out all the codes
	for(auto i = codeArray.begin(); i != codeArray.end(); i++)
	{
		std::cout << (*i).first << ": " << (*i).second  << endl;
	}
	
/////////////////////////   Encode Input File   ////////////////////////////////

	// go back to first line of text file
	textfile.close();
	textfile.open(textfilename.c_str(), ifstream::in);

	// Open the file for writing encoded text
	string encodedfilename = "encoded.txt";
	fstream encodedfile;
	encodedfile.open(encodedfilename.c_str(), ios::out | ios::binary);
	assert(encodedfile);

	if (encodedfile.is_open())
	{
		// Input and encode each character from the input file one by one
		// and output them to the output file

		char d = 0x0; //the char that will act as a byte and we will add our code but by bit to it
		int bitsOccupied = 0; //we use this to count how many bits are occupied in d, if its 8 we write and reset	

		while (!textfile.eof()) 
		{
			// Read the character
			char c;
			textfile.get(c);   
			string s = codeArray[c];
			
			//convert the code string to binary string
			for (size_t i = 0; i < s.length(); i++)  
			{ 
				//shift everything to the left and binary or to add 0 or 1 to the right
				d = (d << 1) | (s[i] == '0' ? 0 : 1);

				bitsOccupied++;

				if (bitsOccupied == 8)
				{
					//write our finished 1 byte to  file and reset
					encodedfile.write(new char(d), 1);
					bitsOccupied = 0;
					d = 0x0;
				}
			}
		}
	} 
	else
	{
		std::cout << "Error: output file cannot be opened!\n";
		textfile.close();
		return 0;
	}

	// Close the text file
	textfile.close();

//////////////////////// Decode the Encoded File ///////////////////////////

	// Reset the encoded text file for readings
	encodedfile.close();
	encodedfile.open(encodedfilename.c_str(), ios::in | ios::binary);

	// Open the file for wrcharKeying decoded text
	string decodedfilename = "decoded.txt";
	ofstream decodedfile;
	decodedfile.open(decodedfilename.c_str(), ofstream::out);

	assert(decodedfile);


	if (decodedfile.is_open())
	{
		//get the full code in a string variable
		string huffmanCodes = "";

		// get the size of the input file in bytes and put it into the buffer
		struct stat results; 
		char* buffer; 
		int size = 0;
		if (stat(encodedfilename.c_str(), &results) == 0)
		{ 
			size = results.st_size;  
			buffer = new char(size); 
			encodedfile.read(buffer, size); // read from a file 
		} 
		else
		{
			std::cout << "an error occured while reading encoded file \n stopping program";
			encodedfile.close();
			decodedfile.close();
			return 0;
		}

		for(int i = 0; i < size - 1; i++)
		{
			//we need to cast to unsigned char because using char could give 
			//us a negative value which wont get converted properly to a bit string
			unsigned char x = (unsigned char) buffer[i];
			huffmanCodes += std::bitset<8>(x).to_string();
		}

		//now we have the full code we can use this var to see where we are in the code
		size_t stringIndex = 0;

		while(stringIndex < huffmanCodes.length())
		{
			char c = huffmanCodes[stringIndex];
			stringIndex++;
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
					c = huffmanCodes[stringIndex];
					stringIndex++;
					workingRoot = c == '0' ? workingRoot->left : workingRoot->right;
				}
			}		
		}          	
	}
	else 
	{
		std::cout << "output decoded file cannot be opened!\n";
		encodedfile.close();
		return 0;
	}

	// Close the input and output files for decoding
	encodedfile.close();
	decodedfile.close();

	clean(root);
    
	return 0;
}
