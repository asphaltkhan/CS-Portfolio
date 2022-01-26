// Filename: bst.cpp
//
// Contains the actual implementation of the BST data structure
//
// Afzal Khan, November 8, 2021

#include "bst.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

BST :: BST() {
	root = NULL;
	nodeCount = 0;
}

// function is used to return theheight of the given node
int BST :: height(Node* start) {
	if (start == NULL) {
		return 0;
	}
	
	return start->balanceFactor;
	//return max(height(start->left), height(start->right)) + 1;
}

// this function returns the balance of the node using the node property balanceFactor
int BST :: get_balance(Node* node) {
	if (node->left != NULL && node->right != NULL) { // if there exists in bothe left and right branches
		return node->left->balanceFactor - node->right->balanceFactor; // subtract the heights for the balance factor and return 
	} else if (node->left != NULL && node->right == NULL) { // if only the left branch exists return the left branches height 
		return node->left->balanceFactor; // return the left nodes height
	} else if (node->left == NULL && node->right != NULL) { // if only the right branch exists 
		return node->right->balanceFactor * -1; // return the right nodes height and multiply -1 since equation is (left height - right height)
	}
	return 0;
}

// wrapper class for the insert function of the VAL tree
void BST :: insert(string new_string) {
	root = AVLinsert(root, new_string);
}

// thsi function is for inserting a new node into the balanced AVL tree
// adapted from the geeksforgeeks implementation : geeksforgeeks avl insertion (30+ min was given before implementation myself)
Node* BST :: AVLinsert(Node* start, string to_insert) {
	// base case if we reach the end of the tree
	if (start == NULL) {
		return new Node(to_insert); // insert a new node 
	}
	
	if (to_insert < start->key) { // if less than current node 
		start->left = AVLinsert(start->left, to_insert); // recursively call down the left branch
	} else if (to_insert > start->key) { // if greater than current node 
		start->right = AVLinsert(start->right, to_insert); // recursively call down the right branch 
	}
	
	start->balanceFactor = max(height(start->left), height(start->right)) + 1; // find the max height of either child and add one to include current level
	
	// calculates the size of the sub tree at the root
	if ((start->left != NULL) && (start->right != NULL)) {
		 start->subSize = start->left->subSize + start->right->subSize + 1; // if both nodes exist, add left subtree and right subtree and add 1 for the node itself
	} else if ((start->left == NULL) && (start->right != NULL)) { // if only right branch exists
		start->subSize = start->right->subSize + 1; // add right node size plus 1 for the node itself
	} else if ((start->left != NULL) && (start->right == NULL)) { // if only left branch exists
		start->subSize = start->left->subSize + 1; // add left node size plus 1 for node itself
	} else if ((start->left == NULL) && (start->right == NULL)) { // if none of the branches exists
		start->subSize = 1; // only add one for the node itself
	}
	
	
	if (get_balance(start) > 1 && to_insert < start->left->key) { // if unbalanced (left heavy) and key to insert is less than the roots left subtree (three nodes are inline)
		return rightRotate(start); // rotate the right two nodes including the start node
	} 
	if (get_balance(start) < -1 && to_insert > start->right->key) { // if unbalanced (right heavy) and key to insert is less than the roots rights subtree
		return leftRotate(start); // rotate the left two nodes including the start node
	}
	if (get_balance(start) > 1 && to_insert > start->left->key) { // if ubalanced (left heavy) and the key to insert is greater than the roots left child (three nodes are staggered on left)
		start->left = leftRotate(start->left); // first do a left rotate for the nodes not including the root
		return rightRotate(start); // then rotate the root along with the new left child
	}
	if (get_balance(start) < -1 && to_insert< start->right->key) { // if unbalanced (right heavy) and the key to insert is less than the roots right child (three nodes are staggered on the right)
		start->right = rightRotate(start->right); // first do a right rotate for the nodes not including the root 
		return leftRotate(start); // then rotate the root along with the new right child
	}
	
	return start; // return the root node
} 

