#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_TYPE unsigned char
#define MAX_STRING_LEN 255


int main(int argc, char **argv) {

	assert(argc == 2);

	char *inputFile = argv[1];
	char *outputFile = calloc(sizeof(*inputFile), MAX_STRING_LEN);

	// Create Output File
	strcpy(outputFile, inputFile);
	strcat(outputFile, ".huff");

	FILE *fpIn = NULL;
	FILE *fpOut = NULL;

	fpIn = fopen(inputFile, "rb");
	fpOut = fopen(outputFile, "wb");

	assert(fpIn != NULL);
	assert(fpOut != NULL);


	unsigned int *frequencyArray = NULL;
	frequencyArray = calloc(sizeof(*frequencyArray), 256);
	INPUT_TYPE *chr = calloc(sizeof(*chr), 1);

	while(fread(chr, sizeof(*chr), 1, fpIn) == 1) frequencyArray[*chr]++;

	rewind(fpIn);

	for(int i = 0; i < 256; i++) {
		unsigned char x = frequencyArray[i];
		int j = i;
		while(j > 0 && frequencyArray[j-1] > x) {
			frequencyArray[j] = frequencyArray[j-1];
			j--;
		}
		frequencyArray[j] = x;
	}	

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
