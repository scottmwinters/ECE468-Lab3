#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "huffman.h"

FILE *fpIn = NULL;
FILE *fpOut = NULL;
entry *head = NULL;
entry *root = NULL;
unsigned char buffer = 0;
int buffer_fill_count = 0;

int main(int argc, char **argv) {

	assert(argc == 2);

	char *inputFile = argv[1];
	char *outputFile = calloc(sizeof(*inputFile), MAX_STRING_LEN);

	// Create Output File
	strcpy(outputFile, inputFile);
	strcat(outputFile, ".huff");

	fpIn = fopen(inputFile, "rb");
	fpOut = fopen(outputFile, "wb");

	assert(fpIn != NULL);
	assert(fpOut != NULL);

	unsigned char val;

	while(fread(&val, sizeof(val), 1, fpIn) == 1) {

		entry *rover = head;
		while(rover != NULL) {
			if(*rover->val == val) {
				rover->freq++;
				break;
			} 
			rover = rover->fwd;
		}

		if(rover == NULL) create_entry(val);
	}

	entry *rover = head;
	for(int i = 0; i < 256; i++) {

		if(rover != NULL && *rover->val == i) {
			fwrite(&(rover->freq), sizeof(rover->freq), 1, fpOut);
			rover = rover->fwd;
		} else {
			int zero = 0;
			fwrite(&zero, sizeof(int), 1, fpOut);
		}
	}

	list_sort_by_freq();

	build_tree();

	rewind(fpIn);

	buffer = 0;
	buffer_fill_count = 0;
	while(fread(&val, sizeof(val), 1, fpIn) == 1) {
	 	
	 	sequence *currentSeq = build_encoded_sequence(val, root);
	 	
	 	sequence *rover = currentSeq;

	 	while(rover != NULL) {

	 		buffer |= rover->val << (7 - buffer_fill_count); // Upper Most Bit is First
	 		buffer_fill_count = (buffer_fill_count + 1) % 8;

	 		if(buffer_fill_count == 0) {
	 			fwrite(&buffer, sizeof(buffer), 1, fpOut);
	 			buffer = 0;
	 		}

	 		rover = rover->fwd;
	 	}

	}

	if(buffer_fill_count != 0) fwrite(&buffer, sizeof(buffer), 1, fpOut);

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
