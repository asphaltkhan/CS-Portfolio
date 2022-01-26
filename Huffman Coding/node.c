#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// initializes the node
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node)); // allocates memory for size of Node
    if (n) {
        n->symbol = symbol; // symbol of node is equalt to user inputted symbol
        n->frequency = frequency; // frequency of Node is equal to user defined freq
        n->left = NULL; // left child is NULL
        n->right = NULL; // right child is NULL
    }
    return n;
}

// deletes Node
void node_delete(Node **n) {
    free(*n); // frees pointer of node
    *n = NULL; // sets pointer to null
    return;
}

// this function joins two nodes to form a parent node
Node *node_join(Node *left, Node *right) {
    // new node is made with symbol '$' and the addition of children frequencies
    Node *new = node_create('$', (left->frequency + right->frequency));
    new->left = left; // parent nodes left is passed left
    new->right = right; // parent nodes right is passed right
    return new; // return the parent nodes
}

// prints node for debuging
void node_print(Node *n) {
    printf("%c %lu\n", n->symbol, n->frequency);
    return;
}
