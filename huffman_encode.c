#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "huffman.h"

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

	while(fread(&val, sizeof(val), 1, fpIn) == 1) {
	 	assert(output_huffman_code(val, root) == true);
	}

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
