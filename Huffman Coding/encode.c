#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OPTIONS "hi:o:v" // encoding options

// function is reponsible for creating a histograg from the infile
// adapted from asgn5 entropy code
void histogram(int infile, uint64_t hist[ALPHABET]) {
    int length; // integer length
    uint8_t buffer[BLOCK] = { 0 }; // buffer of size BLOCK initialized with 0s
    while ((length = read_bytes(infile, buffer, BLOCK)) > 0) { // read bytes is greater than 0
        for (int i = 0; i < length; i += 1) { // loop through from 0 to length
            hist[buffer[i]] += 1; // increase the count of char
        }
    }
    return;
}

// function created the tree dump of the built tree for decoding
void tree_dump(int outfile, Node *root) {
    if (!root) {
        return;
    }
    if ((root->left == NULL) && (root->right == NULL)) { // if children of node are NULL
        uint8_t buff[2]
            = { 'L', root->symbol }; // create a buffer with two elements, L and the char
        write_bytes(outfile, buff, 2); // write out the two elements to the outfile
    } else {
        tree_dump(outfile, root->left); // recursively call tree dump on right child of node
        tree_dump(outfile, root->right); // recursively call tree dump on left chile of node
        uint8_t buff[1] = { 'I' }; // create a buffer with on element, I
        write_bytes(outfile, buff, 1); // print out I to the outfile
    }
}

int main(int argc, char **argv) {
    int infile = 0, outfile = 1; // deafult read and write locations

    bool help_run = false; // help message flag
    bool verbose_flag = false; // verbose printing flag

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
            if ((outfile = open(optarg, O_RDWR | O_CREAT | O_TRUNC, 0600)) == -1) {
                fprintf(stderr, "Error: failed to open outfile\n"); // -1 return unable to open
                exit(1);
            }
            break;
        case 'v': verbose_flag = true; break;
        default: // default case
            fprintf(stdout, "SYNOPSIS\n" // print help meesage
                            "  A Huffman encoder.\n"
                            "  Compresses a file using Huffaman coding alorithm.\n\n"
                            "USAGE\n"
                            "  ./encode [-h] [-i infile] [-o outfile]\n\n"
                            "OPTIONS\n"
                            "  -h             Program usage and help.\n"
                            "  -v             Print compression statistics.\n"
                            "  -i infile      Input file to compress.\n"
                            "  -o outfile     Output of compressed data.\n");
            exit(0);
            break;
        }
    }

    if (help_run) { // if help flag is true
        printf("SYNOPSIS\n"
               "  A Huffman encoder.\n"
               "  Compresses a file using Huffaman coding alorithm.\n\n"
               "USAGE\n"
               "  ./encode [-h] [-i infile] [-o outfile]\n\n"
               "OPTIONS\n"
               "  -h             Program usage and help.\n"
               "  -v             Print compression statistics.\n"
               "  -i infile      Input file to compress.\n"
               "  -o outfile     Output of compressed data.\n");
        exit(0);
    }

    // this section creates the histogram from the infile and increments 0x00 and 0xFF manually
    uint64_t hist[ALPHABET] = { 0 }; // hist created of size ALPHABET
    histogram(infile, hist);
    hist[0] += 1; // increment 0x00
    hist[ALPHABET - 1] += 1; // increment 0xFF

    // following loop counts the number of unique elements
    uint64_t number_leaves = 0; // var for number of leaves
    for (uint64_t i = 0; i < ALPHABET; i++) { // loops through index of histogram
        if (hist[i] > 0) { // if char exists
            number_leaves += 1; // increment number of leaves
        }
    }

    // builds tree using histogram
    Node *root = build_tree(hist);

    // code table is build using root node
    Code table[ALPHABET];
    build_codes(root, table);

    // transfering of file perms from infile to outfile (sourced from Darrell Long)
    struct stat statbuf;
    fstat(infile, &statbuf);
    fchmod(outfile, statbuf.st_mode);

    // header for encoded file initialized (from Eric pseudocode);
    Header out_header = { 0, 0, 0, 0 }; // set all struct elements to 0
    out_header.magic = MAGIC; // set magic number to 0xDEADBEEF
    out_header.permissions = statbuf.st_mode; // transfer file perms
    out_header.tree_size = 3 * number_leaves - 1; // size of tree
    out_header.file_size = statbuf.st_size; // size of file in bytes

    // writes out header to outfile
    write_bytes(outfile, (uint8_t *) &out_header, sizeof(Header));

    tree_dump(outfile, root); // uses built tree to create a tree dump
    lseek(infile, 0, SEEK_SET); // start file pos from the start of file

    // following fucntion write out the code for each char in the infile to outfile
    uint8_t cbuffer[BLOCK] = { 0 }; // create a buffer to store chars read
    int length; // int length
    while ((length = read_bytes(infile, cbuffer, BLOCK)) > 0) { // read chars from infile
        for (int i = 0; i < length; i += 1) { // loop through length number of bytes
            write_code(outfile, &table[cbuffer[i]]); // write code for char to outfile
        }
    }
    flush_codes(outfile); // flush any remaining codes to outfile

    // prints out the verbose statistics
    if (verbose_flag) {
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", statbuf.st_size);
        fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_written);
        fprintf(stderr, "Space saving: %.2f%%\n",
            100 * (1 - ((double) bytes_written / statbuf.st_size)));
    }

    delete_tree(&root);
    close(infile);
    close(outfile);
}
