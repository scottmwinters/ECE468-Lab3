all: huff_encode


huff_encode: huffman_encode.c huffman.h
	gcc -Wall --pedantic -O2 huffman_encode.c -c 
	gcc -Wall --pedantic -O2 huffEncode.o -o huffEncode

clean:
	rm *.o huffEncode