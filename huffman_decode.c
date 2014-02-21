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

int main(int argc, char **argv) {

	assert(argc == 2);

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
