#define MAX_STRING_LEN 255

typedef struct entry_tag {
	unsigned char *val;
	int freq;
	struct entry_tag *fwd;
	struct entry_tag *left;
	struct entry_tag *right;
} entry;

typedef struct sequence_tag {
	unsigned char val;
	struct sequence_tag *fwd;
} sequence;

// List Managment
void create_entry(unsigned char val);
void insert_entry(entry *new);
void list_sort_by_freq();

// Tree Managment
void build_tree();
entry *pop_head();
bool search_tree(unsigned char val, entry *node, sequence *currentSeq);
sequence *build_encoded_sequence(unsigned char val, entry *node);
sequence *reverse_sequence(sequence *head);

// Extras
void print_list();
void print_node(entry *node);
void print_sequence(sequence *head);
