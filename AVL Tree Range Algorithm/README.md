### Basic Discription:
These folders contain the files to both populate an AVL tree and find the number of nodes that 
lie within a certain range. The input file provides thousands of nodes to populate the tree. The 
AVL tree wil be able to balance itself and find the nodes within a specified range quickly.

## Files:
The Wordrange folder contains:
Code Files: wordrange.cpp bst.cpp bst.h
I/O Files: Under folder Tests
Makefile
Pseudo Code File: Scratchpad.pdf

## Usage:
In Wordrange folder:
- run 'make'
- ./wordrange <INPUT_FILE> <OUTPUT_FILE>

## Input/Output:
The input file has the letter 'i' do denote that the following value separated by a sapce must be 
added to the AVL tree. The letter 'r' denotes that the two values follwoing are the upper and lower
range bound respectively.

## Sources:
Understanding the AVL tree and balancing: https://www.codesdope.com/course/data-structures-avl-trees/
										  https://www.cise.ufl.edu/~nemo/cop3530/AVL-Tree-Rotations.pdf
										  https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
										  https://youtu.be/jDM6_TnYIqE (Abdul Bari)
										  https://en.wikipedia.org/wiki/AVL_tree
										  https://stackoverflow.com/questions/575772/the-best-way-to-calculate-the-height-in-a-binary-search-tree-balancing-an-avl
										  https://stackoverflow.com/questions/19211692/understanding-balance-factors-node-height-for-avl-rotations
										  
## Range function 
			   http://www.cs.utah.edu/~lifeifei/cis5930/kdtree.pdf (Paper by Hemant M. Kakde)
			   https://stackoverflow.com/questions/37010021/count-number-of-nodes-within-range-inside-binary-search-tree-in-ologn
