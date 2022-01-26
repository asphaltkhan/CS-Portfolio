# Hamming Codes

This program uses the C programming language to implement an encoding and decoding algorithm. 
Through the implementation of the BitVector ADT and a BitMatrix ADT, the program will be able to
encode and decode any file given. Along with this, the decoded file can be decoded with forcefully 
introduced error. Printing the deocde statistics wil help visualize the bytes that were processed.
The program can take the file and read the chars in the file as bytes. These will then be encoded
using a Hamming(8,4) scheme. The arithematic is done through the manipulation of matrices. While 
encoding if error is introduced, the docing algorithm is coded in such a way that it can detect 
the errors and attempt to fix them. The algorithm can fix up to one error but identify two. 

#### Build

This program is built with the included `Makefile`. Make sure to first run `make clean` before
running `make.` The option is available to compile indivdidual files. When executed you are
required to select from a set of command line arguments. Typing `-h` without specifying a
command will print out the available commands.\

```
make types:

make clean
make all

make encode/decode/error/entropy
```

Building and Running:
```
make clean
make
./encode -i random.txt | ./error -e 0.05 -s 2021 | ./decode -v
```

Help Messages:
```
---encode---

SYNOPSIS
  A Hamming(8, 4) systematic code generator.

USAGE
  ./encode [-h] [-i infile] [-o outfile]

OPTIONS
  -h             Program usage and help.
  -i infile      Input data to encode.
  -o outfile     Output of encoded data.

---decode---

SYNOPSIS
  A Hamming(8, 4) systematic code decoder.

USAGE
  ./decode [-h] [-v] [-i infile] [-o outfile]

OPTIONS
  -h             Program usage and help.
  -v             Print statistics of decoding to stderr.
  -i infile      Input data to decode.
  -o outfile     Output of decoded data.

---error---

SYNOPSIS
  A error-injection (noise) program.

USAGE
  ./error [-h] [-s seed] [-e error_rate]

OPTIONS
  -h               Program usage and help.
  -s seed          Specifies the random seed.
  -e error_rate    Specifies the error rate.

---entropy---

SYNOPSIS
  A entropy measuring program.

USAGE
  ./entropy < [input (reads from stdin)]

OPTIONS
  -h               Program usage and help.
```

Flags: `-Wall -Wextra -Werror -Wpedantic`

### Files

This folder contains the following files:
> encode.c (encode main file)\
> decode.c (decode main file)\
> hamming.c (hamming algorithm file)\
> hamming.h (corresponding header file)\
> bm.c (BitMatrix ADT)\
> bm.h (corresponding header file)\
> bv.c (BitVector ADT)\
> bv.h (corresponding header file)\
> error.c (error file)\
> entropy.c (entropy calculator file)\
> helper.h (helper header file)\
> Makefile (code builder)\
> DESIGN.pdf (design document)\
> WRITEUP.pdf (code analysis)\
> README.md 


