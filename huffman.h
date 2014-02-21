#define MAX_STRING_LEN 255

typedef struct entry_tag {
	unsigned char *val;
	int freq;
	struct entry_tag *fwd;
	struct entry_tag *left;
	struct entry_tag *right;
} entry;

// List Managment
void create_entry(unsigned char val);
void insert_entry(entry *new);
void list_sort_by_freq();

// Tree Managment
void build_tree();
entry *pop_head();

// Huffman Functions
bool output_huffman_code(unsigned char val, entry *node);

// Extras
void print_list();
void print_node(entry *node);
