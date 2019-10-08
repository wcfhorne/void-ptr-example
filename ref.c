/* ref.c
 * VoidPtr Example
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ref.h"
#include "util.h"


Ref* new_refrence() {
	Ref *ref;
	ref = (Ref *)malloc(1*sizeof(Ref));

	// zero the data
	memset(ref, 0, sizeof(Ref));

	return ref;
}

void free_refrence(Ref * ref) {
	free(ref);
}

void free_data(void * data) {
	free((Ref *)data);
}

void print_ref_void(void * data) {
	Ref * ref;

	//cast the data to ref
	ref = (Ref *)data;

	// call print
	print_ref(ref);	
}

void print_ref(Ref *ref){

	printf("\n");
	
	printf("type: %s\n", ref->type);
	
	// check that the data is not empty
	// print if not empty
	if(strlen(ref->header) != 0){
		printf("header: %s\n", ref->header);
	}

	if(strlen(ref->title) != 0){
		printf("title: %s\n", ref->title);
	}
	
	if(strlen(ref->author) != 0){
		printf("author: %s\n", ref->author);
	}
	
	if(strlen(ref->journal) != 0){
		printf("journal: %s\n", ref->journal);
	}
	
	if(strlen(ref->volume) != 0){
		printf("volume: %s\n", ref->volume);
	}

	if(strlen(ref->number) != 0) {
		printf("number: %s\n", ref->number);
	}
		
	if(strlen(ref->pages) != 0) {
		printf("pages: %s\n", ref->pages);
	}

	if(strlen(ref->year) != 0) {
		printf("year: %s\n", ref->year);
	}

	if(strlen(ref->publisher) != 0) {
		printf("publisher: %s\n", ref->publisher);
	}
	
	if(strlen(ref->booktitle) != 0){
		printf("booktitle: %s\n", ref->booktitle);
	}
	
	if(strlen(ref->organization) != 0){
		printf("organization: %s\n", ref->organization);
	}
	
	if(strlen(ref->note) != 0){
		printf("note: %s\n", ref->note);
	}

	if(strlen(ref->howpublished) != 0){
		printf("howpublished: %s\n", ref->howpublished);
	}
}

void search_year(void * data, void * year) {
	Ref * ref;
	char * year_string;

	// cast the data to ref
	ref = (Ref *)data;
	
	// cast the year to a char array
	year_string = (char *)year;

	// compare
	if (strcmp(ref->year, year_string) == 0){
		printf("found: ");
		print_ref(ref);
	}	
}

void search_publisher(void * data, void * publisher) {
	Ref * ref;
	char * publisher_string;

	// cast the data to ref
	ref = (Ref *)data;

	// cast the year to a char array
	publisher_string = (char *)publisher;

	// compare
	if (strcmp(ref->publisher, publisher_string) == 0){
		printf("found: ");
		print_ref(ref);
	}
}
