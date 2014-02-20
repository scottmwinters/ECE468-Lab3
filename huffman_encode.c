#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INPUT_TYPE unsigned char
#define MAX_STRING_LEN 255

typedef struct entry_tag {
	unsigned char *val;
	int freq;
	struct entry_tag *fwd;
	struct entry_tag *left;
	struct entry_tag *right;
} entry;

entry *head = NULL;
entry *root = NULL;
unsigned char buffer = 0;
int buffer_fill_count = 0;

// Sorted Insert
void create_entry(unsigned char val) {

	entry *current = calloc(sizeof(*current), 1);

	current->val = calloc(sizeof(*current->val), 1);

	*current->val = val;
	current->freq = 1;
	current->fwd = NULL;
	current->left = NULL;
	current->right = NULL;

	if(head == NULL) {
		head = current;
	} else {

		entry *rover = head;

		if(val < *head->val) {
			current->fwd = head;
			head = current;
		} else {

			entry *previous = rover;
			rover = rover->fwd;

			while(rover != NULL) {
		
				if(val > *previous->val && val < *rover->val) {
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
				unsigned char tempVal = *current->val;
				int tempFreq = current->freq;
				
				*current->val = *next->val;
				current->freq = next->freq;

				*next->val = tempVal;
				next->freq = tempFreq;

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
		if(rover->val != NULL) printf("%d : %d\n", rover->freq, *rover->val);
		else printf("%d : * \n", rover->freq);
		rover = rover->fwd;
	}

	printf("\n");
}

entry *pop_head() {
	entry *temp = head;
	if(head->fwd != NULL) head = head->fwd;
	else head = NULL;
	return temp;
}

void insert_entry(entry *new) {

	if(head == NULL) head = new;
	else {

		if(new->freq <= head->freq) {
			new->fwd = head;
			head = new;
		} else {

			entry *current = head;
			entry *next = head->fwd;

			while(next != NULL) {

				if(new->freq > current->freq && new->freq <= next->freq) {
					new->fwd = next;
					current->fwd = new;
					break;
				}

				current = next;
				next = next->fwd;
			}

			if(next == NULL) current->fwd = new;
		}
	}
}

void build_tree() {

	while(head->fwd != NULL) {

		entry *left_node = pop_head();
		entry *right_node = pop_head();

		entry *parent_node = calloc(sizeof(*parent_node), 1);

		parent_node->val = NULL;
		parent_node->freq = left_node->freq + right_node->freq;
		parent_node->fwd = NULL;
		parent_node->left = left_node;
		parent_node->right = right_node;

		insert_entry(parent_node);
	}
	root = pop_head();
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
			if(*rover->val == val) {
				rover->freq++;
				break;
			} 
			rover = rover->fwd;
		}

		if(rover == NULL) create_entry(val);
	}

	list_sort_by_freq();
	build_tree();

	rewind(fpIn);

	while(fread(&val, sizeof(val), 1, fpIn) == 1) {

	}

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
