// wrapper file for the AVL tree assignment- finds the number of nodes that fall within a certain range
//
// Usage : ./wordrange <INPUT_FILE> <OUTPUT_FILE>
//
// AFzal Khan November 13 2021
#include <iostream>
#include "bst.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;

int main(int argc, char** argv) {
	if (argc < 3) {
		throw std::invalid_argument("Usage: ./wordrange <INPUT_FILE> <OUTPUT_FILE>");
	}
	
	ifstream input; // stream for input file
	ofstream output; // stream for output file
	
	input.open(argv[1]); // open input file 
	output.open(argv[2]); // open outpput file 
	
	string command; // to store next command and operation 
	char *com, *valchar, *op; // for using with strtok and strtol
	string valstr; // stores the value read from file as string
	
	BST myBST; // create a BST
	
	while (getline(input, command)) { // get the lines from the input file 
		if (command.length() == 0) // if nothing is read 
			continue;
		com = strdup(command.c_str()); // copy string as a c style string
		op = strtok(com, " \t"); // tokenize by white space 
		
		valchar = strtok(NULL, " \t"); // the enxt thing read on the line is the actual node input 
		if (valchar != NULL) { // if it is not NULL
			valstr = valchar; // turn read input from char* to string
		}
		
		if (strcmp(op, "i") == 0) { // if command read is i
			//cout << "Insert " + valstr << endl;
			myBST.insert(valstr); // insert into AVL tree
		}
		
		if (strcmp(op, "f") == 0) { // if command read is f
			string message;
			if (myBST.find(valstr)) { // find string in BST
				message = " found";
			} else {
				message = " not found";
			}
			cout << valstr + message << endl;
			output << valstr + message << endl;
		}
		
		if (strcmp(op, "ppre") == 0) { // if command read is ppre
			output << myBST.printPreOrder() << endl; // do a pre order traversal
			//cout << "Print Pre order" << endl;
			//cout << myBST.printPreOrder() << endl;
			continue;
		}
		
		if (strcmp(op, "r") == 0) { // if command read is r
			char* valchar2 = strtok(NULL, " \t");
			string valstr2 = valchar2;
			
			//cout << "Range between " << valstr << " " << valstr2 << endl;
			output << myBST.rangeAVL(valstr, valstr2) << endl; // find the number of nodes between range
			//cout << myBST.rangeAVL(valstr, valstr2) << endl;
			continue;
		}
		
		if (strcmp(op, "print") == 0) { // if command read is print
			cout << "Tree Visual: " << endl;
			myBST.print_tree(); // prints out a tree visual to terminal 
			continue;
		}
	}
	
	input.close();
	output.close();
}