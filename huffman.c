#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "huffman.h"

extern FILE *fpIn;
extern FILE *fpOut;
extern entry *head;
extern entry *root;
extern unsigned char buffer;
extern int buffer_fill_count;

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

// Keep Sorted by Frequency
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

void print_node(entry *node) {

	printf("Node Properties:\n\t");
	if(node != NULL) {
		if(node->val != NULL) printf("%d\t:\t%d\n", node->freq, *node->val);
		else printf("%d\t:\t*\n", node->freq);
	} else {
		printf("Nodes is empty\n");
	}
}

void print_sequence(sequence *head) {
	sequence *rover = head;

	while(rover != NULL) {
		printf("%u", rover->val);
		rover = rover->fwd;
	}

	printf("\n");
}

bool search_tree(unsigned char val, entry *node, sequence *currentSeq) {

	if(node == NULL) return false;

	if(node->val != NULL && *node->val == val) return true;
	 
	if(search_tree(val, node->left, currentSeq)) {

		sequence *rover = currentSeq;

		while(rover->fwd != NULL) rover = rover->fwd;

		rover->fwd = calloc(sizeof(*rover->fwd), 1);
		rover->fwd->val = 0;

		return true;

	} else if(search_tree(val, node->right, currentSeq)) {
		
		sequence *rover = currentSeq;

		while(rover->fwd != NULL) rover = rover->fwd;

		rover->fwd = calloc(sizeof(*rover->fwd), 1);
		rover->fwd->val = 1;

		return true;
	}

	return false;
}

sequence *build_encoded_sequence(unsigned char val, entry *node) {

	sequence *currentSeq = calloc(sizeof(*currentSeq), 1);

	currentSeq->fwd = NULL;

	search_tree(val, node, currentSeq);

	currentSeq = currentSeq->fwd;

	// print_sequence(currentSeq);

	currentSeq = reverse_sequence(currentSeq);

	return currentSeq;

}

sequence *reverse_sequence(sequence *current) {

	sequence *previous = NULL;
	sequence *next;

	while(current != NULL) {

		next = current->fwd;
		current->fwd = previous;
		previous = current;
		current = next;

	}

	return previous;

}