// this function is for roatating the nodes anchored at some node start right
// this function was adapted from the geeksforgeeks, abdul bari, stackoverflow implementation (30+ min was given before implementation myself)
Node* BST :: rightRotate(Node* start) {
	Node* temp1 = start->left; // temp node is equal to left node 
	Node* temp2 = temp1->right; // temp2 node is equal to the start nodes -> left childs -> right node 
	
	// swaps the two nodes on the left of the root 
	temp1->right = start; // swap the nodes
	start->left = temp2; // swap the nodes 
	
	// recalculates the heights after swapping the nodes
	start->balanceFactor = max(height(start->left), height(start->right)) + 1; // the height of a node is the max of the left and right tree heights (add one to include self)
	temp1->balanceFactor = max(height(temp1->left), height(temp1->right)) + 1; // the height of a node is the max of the left and right tree heights (add one to include self)
	
	// recalculates the size of the subtrees with the new root
	if ((start->left != NULL) && (start->right != NULL)) { // if both branches exists
		 start->subSize = start->left->subSize + start->right->subSize + 1;
	} else if ((start->left == NULL) && (start->right != NULL)) { // if only the right side exists
		start->subSize = start->right->subSize + 1;
	} else if ((start->left != NULL) && (start->right == NULL)) { // if only the left side is exists
		start->subSize = start->left->subSize + 1;
	} else if ((start->left == NULL) && (start->right == NULL)) { // if both dont exist
		start->subSize = 1;
	}
	
	// recalculates the size of the subtree with new swapped nodes
	if ((temp1->left != NULL) && (temp1->right != NULL)) { // if both bracnhes exist
		 temp1->subSize = temp1->left->subSize + temp1->right->subSize + 1;
	} else if ((temp1->left == NULL) && (temp1->right != NULL)) { // if only the right side exists
		temp1->subSize = temp1->right->subSize + 1;
	} else if ((temp1->left != NULL) && (temp1->right == NULL)) { // if only the left side exists
		temp1->subSize = temp1->left->subSize + 1;
	} else if ((temp1->left == NULL) && (temp1->right == NULL)) { // if both branches dont exist
		temp1->subSize = 1;
	}
	
	// set the left node of the original root as the new root 
	temp1->parent = start->parent; // make the new roots parent the old roots parent
	start->parent = temp1; // the old roots parent is now the new root
	return temp1; // return the new root 
}

// this function if for rotating the nodes anchored at some node start left
// this function was adapted from the geeksforgeeks, abdul bari, stackoverflow implementation (30+ min was given before implementation myself)
Node* BST :: leftRotate(Node* start) {
	Node* temp1 = start->right; // temp node is equal to right node
	Node* temp2 = temp1->left; // temp2 node is equal to the start nodes right childs lef node
	
	// swap the nodes right of the root node with balance issue 
	temp1->left = start; // swap the nodes
	start->right = temp2; // swap the nodes
	
	// calculate the height of the rotated tree 
	start->balanceFactor = max(height(start->left), height(start->right)) + 1;
	temp1->balanceFactor = max(height(temp1->left), height(temp1->right)) + 1;
	
	// recalculates the size of the subtrees with the new root
	if ((start->left != NULL) && (start->right != NULL)) { // if both branches exists
		 start->subSize = start->left->subSize + start->right->subSize + 1;
	} else if ((start->left == NULL) && (start->right != NULL)) { // if only right side exists 
		start->subSize = start->right->subSize + 1;
	} else if ((start->left != NULL) && (start->right == NULL)) { // if only left side exists 
		start->subSize = start->left->subSize + 1;
	} else if ((start->left == NULL) && (start->right == NULL)) { // if both branches dont exist
		start->subSize = 1;
	}
	
	// recalculates the size of the subtree with new swapped nodes
	if ((temp1->left != NULL) && (temp1->right != NULL)) { // if both branches exists
		 temp1->subSize = temp1->left->subSize + temp1->right->subSize + 1;
	} else if ((temp1->left == NULL) && (temp1->right != NULL)) { // if only the right branch exists
		temp1->subSize = temp1->right->subSize + 1;
	} else if ((temp1->left != NULL) && (temp1->right == NULL)) { // if only the left branch exists
		temp1->subSize = temp1->left->subSize + 1;
	} else if ((temp1->left == NULL) && (temp1->right == NULL)) { // if both branches dont exists
		temp1->subSize = 1;
	}
	
	// set the right node of the original root to the new root 
	temp1->parent = start->parent; // make new roots parent the old roots parent 
	start->parent = temp1; // make the old roots parent the new root
	return temp1; // return the new root
}

