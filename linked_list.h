/* linked_list.h
 * VoidPtr Example
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "util.h"

typedef struct Node {
	void * data;
	struct Node * link;
} Node;

// create a new linked list
Node* new_linked_list();

// add data to the linked list, note the return node
Node * add_node(Node * node, void * data);

// delete a node, must pass address of node, index and a data freeing function
bool delete_node(Node ** node, int index, void(*free_data)(void *data));

// walk the list and excute void op on data
void walk(Node * node, void(*op)(void* data));

// search for a node, must pass in compartor function 
void search(Node * node, void * cmp, void(*op)(void* data, void * cmp)); 

// not really used but should be helpful if you play around with the program
void * get_data(Node * node);

// free the nodes by walking the list, must pass in the data freeing func
void free_nodes(Node * node, void (*free)(void* data));

#endif
