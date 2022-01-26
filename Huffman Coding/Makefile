CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode decode entropy 

encode: encode.o huffman.o io.o stack.o code.o node.o pq.o
	$(CC) -o encode encode.o huffman.o io.o stack.o code.o node.o pq.o -lm

decode: decode.o huffman.o io.o stack.o code.o node.o pq.o 
	$(CC) -o decode decode.o huffman.o io.o stack.o code.o node.o pq.o -lm

entropy: entropy.o
	$(CC) -o entropy entropy.o -lm 

encode.o:
	$(CC) $(CFLAGS) -c encode.c

decode.o:
	$(CC) $(CFLAGS) -c decode.c

entropy.o:
	$(CC) $(CFLAGS) -c entropy.c

huffman.o:
	$(CC) $(CFLAGS) -c huffman.c

io.o:
	$(CC) $(CFLAGS) -c io.c

stack.o:
	$(CC) $(CFLAGS) -c stack.c

code.o:
	$(CC) $(CFLAGS) -c code.c

node.o:
	$(CC) $(CFLAGS) -c node.c

pq.o:
	$(CC) $(CFLAGS) -c pq.c
	
format:
	clang-format -i -style=file *.[ch]

clean:
	rm -f encode decode entropy 
	rm -f encode.o decode.o huffman.o io.o stack.o code.o node.o pq.o entropy.o

scan-build: clean
	scan-build make