// the following function is for counting the number of nodes within some string range
// the implementation was developed after reading a paper by Hemant Kakde (pseudocode can be found in Wordrange folder under file name Scratchpad)
int BST :: rangeAVL(string str1, string str2) {
// 	if (str1 == str2) { // if both string ranges are the same 
// 		Node* check = lca(str1, str2);
		
// 	}
	
	nodeCount = 0; // initialize the count to 0
	Node* ancestor = lca(str1, str2); // find the lca of the two input strings 
	if (ancestor == NULL) { // if the lca cant find any common ancestor 
		return 0; // return 0
	}
	
	//cout << ancestor->key << " " << str1 << " : " << str2 << endl;
	if ((ancestor->right == NULL) && (ancestor->left == NULL)) { // if the ancestor does not have any left or right children
		nodeCount += 1; // add one to the count for that node
		return nodeCount; // return node count
	} else if (ancestor->left == NULL) { // if there is no left tree rooted at the ancestor 
		rightTraverse(ancestor->right, str1, str2); // only caluclate the nodecount for the right side
		nodeCount += 1; // add one for the ancestor node itself 
		return nodeCount; // return nodecount
	} else if (ancestor->right == NULL) { // if there is no right tree roooted at ancestor 
		leftTraverse(ancestor->left, str1, str2); // tarverse only on the left side to find ocunt
		nodeCount += 1; // add one for the ancestor node itself 
		return nodeCount; // return nodecount
	} else { // if there exists both a left and right side to teh tree at the ancestor node
		leftTraverse(ancestor->left, str1, str2); // traverse the left side of the tree
		rightTraverse(ancestor->right, str1, str2); // traverse the right side 
		nodeCount += 1; // add one for root node
		return nodeCount; // return the count 
	}
}

// this traverse compares each subtree node against str1 to determine the count total
void BST :: leftTraverse(Node* start, string str1, string str2) {
	if (start->key >= str1) { // if the current node is greater than or equal to str1 
		if (start->right != NULL) { // if there is a right subtree at start node
			nodeCount += start->right->subSize + 1; // ad right subtree size plus 1 for the start node itself 
		} else if (start->right == NULL) { // if the current node does not have a right subtree
			nodeCount += 1; // just add the current node 
		}
		
		if ((start->key == str1) || (start->left == NULL)) { // if we are at the lower range or we cant traverse further
			return; // just return 
		} else {
			leftTraverse(start->left, str1, str2); // otherwise continue down the left side
		}
	} else if (start->key < str1) { // if the current node is less than str1
		if (start->right == NULL) { // if the current node does not have a right subtree 
			return; // just return 
		} else {
			leftTraverse(start->right, str1, str2); // otherwise move one node to the right of current and continue keft again
		}
	}
}

