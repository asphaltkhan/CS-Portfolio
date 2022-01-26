#include "code.h"

#include "defines.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Code code_init(void) {
    Code c; // code is initialized
    c.top = 0; // code top is set to 0
    for (uint64_t i = 0; i < MAX_CODE_SIZE; i++) { // iterate through code array set all bit to 0
        c.bits[i] = 0;
    }
    return c;
}

// function returns the top of the code
uint32_t code_size(Code *c) { // size of code is top pointer
    return c->top;
}

// returns bool value whether code is empty
bool code_empty(Code *c) {
    return c->top == 0; // checks if top pointer is 0
}

// returns bool value if code is full
bool code_full(Code *c) {
    return c->top == 256; // checks if top pointer is at max size
}

// pushed a bit onto the code
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) { // checks if code is full first
        return false; // if full return false
    }
    if (bit) { // if bit is a 1 push it onto code
        // Ors the bit at byte in code with 1
        c->bits[c->top / 8] |= (bit << (c->top % 8));
    }
    c->top += 1; // increment top
    return true; // return true for success
}

// pops bit of the top of code
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) { // checks if the code is empty
        return false; // if code is empty return false
    }
    c->top -= 1; // decrements the top pointer
    // sets bit equal to the bit right shifted and anded with 1
    *bit = (c->bits[c->top / 8] >> (c->top % 8) & 0x1);
    c->bits[c->top / 8] &= ~(0x1 << (c->top % 8)); // clears the bit after popping
    return true; // return true for success
}

// prints code in the array for debug
void code_print(Code *c) {
    for (uint64_t i = 0; i < ALPHABET; i++) {
        if ((i % 8) == 0) {
            printf(" ");
        }
        printf("%d", (c->bits[i / 8] >> (i % 8) & 0x1));
    }
    printf("\n");
    return;
}
