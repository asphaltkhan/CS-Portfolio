#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:v" // decoding options

int main(int argc, char **argv) {
    int infile = 0, outfile = 1; // deafult read and write locations

    bool help_run = false; // help message flag
    bool verbose_flag = false;

    int32_t choice = 0; // command line option var

    //
    // the following while loop is for the users selected command line options
    while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
        switch (choice) { // when switch is any value other than 0
        case 'h': help_run = true; break; // set a help flag and break
        case 'i':
            if ((infile = open(optarg, O_RDONLY)) == -1) { // open infile to read
                fprintf(stderr, "Error: failed to open infile\n"); // if -1 return unable to open
                exit(1);
            }
            break;
        case 'o':
            if ((outfile = open(optarg, O_RDWR | O_CREAT | O_TRUNC)) == -1) {
                fprintf(stderr, "Error: failed to open outfile\n"); // -1 return unable to open
                exit(1);
            }
            break;
        case 'v': verbose_flag = true; break;
        default: // default case
            fprintf(stdout, "SYNOPSIS\n" // print help meesage
                            "  A Huffman decoder.\n"
                            "  Decompresses a file using the Huffaman coding alorithm.\n\n"
                            "USAGE\n"
                            "  ./encode [-h] [-i infile] [-o outfile]\n\n"
                            "OPTIONS\n"
                            "  -h             Program usage and help.\n"
                            "  -v             Print compression statistics.\n"
                            "  -i infile      Input file to decompress.\n"
                            "  -o outfile     Output of decompressed data.\n");
            exit(0);
            break;
        }
    }

    if (help_run) { // if help flag is true
        printf("SYNOPSIS\n"
               "  A Huffman decoder.\n"
               "  Decompresses a file using Huffaman coding alorithm.\n\n"
               "USAGE\n"
               "  ./encode [-h] [-i infile] [-o outfile]\n\n"
               "OPTIONS\n"
               "  -h             Program usage and help.\n"
               "  -v             Print compression statistics.\n"
               "  -i infile      Input file to decompress.\n"
               "  -o outfile     Output of decompressed data.\n");
        exit(0);
    }

    // following read in header for information on file
    Header in_header = { 0, 0, 0, 0 }; // initialize header
    read_bytes(infile, (uint8_t *) &in_header, sizeof(Header)); // read in header from infile

    if (in_header.magic != MAGIC) { // make sure the right file is being decoded from magic number
        fprintf(stderr, "Ivalid file was passed to decode.\n");
        exit(1);
    }

    // assign file perms for outfile
    fchmod(outfile, in_header.permissions);

    // rebuild the tree using header tree size and tree dump
    uint8_t tree_rebuild[in_header.tree_size];
    read_bytes(infile, tree_rebuild, in_header.tree_size); // read the bytes of the tree dump
    Node *rebuild_root = rebuild_tree(in_header.tree_size, tree_rebuild);

    // following uses the code written in infile to travers the rebuilt tree and print
    Node *current = rebuild_root; // create a node eqaul to the root
    uint64_t index = 0; // index for number of bytes
    uint8_t bit; // bit being read
    while (current && read_bit(infile, &bit)) { // while there bits to read
        if (index == in_header.file_size) { // the number of bytes written equal file size of og
            break; // break loop
        }
        if (bit == 0) { // if bit read is 0
            current = current->left; // travers down left branch
        } else {
            assert(bit == 1); // if bit read is 1
            current = current->right; // traverse down right branch
        }
        // if the current node has children that are NULL
        if (current && ((current->left) == NULL) && ((current->right) == NULL)) {
            uint8_t temp[1] = { current->symbol }; // create a temp buffer with nodes symbol
            write_bytes(outfile, temp, 1); // write the char to the outfile
            current = rebuild_root; // reset back to top of tree
            index += 1; // increase number of bytes written counter
        }
    }

    // prints out the file decompression statistics
    if (verbose_flag) {
        fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_read);
        fprintf(stderr, "Decompressed file size: %lu bytes\n", bytes_written);
        fprintf(
            stderr, "Space saving: %.2f%%\n", 100 * (1 - ((double) bytes_read / bytes_written)));
    }

    delete_tree(&rebuild_root);
    close(infile);
    close(outfile);
}
