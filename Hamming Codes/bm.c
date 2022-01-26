#include "bm.h"

#include "bv.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct BitMatrix { // bitmatrix struct provided on the lab pdf
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

// this function is responsible for creating the Bit Matrix ADT
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = calloc(1, sizeof(BitMatrix)); // allocates memory for 1 bitmatrix
    if (m) {
        m->rows = rows; // matrix rows are equal to user defined row size
        m->cols = cols; // matrix columns are equal to user defined column size
        m->vector = bv_create(rows * cols); // create a bitvector adt
    }
    return m;
}

// this function is reposnible for deleting the bitmatrix
void bm_delete(BitMatrix **m) {
    bv_delete(&(*m)->vector); // deletes the bitvector as well
    free(*m); // free matrix pointer
    m = NULL; // sets ptr to NULL
    return;
}

// returns the number of rows in the bit matrix
uint32_t bm_rows(BitMatrix *m) {
    return m->rows; // returns rows
}

// returns the number of columns in the matrix
uint32_t bm_cols(BitMatrix *m) {
    return m->cols; // returns cols
}

// sets a bit within the bitmatrix to 1
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    // utilizes the bitvector function to set a bit
    // position of bit is calculated using the formula (r * # cols + current cols)
    bv_set_bit(m->vector, r * (m->cols) + c);
}

// clears the bit at specified position in the bitm,atrix
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    // utilizes the bitvector function for clearing a bit
    // position of bit is calculated using the formula (r * # cols + current cols)
    bv_clr_bit(m->vector, r * (m->cols) + c);
}

// returns the bit at the specified row and column
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    // uses the the get bit function of the bitvector adt
    // position of bit is calculated using the formula (r * # cols + current cols)
    return bv_get_bit(m->vector, r * (m->cols) + c);
}

// takes a uint8_t value and coverts into binary to put into a bitmatrix
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    assert((length == 4) || (length = 8));
    BitMatrix *t = bm_create(1, length); // creates a new bitmatrix to return
    for (uint32_t bit = 0; bit < length; bit += 1) { // loop through the size of the byte 4 or 8
        // shift the 1 to the left bit number of times and logical and the bits
        if (byte & (1 << bit)) {
            bm_set_bit(t, 0, bit); // if bit is a one at that position set to 1 on matrix
        }
    }
    return t; // return the matrix
}

// returns a uint8_ value from a bitmatrix representation (pseudo from Eric ta)
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t data = 0; // initialize arbitrary variable
    for (uint8_t i = 0; i < 8; i += 1) { // loop throught the 8 columns of the matrix
        if ((bm_get_bit(m, 0, i)) == 1) { // since its a 1x8 matrix if the value at ith bit is 1
            data = data | (1 << i); // bitwise or the the data with 1 logical shifted left (2^i)
        }
    }
    return data; // return the value
}

// returns a BitMatrix that is the result of matrix multiplication (pseudo from Eric ta)
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    // creates a matrix with A number of rows and B number of columns
    BitMatrix *C = bm_create(bm_rows(A), bm_cols(B));

    uint32_t prod = 0; // arbritrary value for product of two positions
    for (uint32_t i = 0; i < C->rows; i += 1) { // iterate tthrough the rows of C
        for (uint32_t j = 0; j < C->cols; j += 1) { // iterate through the columns of C
            for (uint32_t k = 0; k < bm_rows(B); k += 1) { // iterate through the rows of B
                // bitwise and the bits at position (i,k) of A and (k,j0 of B
                prod = bm_get_bit(A, i, k) & bm_get_bit(B, k, j);
                bv_xor_bit(C->vector, (i * (C->cols) + j), prod); // add result to the C matrix
            }
        }
    }
    return C; // return C
}

// this function prints out the matrix representation
void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < m->rows; i += 1) {
        for (uint32_t j = 0; j < m->cols; j += 1) {
            printf("%d ", bm_get_bit(m, i, j));
        }
        printf("\n");
    }
}
