all: huff_encode huff_decode

huff_encode: huffman_encode.c huffman.c huffman.h
	gcc -Wall --pedantic -O2 -c huffman_encode.c
	gcc -Wall --pedantic -O2 -c huffman.c
	gcc -Wall --pedantic -O2 huffman_encode.o huffman.o -o huffEncode

huff_decode: huffman_decode.c huffman.c huffman.h
	gcc -Wall --pedantic -O2 -c huffman_decode.c
	gcc -Wall --pedantic -O2 -c huffman.c
	gcc -Wall --pedantic -O2 huffman_decode.o huffman.o -o huffDecode

clean:
	rm *.o huffEncode huffDecode