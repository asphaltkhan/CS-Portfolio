#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "helper.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:v" // command line options for decoding

// Returns the lower nibble of val (provided on lab pdf - Darrell Long)
uint8_t lower_nibbledec(uint8_t val) {
    return val & 0xF;
}

// Returns the upper nibble of val (provided on lab pdf - Darrell Long)
uint8_t upper_nibbledec(uint8_t val) {
    return val >> 4;
}

// Packs two nibbles into a byte (provided on lab pdf - Darrell Long)
uint8_t pack_bytedec(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    FILE *infile = stdin, *outfile = stdout; // default read write locations

    bool help_run = false, stats = false; // help message and program stats flags

    int32_t choice = 0; // command line choice variable

    //
    // the following while loop is for the users selected command line options
    while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
        switch (choice) { // when switch is any value other than 0
        case 'h': help_run = true; break; // set a help flag and break
        case 'i':
            if ((infile = fopen(optarg, "rb")) == NULL) { // // open infile to read
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
        case 'v': stats = true; break; // set stats printing flag
        default: // default case
            fprintf(outfile, "SYNOPSIS\n" // print help message
                             "  A Hamming(8, 4) systematic code generator.\n\n"
                             "USAGE\n"
                             "  ./decode [-h] [-v] [-i infile] [-o outfile]\n\n"
                             "OPTIONS\n"
                             "  -h             Program usage and help.\n"
                             "  -v             Print statistics of decoding to stderr.\n"
                             "  -i infile      Input data to encode.\n"
                             "  -o outfile     Output of encoded data.\n");
            exit(0);
            break;
        }
    }

    // the follwing three lines is to set file permissions of in and outfiles
    // (lab pdf - Darrell Long)
    struct stat statbuf;
    fstat(fileno(infile), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);

    if (help_run) { // if help flag is true
        printf("SYNOPSIS\n"
               "  A Hamming(8, 4) systematic code generator.\n\n"
               "USAGE\n"
               "  ./decode [-h] [-v] [-i infile] [-o outfile]\n\n"
               "OPTIONS\n"
               "  -h             Program usage and help.\n"
               "  -v             Print statistics of decoding to stderr.\n"
               "  -i infile      Input data to encode.\n"
               "  -o outfile     Output of encoded data.\n");
        exit(0);
    }

    // this is the array of values for the transposed matrix Ht
    uint32_t H_val[32] = { 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 1 };

    BitMatrix *H = bm_create(8, 4); // initialize size of Ht matrix
    for (uint32_t i = 0; i < bm_rows(H); i += 1) { // loop through the rows
        for (uint32_t j = 0; j < bm_cols(H); j += 1) { // loop through the cols
            if (H_val[i * 4 + j]) { // if corresponding postion in matrix array is 1
                bm_set_bit(H, i, j); // set the bit at that position in the g matrix
            }
        }
    }

    int32_t byte;
    while ((byte = fgetc(infile)) != EOF) { // grab each byte until end of file

        uint8_t lower_byte; // variable for lower byte
        ham_decode(H, byte, &lower_byte); // run decoding algorithm on first byte

        uint8_t upper_byte; // variable for upp byte
        byte = fgetc(infile); // get next byte
        ham_decode(H, byte, &upper_byte); // run decoding algorithm on second byte

        uint8_t og = pack_bytedec(upper_byte, lower_byte); // combine the two resulting nibbles

        fputc(og, outfile); // put combined byte into outfile
    }

    // following statistics are printed when specified by user
    if (stats) {
        fprintf(stderr, "Total bytes processed: %d\n", total_bytes);
        fprintf(stderr, "Uncorrected errors: %d\n", uncorrected_errors);
        fprintf(stderr, "Corrected errors %d\n", corrected_errors);
        fprintf(stderr, "Error rate: %f\n", ((double) uncorrected_errors) / total_bytes);
    }

    // close both infile and outfile
    fclose(infile);
    fclose(outfile);

    // delete the Ht transpose matrix
    bm_delete(&H);

    return 0;
}
