#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_TYPE unsigned char
#define MAX_STRING_LEN 255

typedef struct entry_tag {
	unsigned char val;
	int freq;
	struct entry_tag *fwd;
} entry;

typedef struct node_tag {
	entry *entry; 
	struct node_tag *left;
	struct node_tag *right;
} node;

entry *head = NULL;

// Sorted Insert
void create_entry(unsigned char val) {

	entry *current = calloc(sizeof(*current), 1);

	current->val = val;
	current->freq = 1;
	current->fwd = NULL;

	if(head == NULL) {
		head = current;
	} else {

		entry *rover = head;

		if(val < head->val) {
			current->fwd = head;
			head = current;
		} else {

			entry *previous = rover;
			rover = rover->fwd;

			while(rover != NULL) {
		
				if(val > previous->val && val < rover->val) {
					current->fwd = rover;
					previous->fwd = current;
					break;
				}

				previous = rover;
				rover = rover->fwd;
			}

			if(rover == NULL) previous->fwd = current;
		}
	}
}

void list_sort_by_freq() {

	if(head->fwd == NULL) return;

	int sorted = 0;

	do {

		entry *current = head;
		entry *next = head->fwd;
		
		sorted = 0;

		do {
			if(current->freq > next->freq) {
				entry *temp = calloc(sizeof(*temp), 1);
				
				temp->val = current->val;
				temp->freq = current->freq;

				current->val = next->val;
				current->freq = next->freq;

				next->val = temp->val;
				next->freq = temp->freq;

				sorted = 1;
			}

			current = next;
			next = next->fwd;
		} while(next != NULL);
	} while(sorted);
}

void print_list() {
	entry *rover = head;
	while(rover != NULL) {
		printf("%d : %d\n", rover->val, rover->freq);
		rover = rover->fwd;
	}
}

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

	unsigned char val;

	while(fread(&val, sizeof(val), 1, fpIn) == 1) {

		entry *rover = head;
		while(rover != NULL) {
			if(rover->val == val) {
				rover->freq++;
				break;
			} 
			rover = rover->fwd;
		}

		if(rover == NULL) create_entry(val);

	}

	list_sort_by_freq();
	print_list();
	

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
