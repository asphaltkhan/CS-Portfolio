#include "hamming.h"

#include "bm.h"
#include "helper.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

uint32_t total_bytes = 0; // extern variable to count the total bytes decoded
uint32_t uncorrected_errors = 0; // extern variable to count the uncorrected errors
uint32_t corrected_errors = 0; // extern variable to count the corrected errors

// function to grab the lower nibble of a byte (from lab pdf - Darrell Long)
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

//
// the following function is the main logic behind the encoding process of each nibble
// this function will return an encoded character of 8 bytes.
// part pseudo from Eric ta
//
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *matrix_data = bm_from_data(msg, 4); // create a 1x4 matrix with nibble of msg
    BitMatrix *matrix_ptr = bm_multiply(matrix_data, G); // multiply and encode it with matrix G
    msg = bm_to_data(matrix_ptr); // convert matrix to data and pass to msg
    bm_delete(&matrix_data); // free 1x4 matrix
    bm_delete(&matrix_ptr); // free multiplied matrix
    return msg; // return msg
}

//
// the following function is the logic behind the hammong decode process
// the function takes the encoded matrix and check is the msg bits have an error
// if the error is solvable then it is fixed and returned
// adapted from Eric ta pseudocode
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    total_bytes += 1; // increment byte counter
    // this is the hard coded look up table used to check for possible errors and it location
    // since there are only 16 possible values for a nibble, all possibilities are coded
    uint32_t lookup_table[16] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR,
        HAM_ERR, 2, HAM_ERR, 1, 0, HAM_ERR };
    BitMatrix *matrix_data = bm_from_data(code, 8); // code is converted into a 1x8 matrix
    BitMatrix *matrix_err = bm_multiply(matrix_data, Ht); // multiplied with the transpose H
    uint8_t tem = bm_to_data(matrix_err); // the matrix is converted back to a data value
    bm_delete(&matrix_data); // free code converted matrix
    bm_delete(&matrix_err); // free multiplied matrix
    int32_t look = lookup_table[tem]; // look up data value in table and return results
    if (look == HAM_OK) { // if no errors
        *msg = lower_nibble(code); // return lower nibble of code in msg
        return HAM_OK; // return enum value for no erros
    } else if (look >= 0) { // if error position is returned
        corrected_errors += 1; // increment corrected error counter
        // xor to flip the bit at corresponding position and return lower nibble to msg
        *msg = lower_nibble(code ^ (1 << look));
        return HAM_CORRECT; // return enum value for corrected error
    } else { // if uncorrectable error
        uncorrected_errors += 1; // increment uncorrected error
        return HAM_ERR; // leave code untouched and return the enum value ofr uncorrectable error
    }
}
