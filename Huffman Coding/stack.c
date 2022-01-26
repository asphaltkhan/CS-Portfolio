#include "stack.h"

#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

// stack is initialized
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); // memory is allocated for the stack
    if (s) {
        s->top = 0; // top of the stack started off at 0
        s->capacity = capacity; // capacity of stack is passed in param
        s->items = calloc(capacity, sizeof(Node *)); // capacity of Node is allocated
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// sourced from Darrell Long
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// function checks if stack is empty
bool stack_empty(Stack *s) {
    return s->top == 0; // returns if top pointer is at 0
}

// function checks if stack is full
bool stack_full(Stack *s) {
    return s->top == s->capacity; // checks if top pointer is equal to capacity
}

// function returns the size of the stack
uint32_t stack_size(Stack *s) {
    return s->top; // return the top of the pointer
}

// function pushes node unto the stack
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) { // checks if there is room on stack
        return false;
    }
    s->items[s->top] = n; // value of location where top is pointing to is node
    s->top += 1; // increment the top pointer
    return true; // return true for success
}

// function pops node of the stack
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) { // checks if stack is empty
        return false;
    }
    s->top -= 1; // top is decremented so it points to value
    *n = s->items[s->top]; // pointer to node is set to the value at top
    return true; // return true for success
}

// prints stack for debugging
void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i++) {
        node_print(s->items[i]);
    }
    return;
}
