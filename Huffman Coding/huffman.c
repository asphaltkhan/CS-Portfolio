#include "huffman.h"

#include "defines.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//static Code c = {0, {0}};

// function is responsible for building the tree from the histogram of file data
// pseudo code of Eugene used
Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *pq = pq_create(ALPHABET); // pq is created
    for (uint64_t i = 0; i < ALPHABET; i++) { // looping through the elements of the histogram
        if (hist[i] > 0) { // if char occurs more than 0
            Node *a = node_create(i, hist[i]); // create a node for the char
            enqueue(pq, a); // enqueue onto the pq
        }
    }
    while (pq_size(pq) >= 2) { // while there are more than nodes on pw
        Node *left;
        dequeue(pq, &left); // dequeue left node
        Node *right;
        dequeue(pq, &right); // dequeue right node
        Node *j = node_join(left, right); // join the two nodes
        enqueue(pq, j); // enqueue the parent node
    }

    assert(pq_size(pq) == 1); // checks if there is only one node in the pq
    Node *root;
    dequeue(pq, &root); // this is the root node and is dequeued
    pq_delete(&pq); // delete the pq
    return root; // return the root node
}

// function is a subroutine for building the codes from the historgram
// tutor Eric's pseudocode was used
void build(Node *root, Code table[static ALPHABET], Code c) {
    uint8_t bit; // initialize a bit var
    if ((root->left == NULL) && (root->right == NULL)) { // if the nodes children are NULL
        table[root->symbol] = c; // add the built code to the table
    } else {
        if ((root->left) != NULL) { // if the left child is NULL
            code_push_bit(&c, 0); // add a 0 to the code
            build(root->left, table, c); // recursively call on current node
            code_pop_bit(&c, &bit); // pop the last bit added
        }
        if ((root->right) != NULL) { // if the right child is NULL
            code_push_bit(&c, 1); // add a 1 to the code
            build(root->right, table, c); // recursively call on current node
            code_pop_bit(&c, &bit); // pop last bit add to code
        }
    }
}

// main routine that calls build to help build codes
void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init(); // initialize a code adt
    build(root, table, c); // call build subroutine
}

// this function rebuilds the tree from the tree dump
// Eugene's pseudo code was used
Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s = stack_create(ALPHABET); // a stack is initialized
    for (uint16_t i = 0; i < nbytes; i++) { // loop from 0 to the size of tree dump
        if (tree[i] == 'L') { // if value at index is a 'L'
            Node *r = node_create(tree[i + 1], 0); // create a node with the char that follows
            stack_push(s, r); // push it to the stack
            i += 1; // skip the following char
        } else if (tree[i] == 'I') { // if the value at index is 'I'
            Node *right;
            stack_pop(s, &right); // pop the node from stack and make it right child
            Node *left;
            stack_pop(s, &left); // pop the node from stack and make it left child
            Node *joined = node_join(left, right); // join the two nodes to make a parent node
            stack_push(s, joined); // push the parent node onto the stack
        }
    }

    Node *root;
    stack_pop(s, &root); // last node on stack is root node
    stack_delete(&s); // delete the stack
    return root; // return the root node
}

// function takes care of deleting the tree
void delete_tree(Node **root) {
    if (*root) {
        delete_tree(&(*root)->left); // recursively call delete tree on nodes left child
        delete_tree(&(*root)->right); // recursively call delete tree on nodes right child
        node_delete(root);
    }
    return;
}
