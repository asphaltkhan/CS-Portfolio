CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode error entropy decode

encode: encode.o bv.o bm.o hamming.o
	$(CC) -o encode encode.o bv.o bm.o hamming.o -lm

decode: decode.o bv.o bm.o hamming.o
	$(CC) -o decode decode.o bv.o bm.o hamming.o -lm

error: error.o
	$(CC) -o error error.o -lm

entropy: entropy.o
	$(CC) -o entropy entropy.o -lm

encode.o:
	$(CC) $(CFLAGS) -c encode.c

decode.o:
	$(CC) $(CFLAGS) -c decode.c

bv.o:
	$(CC) $(CFLAGS) -c bv.c

bm.o:
	$(CC) $(CFLAGS) -c bm.c

hamming.o:
	$(CC) $(CFLAGS) -c hamming.c

error.o:
	$(CC) $(CFLAGS) -c error.c

entropy.o:
	$(CC) $(CFLAGS) -c entropy.c

format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f encode decode error entropy encode.o decode.o bv.o bm.o hamming.o error.o entropy.o

scan-build: clean
	scan-build make