// this traverse compares each subtree node against str2 to determine the count total
void BST :: rightTraverse(Node* start, string str1, string str2) {
	if (start->key <= str2) { // if the current node is greater than or equal to str2
		if (start->left != NULL) { // if there is a left subtree at the current node
			nodeCount += start->left->subSize + 1; // add the left subtree size pluys one for the node itself
		} else if (start->left == NULL) { // if the current node does not have a left side
			nodeCount += 1; // add one for the current node itself 
		}
		
		if ((start->key == str2) || (start->right == NULL)) { // if we are at the upper range or we cant traverse any further
			return; // just return 
		} else {
			rightTraverse(start->right, str1, str2); // otherwise continue down the right side
		}
	} else if (start->key > str2) { // if the current node is greater than the upper range
		if (start->left == NULL) { // if the current node does not have a left subtree
			return; // just return 
		} else {
			rightTraverse(start->left, str1, str2); // otherwise go to the current nodes left subtree and continue traversing right 
		}
	}
}

// this function is a wrapper for one that calculates the least common ancestor 
Node* BST :: lca(string val1, string val2) {
	return lca(root, val1, val2);
}

Node* BST :: lca(Node* start, string val1, string val2) {
	if (start == NULL) { // if start is NULL 
		return NULL; // return 
	}
	if ((start->key > val1) && (start->key > val2)) { // if the start nodes key is greater than both nodes
		return lca(start->left, val1, val2); // traverse left
	} else if ((start->key < val1) && (start->key < val2)) { // if the start nodes key is greater than both nodes 
		return lca(start->right, val1, val2); // traverse right
	} else {
		return start; // otherwise just return node itself
	}
}
//-------------------------------------------------------------
// void BST :: insert(string val) {
// 	if (!find(val)) {
// 		Node *to_insert = new Node(val);
// 		if (root == NULL) {
// 			root = to_insert;
// 			root->subSize += 1;
// 			//root->balanceFactor = height(root->left) - height(root->right);
// 		} else {
// 			insert(root, to_insert);
// 		}
// 	}
// }

// void BST :: insert(Node* start, Node* to_insert) {
// 	if (start == NULL) {
// 		return;
// 	}
// 	if (start->balanceFactor > 1 && to_insert->key < start->left->key) {
// 		cout << "here" << endl;
// 		start = rr(start);
// 		return;
// 	}
// 	if (to_insert->key <= start->key) {
// 		if (start->left == NULL) {
// 			start->subSize += 1;
// 			start->left = to_insert;
// 			start->balanceFactor = height(start->left) - height(start->right);
// 			start->left->subSize += 1;
// 			to_insert->parent = start;
// 			if (start->balanceFactor > 1 && to_insert->key < start->left->key) {
// 				cout << "here" << endl;
// 				start = rr(start);
// 				return;
// 			}
// 			return;
// 		} else {
// 			start->subSize += 1;
// 			insert(start->left, to_insert);
// 			start->balanceFactor = height(start->left) - height(start->right);
// 			return;
// 		}
// 	 } else {
// 		if (start->right == NULL) {
// 			start->subSize += 1;
// 			start->right = to_insert;
// 			start->balanceFactor = height(start->left) - height(start->right);
// 			start->right->subSize += 1;
// 			to_insert->parent = start;
// 			return;
// 		} else {
// 			start->subSize += 1;
// 			insert(start->right, to_insert);
// 			start->balanceFactor = height(start->left) - height(start->right);
// 			return;
// 		}
// 	}
// 	cout << "here" << endl;
// }

Node* BST :: find(string val) {
	return find(root, val);
}

Node* BST :: find(Node* start, string val) {
	if (start == NULL || start->key == val)
		return start;
	if (val < start->key)
		return find(start->left, val);
	else 
		return find(start->right, val);
}

void BST :: deleteBST() {
	deleteBST(root);
}

void BST :: deleteBST(Node* start) {
	if (start == NULL)
		return;
	deleteBST(start->left);
	deleteBST(start->right);
	delete(start);
}

string BST :: printPreOrder() {
	return printPreOrder(root);
}

