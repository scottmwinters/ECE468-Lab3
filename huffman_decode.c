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
	char *outputFile = calloc(sizeof(*outputFile), MAX_STRING_LEN);

	char *fileExtension = calloc(sizeof(*fileExtension), MAX_STRING_LEN);
	strcpy(fileExtension, &inputFile[strlen(inputFile) - 5]);
	assert(strcmp(fileExtension, ".huff") == 0);

	strncpy(outputFile, inputFile, strlen(inputFile) - strlen(".huff"));

	printf("%s\n", inputFile);
	printf("%s\n", outputFile);

	fpIn = fopen(inputFile, "rb");
	fpOut = fopen(outputFile, "wb");

	assert(inputFile != NULL);
	assert(outputFile != NULL);

	int inputFreq;

	for(int i = 0; i < 256; i++) {
		
		fread(&inputFreq, sizeof(inputFreq), 1, fpIn);
		
		if(inputFreq > 0) {

			create_entry((unsigned char)i);
			entry *rover = head;
			while(rover != NULL) {
				if(*rover->val == (unsigned char)i) {
					rover->freq = inputFreq;
					break;
				}
				rover = rover->fwd;
			}
		}

	}

	print_list();

	list_sort_by_freq();

	print_list();

	build_tree();


	// unsigned char inputBuffer;
	int writtenValues = 0;
	entry *currentNode = root;
	int bufferPos = 0;

	printf("Number of Characters = %d\n", root->freq);

	print_node(root);
	print_node(root->right->right);

	while(writtenValues < root->freq) {

		if(bufferPos == 0) {
			fread(&buffer, sizeof(buffer), 1, fpIn);
			printf("0x%x\n", buffer);
		}

		unsigned char currentBit = 0x80;
		currentBit &= buffer << bufferPos;
		currentBit = currentBit >> 7;

		if(currentBit == 0) currentNode = currentNode->left;
		else if(currentBit == 1) currentNode = currentNode->right; 

		if(currentNode->left == NULL && currentNode->right == NULL) {
			printf("%c\n", *currentNode->val);
			sleep(1);
			fwrite(currentNode->val, sizeof(*currentNode->val), 1, fpOut);
			writtenValues++;
			currentNode = root;
		}

		bufferPos = (bufferPos + 1) % 8;

	}



	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
