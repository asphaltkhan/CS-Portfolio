//Filename: bst.h
//
// Header file for the BST class
//
// Afzal Khan, November 8 2021

#ifndef BST_H
#define BST_H

#include <string>

using namespace std;

class Node {
	public:
		string key; // the key of the node
		int balanceFactor; // balance factor variable
		int subSize; // the node subtree size
		//int height;
		Node *left, *right, *parent; // nodes child, parent
		
		Node() {
			left = right = parent = NULL; // set nodes children and parent to NULL
			balanceFactor = 1; // initialize balanceFactor with 1
			subSize = 1; // initialize subSize with 1
			//height = 1;
		}
	
		Node(string val) { // for Node initialize with value 
			key = val; // set key to the val
			balanceFactor = 1; // initialize balanceFactor with 1
			subSize = 1; // initialize subSize with 1
			//height = 1;
			left = right = parent = NULL; // set the children and parent to NULL
		}
};

class BST {
	private:
		Node *root; // BST has node 
		int nodeCount; // counter for the range function
	public:
		BST(); // constructor
		int height(Node*); // get height of the node
		int get_balance(Node*); ; // gets balance factor of the node
	
		void insert(string); // insert wrapper
		Node* AVLinsert(Node*, string); // inserts into AVL tree
		
		Node* rightRotate(Node*); // rotating the AVL tree right
		Node* leftRotate(Node*); // rotating the AVL tree left
		
		int rangeAVL(string, string); // range function 
		void leftTraverse(Node*, string, string); // used in range for traversing left side of tree
		void rightTraverse(Node*, string, string); // used in raneg for traversing right side of the tree
	
		Node* find(string); 
		Node* find(Node*, string);

		void deleteBST();
		void deleteBST(Node* start);

		string printPreOrder();
		string printPreOrder(Node* start);

	
		void print_tree();
		void print_tree(Node*, int); // miles 
	
		Node* lca(string, string); // lca wrapper function
		Node* lca(Node*, string, string); // used to find the least common ancestor of two strings
	
// 		int range(string, string);
// 		int range (Node*, string, string);
	
// 		int rangeAVL(string, string);
// 		void rangeAVL(Node*, string, string);
};

#endif