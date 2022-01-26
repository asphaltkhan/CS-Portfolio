#include "pq.h"

#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct PriorityQueue {
    uint32_t capacity;
    uint32_t size;
    Node **arr;
    uint32_t head;
    uint32_t tail;
};

// Priority Queue is initialized
PriorityQueue *pq_create(uint32_t capacity) {
    // memory is allocated for the sizeof malloc
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity; // capacity if pq is user defined
        q->size = 0; // pq size is set to 0
        q->head = 0; // pq head is set to 0
        q->tail = 0; // pq tail is set to 0
        q->arr = calloc(capacity, sizeof(Node *)); // mem for an array of Nodes
    }
    return q;
}

// function for delting the pq
void pq_delete(PriorityQueue **q) {
    free((*q)->arr); // array of nodes is freed
    free(*q); // mem for pq is freed
    *q = NULL; // pointer is set to NULL
    return;
}

// function checks if pq is empty
bool pq_empty(PriorityQueue *q) {
    return q->tail == q->head; // queue is empty when both the tail and head are equal
}

// function checks if the pq is full
bool pq_full(PriorityQueue *q) {
    // checks if the index after the tail wrap saround to the head
    return ((q->tail + 1) % (q->capacity)) == q->head;
}

// functions returns the size of queue
uint32_t pq_size(PriorityQueue *q) {
    return q->size; // returns the value of size
}

// following function is reposnible for enqueueing the item in to the queue
// however unlike a traditional queue this enqueue uses a insertion sort to implement priority
bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) { // checks if pq is full
        return false; // returns false if full
    }
    q->size += 1; // pq size in incremented
    q->arr[q->tail] = n; // node is queued at the tail
    for (uint32_t i = 1; i < pq_size(q); i++) { // iterate through the nodes in the array
        uint32_t index = i; // create a var called index
        Node *node = q->arr[i]; // assign node with value at postion i
        // if the index is greater than zero and the node at i - 1 has a higher freq than node
        // at i, swap the nodes
        while (index > 0 && ((q->arr[index - 1]->frequency) > (node->frequency))) {
            q->arr[index] = q->arr[index - 1];
            index -= 1; // decrement the index to sift the node to its correct position
        }
        q->arr[index] = node; // og position is equla to the node
    }
    q->tail = (q->tail + 1) % (q->capacity); // increment the tail
    return true; // return true for success
}

// following function dequeues nodes form the queue
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) { // checks if queue is empty
        return false; // returns false if queue is empty
    }
    q->size -= 1; // decrease queue size
    *n = q->arr[q->head]; // retrn node at pointer head
    q->head = (q->head + 1) % (q->capacity); // increment head pointer
    return true; // return true for success
}

// print pq for debugging
void pq_print(PriorityQueue *q) {
    for (uint32_t i = q->head; i < q->tail; i++) {
        node_print(q->arr[i]);
    }
    return;
}
