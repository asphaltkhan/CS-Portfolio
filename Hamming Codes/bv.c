#include "bv.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// provided by Darrell Long used to calulate number of bytes needed for x bits
#define byte_length(x) ((x / 8) + !!(x % 8))

struct BitVector { // provided on Lab pdf
    uint32_t length;
    uint8_t *vector;
};

//
// this function takes care of creating the BitVector ADT
//
BitVector *bv_create(uint32_t length) {
    BitVector *v = calloc(1, sizeof(BitVector)); // memory allocated for 1 BitVector
    if (v) {
        v->length = length; // vector length is equal to user defined bit length
        v->vector = calloc(byte_length(length), sizeof(uint8_t)); // allocated space per byte
    }
    return v;
}

// function reposnible for deleting and freeing memory and the stack ptr
void bv_delete(BitVector **v) {
    free((*v)->vector); // vector memory is freed
    free(*v); // adt pointer is freed
    v = NULL; // ptr is set to NULL
    return;
}

// returns the length of th bitvector
uint32_t bv_length(BitVector *v) {
    return v->length; // simply return the length
}

// sets bitvector at ith position to 1 (Eugene lab section)
void bv_set_bit(BitVector *v, uint32_t i) {
    // vector at i/8 th byte is bitwise or with 1 logical shifted left i % 8
    v->vector[i / 8] |= (0x1 << (i % 8));
}

// sets bitvector at ith position to 0
void bv_clr_bit(BitVector *v, uint32_t i) {
    // vector at i/8 th byte is bitwise anded with the complement of 1 logical shifted left
    v->vector[i / 8] &= ~(0x1 << (i % 8));
}

// return the the bit at the ith position either 1 or 0
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    // bit is shifted all the way to the right and anded with a 1 to return value
    return (v->vector[i / 8] >> (i % 8) & 0x1);
}

// xors the specific bit and the ith value
void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    // vector at 1/8 the byte is xor with the bit offset i % 8 to the left
    v->vector[i / 8] ^= (bit << (i % 8));
}

// print function
void bv_print(BitVector *v) {
    for (uint32_t i = v->length; i > 0; i -= 1) {
        printf("%c", bv_get_bit(v, i));
    }
    printf("\n");
}
