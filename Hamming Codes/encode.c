#include "bm.h"
#include "bv.h"
#include "hamming.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:" // encoding options

// Returns the lower nibble of val (provided in lab pdf - Darrell Long)
uint8_t lower_nibblenc(uint8_t val) {
    return val & 0xF;
}

// Returns the upper nibble of val (provided in lab pdf - Darrell Long)
uint8_t upper_nibblenc(uint8_t val) {
    return val >> 4;
}

// Packs two nibbles into a byte (provided in lab pdf - Darrell Long)
uint8_t pack_bytenc(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    FILE *infile = stdin, *outfile = stdout; // deafult read and write locations

    bool help_run = false; // help message flag

    int32_t choice = 0; // command line option var

    //
    // the following while loop is for the users selected command line options
    while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
        switch (choice) { // when switch is any value other than 0
        case 'h': help_run = true; break; // set a help flag and break
        case 'i':
            if ((infile = fopen(optarg, "rb")) == NULL) { // open infile to read
                fprintf(stderr, "Error: failed to open infile\n"); // if NULL return unable to open
                exit(1);
            }
            break;
        case 'o':
            if ((outfile = fopen(optarg, "wb")) == NULL) { // open outfile to write
                fprintf(stderr, "Error: failed to open outfile\n"); // NULL return unable to open
                exit(1);
            }
            break;
        default: // default case
            fprintf(outfile, "SYNOPSIS\n" // print help meesage
                             "  A Hamming(8, 4) systematic code generator.\n\n"
                             "USAGE\n"
                             "  ./encode [-h] [-i infile] [-o outfile]\n\n"
                             "OPTIONS\n"
                             "  -h             Program usage and help.\n"
                             "  -i infile      Input data to encode.\n"
                             "  -o outfile     Output of encoded data.\n");
            exit(0);
            break;
        }
    }

    // the following three lines is to set file permissions of in and outfiles
    // (lab pdf - Darrell Long)
    struct stat statbuf;
    fstat(fileno(infile), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);

    if (help_run) { // if help flag is true
        printf("SYNOPSIS\n"
               "  A Hamming(8, 4) systematic code generator.\n\n"
               "USAGE\n"
               "  ./encode [-h] [-i infile] [-o outfile]\n\n"
               "OPTIONS\n"
               "  -h             Program usage and help.\n"
               "  -i infile      Input data to encode.\n"
               "  -o outfile     Output of encoded data.\n");
        exit(0);
    }

    // this is the array of values of the G encoding matrix
    uint32_t G_val[32] = { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1,
        0, 0, 0, 1, 1, 1, 1, 0 };

    BitMatrix *G = bm_create(4, 8); // initialize the size of the G matrix
    for (uint32_t i = 0; i < bm_rows(G); i += 1) { // loop through the rows
        for (uint32_t j = 0; j < bm_cols(G); j += 1) { // loop through the cols
            if (G_val[i * 8 + j]) { // if the corrsponding postion in the matrix array is 1
                bm_set_bit(G, i, j); // set the bit at that position in the G matrix
            }
        }
    }

    // the following is an encoding look up table (adapted frlm Eric ta pseudo)
    // since there are only 16 possible values that can be ecoded, they are computed ahead of time
    // and stored in an array.
    int32_t lookup_encoding[16]; // initalize array
    for (uint32_t e = 0; e <= 0x0F; e++) { // loop from 0 to 15
        lookup_encoding[e] = ham_encode(G, e); // encode the corresponding values
    }

    int32_t byte;
    while ((byte = fgetc(infile)) != EOF) { // grab each byte until end of file

        uint8_t lower = lower_nibblenc(byte); // split into lower nibble
        uint8_t upper = upper_nibblenc(byte); // split into upper nibble

        uint8_t lower_byte = lookup_encoding[lower]; // use look up table for lower nibble
        uint8_t upper_byte = lookup_encoding[upper]; // use look up table for upper nibble

        fputc(lower_byte, outfile); // put lower nibble in outfile
        fputc(upper_byte, outfile); // put upper nibble in outfile
    }

    // close both the outfile and infile
    fclose(infile);
    fclose(outfile);

    // delete the enccoding G matrix
    bm_delete(&G);

    return 0;
}