string BST :: printPreOrder(Node* start) {
	if (start == NULL) {
		return "";
	}
	string leftpart = printPreOrder(start->left);
	string rightpart = printPreOrder(start->right);
	string output = "(" + start->key + ": BF " + to_string(start->balanceFactor) + " SS: " + to_string(start->subSize) + ")";
	if (leftpart.length() != 0)
		output = output + " " + leftpart;
	if (rightpart.length() != 0)
		output = output + " " + rightpart;
	return output;
}


// Node* BST :: lca(Node* start, string val1, string val2) {
// 	if (start == NULL) {
// 		return NULL;
// 	}
	
// 	lca(start->left, val1, val2);
// 	lca(start->right, val1, val2);
	
// 	if (find(start, val1)) {
// 		if (find(start, val2)) {
// 			if (lcaStore == NULL) {
// 				lcaStore = start;
// 			}
// 		}
// 	}
// 	return lcaStore;
// }

// int BST :: range(string str1, string str2) {
// 	rangeCount = 0;
// 	return range(root, str1, str2);
// }

// int BST :: range(Node* start, string str1, string str2) {
// 	if (start == NULL) {
// 		return 0;
// 	}
// 	range(start->left, str1, str2);
// 	range(start->right, str1, str2);
	
// 	if ((start->key >= str1) && (start->key <= str2)) {
// 		//cout << start->key << endl;
// 		rangeCount += 1;
// 	}
	
// 	return rangeCount;
// }

void BST :: print_tree() {
	print_tree(root, 0);
}

// void BST :: print_tree(Node* start, int depth) {
// 	if (start) {
// 		print_tree(start->right, depth + 1);
		
// 		for (int i = 0; i < depth; i++) {
// 			cout << "    ";
// 		}
// 		cout << start->key << endl;
// 		//cout << " " * depth << start->key << " : " << start->balanceFactor << endl;
		
// 		print_tree(start->left, depth + 1);
// 	}
// }

// helps with visualizing the tree 
void BST :: print_tree(Node* start, int depth) { // Anurag Agarwal - stackoverflow.com/questions/4965335/how-to-print-binary-tree-diagram-in-java/42449385#42449385
	if (start == NULL) {
		return;
	}
	
	print_tree(start->right, depth + 1);
	
	if (depth != 0) {
		for (int i = 0; i < depth - 1; i++) {
			cout << "|\t";
		}
		cout << "|-------" << start->key << endl;
			
	} else {
		cout << start->key << endl; 
	}
	
	print_tree(start->left, depth + 1);
}

// int BST :: rangeAVL(string str1, string str2) {
// 	count = 0;
// 	rangeAVL(root, str1, str2);
// 	return count;
// }

// void BST :: rangeAVL(Node* start, string str1, string str2) {
// 	if (start == NULL) {
// 		return;
// 	}
// 	cout << start->key << endl;
// 	if(start->key <= str1) {
// 		if (start->key == str1) {
// 			if (start->left != NULL) {
// 				count += start->left->subSize;
// 				rangeAVL(start->right, str1, str2);
// 				return;
// 			} else {
// 				return;
// 			}
// 		} else {
// 			if (start->left != NULL) {
// 				count += start->left->subSize + 1;
// 				rangeAVL(start->right, str1, str2);
// 				return;
// 			} else {
// 				return;
// 			}
// 		}
// 	} else if (start->key >= str2) {
// 		//cout << start->key << endl;
// 		if (start->key == str2) {
// 			if (start->right != NULL) {				
// 				count += start->right->subSize;
// 				rangeAVL(start->left, str1, str2);
// 				return;
// 			} else {
// 				cout << start->key << endl;
// 				return;
// 			}
// 		} else {
// 			if (start->right != NULL) {
// 				count += start->right->subSize + 1;
// 				rangeAVL(start->left, str1, str2);
// 				return;
// 			} else {
// 				return;
// 			}
// 		}
// 	}
// }
