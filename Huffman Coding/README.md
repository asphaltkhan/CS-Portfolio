# Huffman Coding

This program uses the C programming language to implement an encoding and decoding algorithm. 
Through the implementation of the implementation of the Code ADT, Node ADT, Priority Queue ADT, 
and Stack ADT the program will be able to encode and decode any file given. The file will be 
properly compressed when encoded and decompressed when decoded. Printing the encode and  deocde 
statistics will help visualize the number of bytes processed before and after compression, as 
well as the effeciency of the program. The program will read a given input file using a the 
coded I/O functions. These functions are built off of already present low level I/O calls in C. 
The read chars are converted into nodes which are then used to create a node tree structure. 
By treaversing certain paths on the tree to reach the leaf nodes, a table of codes is formed.
This is then used when translating the original file into codes. A header file has also been 
implemented in the encoding and decoding algorithms, allowing for file permissions to be properly
transfered as well as file stats to be read.\

#### Build

This program is built with the included `Makefile`. Make sure to first run `make clean` before
running `make.` The option is available to compile indivdidual files. When executed you are
required to select from a set of command line arguments. Typing `-h` without specifying a
command will print out the available commands.\

```
make types:

make clean
make all

make encode/decode/entropy
```

Building and Running:
```
make clean
make
./encode -i random.txt | ./decode -v
```

Help Messages:
```
---encode---

SYNOPSIS
  A Huffman encoder.
  Compresses a file using Huffaman coding alorithm.

USAGE
  ./encode [-h] [-i infile] [-o outfile]

OPTIONS
  -h             Program usage and help.
  -v             Print compression statistics.
  -i infile      Input file to compress.
  -o outfile     Output of compressed data.

---decode---

SYNOPSIS
  A Huffman decoder.
  Decompresses a file using Huffaman coding alorithm.

USAGE
  ./encode [-h] [-i infile] [-o outfile]

OPTIONS
  -h             Program usage and help.
  -v             Print compression statistics.
  -i infile      Input file to decompress.
  -o outfile     Output of decompressed data.
```

Flags: `-Wall -Wextra -Werror -Wpedantic`

### Variance/ Bugs

The following issue has been resolved.\
~~When running `scan-build make` certain errors are reported. They are to do with the possiblity~~
~~of the root node being `NULL` when finding its children. Although this is a potential issue~~
~~it is trivial and will never be the case. For large files when tested and with extremely~~
~~small files, the root node has never been `NULL.` This issue is ongoing and is yet to~~
~~be resolved.~~

The following issues are ongoing and yet to be resolved.\

For extremely large file sizes, compression ratio is in consistent to example.

In addition, the compression does not seem to run on file types of objects as well as `.pdf.`

### Files

This folder contains the following files:
> encode.c (encode main file)\
> decode.c (decode main file)\
> huffman.c (huffman algorithm file)\
> huffman.h (corresponding header file)\
> io.c (I/O implementation file)\
> io.h (corresponding header file)\
> code.c (Code ADT)\
> code.h (corresponding header file)\
> node.c (Node ADT)\
> node.h (corresponding header file)\
> pq.c (Priority Queue ADT)\
> pq.h (corresponding header file)\
> stack.c (Stack ADT)\
> stack.h (corresponding header file)\
> entropy.c (entropy calculator file)\
> header.h (header file)\
> defines.h (header file)\
> Makefile (code builder)\
> DESIGN.pdf (design document)\
> README.md
