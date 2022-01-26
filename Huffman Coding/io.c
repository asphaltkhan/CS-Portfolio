#include "io.h"

#include "defines.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// extern vars for collecting program stats
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

// static buffer and index defined for read_bit and write_bytes function
static uint8_t buffer[BLOCK] = { 0 };
static uint64_t buf_index = 0;
static uint64_t end = 0; // used to determine the end of the bits in the buffer

// this function is reponsible for reading the bytes from a file and storing them in a buffer
// its passed the infile int fd along with the buffer and number of bytes to read
// code written inspired from Eugene and Eric pseudocode
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int64_t total = 0; // total number of bytes read
    int64_t bytes = 0; // number of bytes read in one call to read
    while ((bytes = read(infile, buf, nbytes - bytes)) != 0) { // while there are bytes to read
        if (bytes == -1) { // if there is an error returned return total and exit
            return total;
        }
        total += bytes; // total number of bytes added
        bytes_read += bytes; // total bytes for extern var statistics
        buf += bytes; // increment the ofset of buffer
        if (total == nbytes) { // if number of bytes to read is equal to total read
            return total; // return total read
        }
    }
    return total; // return total
}

// the following function is responsible for writing the bytes read into the buffer
// function is passed the int fd for outfile as well as the filled buffer and number of bytes
// to right out - code written inspired from Eugene and Eric pseudocode
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int64_t total = 0; // total number of bytes written
    int64_t bytes = 0; // number of bytes written on one call of write
    while ((bytes = write(outfile, buf, nbytes - bytes)) != 0) { // while there are bytes to write
        if (bytes == -1) { // if error returned, return bytes written so far
            return total;
        }
        total += bytes; // increment total bytes written so far
        bytes_written += bytes; // extern var for total bytes written
        buf += bytes; // offset buffer
        if (total == nbytes) { // if total bytes written equal number of bytes needed to write
            return total; // return total
        }
    }
    return total; // return total
}

// the function reads one bit at a time from an out file
// returns true of bits still exist to be read, false otherwise
// written on my own but checked against Eugene pseudocode
bool read_bit(int infile, uint8_t *bit) {

    if (buf_index == 0 || buf_index == (BLOCK * 8)) { // if index is at start or end
        buf_index = 0; // reset index
        int byte = read_bytes(infile, buffer, BLOCK); // read BLOCK number of bytes
        if (byte < BLOCK) { // if number of bytes read is less than BLOCK
            end = byte * 8 + 1; // the last byte is at index byte * 8 + 1
        }
    }
    *bit = (buffer[buf_index / 8] >> (buf_index % 8) & 0x1); // pass the value at index to bit
    buf_index += 1; // increase index
    if (buf_index == (end)) { // if end of is reached
        return false; // no more bits to read
    }
    return true; // else return true (bits left to read)
}

// the function is tasked with writing the code for each byte out to the file
// it is passed the outfile int fd as well as the code
// Eugene pseudo code used
void write_code(int outfile, Code *c) {
    for (uint64_t i = 0; i < c->top; i++) { // index through the bits in code
        if (((c->bits[i / 8] >> (i % 8) & 0x1)) == 1) { // if the bit is a 1 at the index
            buffer[buf_index / 8] |= (0x1 << (buf_index % 8)); // set 1 at buff index
        } else { // else if bit is a 0
            buffer[buf_index / 8] &= ~(0x1 << (buf_index % 8)); // clear bit at buff index
        }
        buf_index += 1; // increment buf index
        if (buf_index == BLOCK * 8) { // if the index reaches the end of the buffer
            write_bytes(outfile, buffer, BLOCK); // the buffer is filled and should be written out
            buf_index = 0; // reset index back to 0
        }
    }
    //write_bytes(outfile, buffer, BLOCK);
    return;
}

// this function handles any bits that were left in the buffer after write code
// this happens when the bits do not fill the buffer completely at the last pass
void flush_codes(int outfile) {
    if (buf_index > 0) { // if bits exist in buffer
        // write out remaining bytes (# bytes neede taken from asgn5)
        write_bytes(outfile, buffer, ((buf_index / 8) + !!(buf_index % 8)));
    }
    return;
}
