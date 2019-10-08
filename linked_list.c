/* linked_list.c
 * VoidPtr Example
 */

#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"
#include "util.h"

Node* new_linked_list() {
	Node * node;
	node = (Node *)malloc(1 * sizeof(Node));

	// this will be a sentinal, if you hit this its the end of the list
	node->data = NULL;
	node->link = NULL;

	return node;
}

Node * add_node(Node * node, void * data) {

	// create a new node	
	Node * new_root;

	new_root = (Node *)malloc(1 *sizeof(Node));	

	// link the data and add it to the end of the list
	new_root->data = data;
	new_root->link = node; 

	return new_root;
}

bool delete_node(Node ** node, int index, void(*free_data)(void *data)) {

	int i = 0;
	Node * walker;
	Node * previous;

	walker = *node;
	previous = NULL;

	// walk to the index
	while (i <= index && walker != NULL) {
		previous = walker;
		walker = walker->link;
		i++;
	}

	// failed to find the index 
	if (walker == NULL) {
		return false;
	}

	// delete head
	if (previous == NULL) {
		*node = walker->link;
		
		free_data(walker->data);
		free(walker);
	
	} else { //delete in other cases
		previous->link = walker->link;

		free_data(walker->data);
		free(walker);
	}	
	return true;
}

void walk(Node * node, void(*op)(void * data)){
	
	Node * walker;

	walker = node;

	int index = 0;

	// walk the entire list
	while(walker->link != NULL) {

		// this is a hack, to implment this correctly, you will have to perform a function pointer pass with two data
		// elements, one is the index and the other is the data to operate on, see search below
		printf("\nindex: %d\n", index);
		
		op(walker->data);
		walker = walker->link;
		index++;
	}
}

void search(Node * node, void * cmp, void(*op)(void * data, void * cmp)){
	
	Node * walker;

	walker = node;

	// walk list execute op compare
	while(walker->link != NULL) {
		op(walker->data, cmp);
		walker = walker->link;
	}
}

void * get_data(Node * node) {
	return node->data;
}


void free_nodes(Node * node, void(*free_data)(void *data)) {

	Node * walker;
	walker = node;

	// walk the data and free the data
	while(walker != NULL) {
		Node * temp;
		temp = walker;
		
		walker = walker->link;

		// free the data and then the node temp ptr
		free_data(temp->data);
		free(temp);	
	}	

	// free the sentinal
	free(walker);	
}
