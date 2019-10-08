/* ref.h
 * VoidPtr Example
 */

#ifndef REF_H
#define REF_H

#include "util.h"

#define SIZE 256

typedef struct {
	char type[SIZE];
	char header[SIZE];
	char title[SIZE];
	char author[SIZE];
	char journal[SIZE];
	char volume[SIZE];
	char number[SIZE];
	char pages[SIZE];
	char year[SIZE];
	char publisher[SIZE];
	char booktitle[SIZE];
	char organization[SIZE];
	char note[SIZE];
	char howpublished[SIZE];
} Ref;

// malloc a new refrence
Ref* new_refrence();

// free the refrence
void free_refrence(Ref * ref);

// cast and free voided data
void free_data(void *data);

// compator function to search for the year, data must be cast ref and cmp is year
void search_year(void * data, void * cmp);

// compator function to seach for the year, data is cast to ref and cmp is publisher
void search_publisher(void * data, void * cmp);

// print refrence, cast it to ref
void print_ref_void(void * data);

// print the refrence, if data is present
void print_ref(Ref * ref);

#endif
