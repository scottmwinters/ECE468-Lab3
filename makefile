all: huff_encode

huff_encode: huffman_encode.c
	gcc -Wall --pedantic huffman_encode.c -o huffEncode

clean:
	rm *.o huffEncode