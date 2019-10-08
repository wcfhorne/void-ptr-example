/* main.c
 * VoidPtr Example
 *
 * To use this program use ./executable bib.txt
 * This is an example of using void ptrs to create generic datastructures
 * You could expand this futher by pushing the searching method and execution loop
 * into other files/datastructures
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "ref.h"
#include "linked_list.h"

#define READSIZE 256

// used to create the linked list
bool create_list(FILE ** file, Node ** node);
bool add_data(char * type, char * data, Ref * ref);
bool add_header(char * ref_type, char * header, Ref * ref);
void strip_chars(char * dest, char * src);

// used to search for and delete data
void year(Node * node);
void publisher(Node * node);
void delete(Node ** node);

int main(int argc, char ** argv) {

	Node * node;
	node = new_linked_list();

	//check only a single required arg was passed
	if (argc != 2){
		printf("failed to provide correct num of inputst\n");
		exit(1);
	}

	FILE *fp;

	// open the file passed in
	fp = fopen(argv[1], "r");

	if (fp == NULL) {
		fprintf(stderr, "failed to open file: %s\n", argv[1]);
		exit(2);
	}

	// create the linked list using the file
	bool pass = create_list(&fp, &node);
	
	if (pass != true){
		fclose(fp);
		fprintf(stderr, "error creating the linked list\n");
		exit(1);
	}
	
	fclose(fp);
	
	bool run = true;
	char readbuf[READSIZE];

	printf("Bib searcher\nPlease select an op: 'year', 'publisher', 'delete', 'all', or enter 'quit' to exit the program\n");

	// run the interactive loop
	while(run){
		printf("Menu > ");
		
		fgets (readbuf , READSIZE , stdin);

		if (strcmp(readbuf, "year\n") == 0){
			
			// search for the year
			year(node);
		} else if(strcmp(readbuf, "publisher\n") == 0) {
			
			// search for the publisher
			publisher(node);
		} else if(strcmp(readbuf, "delete\n") == 0) {
			
			// delete by index
			delete(&node);
		} else if(strcmp(readbuf, "quit\n") == 0) {
			
			// quit the program
			run = false;
		} else if(strcmp(readbuf, "all\n") == 0) {
			
			// print all the data out
			walk(node, print_ref_void);
		}
		else {
			printf("unrecongnized choice\n");
		}
	}	

	// free the data, must use a function ptr to correctly delete malloced data	
	free_nodes(node, free_data);
}

//  Loop to search for years
void year(Node * node){
	bool run = true;
	char readbuf[READSIZE];

	printf("Year Search\nEnter a year or 'back' to return to menu\n");

	while(run){
		printf("Menu/Year > ");
		// get user choice
		fgets (readbuf, READSIZE, stdin);
		
		int len = strlen(readbuf);

		if (len == 0){
			printf("failed to read input");
			break;
		} 

		if (strcmp(readbuf, "back\n") == 0){
			run = false;
		} else {
		
			// strip newline char
			if (readbuf[len-1] == '\n'){
				readbuf[len-1] = 0;
			}

			// void the data
			void * voidptr;

			voidptr = readbuf;
			
			// search for the data using voided data and search year function ptr
			search(node, voidptr, search_year); 
		}
	}
}

// Loop to search for publisher
void publisher(Node * node){
	bool run = true;
	char readbuf[READSIZE];

	printf("Publisher Search\nEnter a publisher or 'back' to return to menu\n");

	while(run){
		printf("Menu/Publisher > ");

		fgets (readbuf, READSIZE, stdin);
		
		int len = strlen(readbuf);

		// make sure something was read
		if (len == 0){
			printf("failed to read input");
			break;
		} 
		
		// check for exiting
		if (strcmp(readbuf, "back\n") == 0){
			run = false;
		} else {
			
			// strip new line
			if (readbuf[len-1] == '\n'){
				readbuf[len-1] = 0;
			}

			void * voidptr;

			voidptr = readbuf;
			
			// search for the publisher by passing the voided data and function ptr
			search(node, voidptr, search_publisher); 
		}
	}
}

// delete a node loop
void delete(Node ** node){
	bool run = true;
	char readbuf[READSIZE];

	printf("Delete a record\nEnter a record index to delete or 'back' to return to the menu\n");

	while(run){
		printf("Menu/Delete > ");

		fgets (readbuf, READSIZE, stdin);
		
		int len = strlen(readbuf);

		if (len == 0){
			printf("failed to read input\n");
			break;
		}

		
		if (strcmp(readbuf, "back\n") == 0){
			run = false;
		} else {
	
			// strip the new line symbol	
			if (readbuf[len-1] == '\n'){
				readbuf[len-1] = 0;
			}
	
			// convert read string to an int
			char * endpoint;

			long num = strtol(readbuf, &endpoint, 10);

			// if the string was converted successfully
			if(!*endpoint){

				// search and delete by index
				bool result = delete_node(node, (int)num, free_data);
				if( result == false) {
					printf("failed\n");
				} else {
					printf("success\n");
				}				
		
			} else {
				printf("failed to convert data to a number\n");
			}	
	
		}
	}
}


// parse the refrence file and create a linked list
bool create_list(FILE **fp, Node ** node) {

	char read[READSIZE];
	Ref * ref;
	char * test;

	// read the file in chuncks until eof is reached
	while (fgets (read, READSIZE, *fp) != NULL){

		// start of a refrence
		if (read[0] == '@'){
			ref = new_refrence();

			char ref_type[256];
			char header[256];
			int success;
		
			// grab the beginning format of the data, due to the two stage formatting
			// basically what is happening is strip '@', read till '{' is encountered
			// don't read '{', read till ',' is encoutnered, and ignore ','
			success = sscanf(read, "@%[^{]{%[^,],", ref_type, header);

			if (success != 2) {
				fprintf(stderr, "failed parse; %s\n", read);
			}

			add_header(ref_type, header, ref);

			//printf("%d, %s, %s\n", success, ref_type, header); 

		 	bool parse = {true};

			// grab the refrences until an '}' is encountered or end of file
			// could also add in deliminting by finding a new node but 
			while(parse) {

				test = fgets(read, READSIZE, *fp);	

				// check the error condition of a malformed ref at end
				if( test == NULL){
					fprintf(stderr, "malformed refrence");
					return false;
				}

				// end of a refrence
				if (read[0] == '}'){
					parse = false;
				
					// cast the ref to linked list
					void *voidptr;
					voidptr = ref;

					// add ref to linked list
					*node = add_node(*node, voidptr);
				} else {
					char type[READSIZE];
					char data[READSIZE];

					// grab type and information 
					success = sscanf(read, " %[^=]=%[^\n]", type, data);


					if(success != 2) {
						fprintf(stderr, "failed to parse: %s\n", read);
					} else {

						char strip[256];
						
						// strip data of ending and beginning, must probe
						strip_chars(strip, data);
						
						//printf("%d, %s, %s\n", success, type, data);
						//printf("stripped: %s\n", strip);

						// add data to refrence
						add_data(type, strip, ref);
					}	
				}
			}
		}
	}

	return true;
}

// strip data of beginning and endings and place in
// destination char array
void strip_chars(char * dest, char * src) {

	int str_len = strlen(src);
	
	memset(dest, 0, READSIZE);

	// you have to strip out the \r\n line endings on unix, using dos2unix or equivalent
	// or you'll have to change this bounds check
	if (src[str_len-1] == ',') {
		memmove(dest, src+1, str_len - 3);
	} else {
		memmove(dest, src+1, str_len - 2);
	}
}

// add_header adds the type and header when starting a new
// refrence.
bool add_header(char * ref_type, char * header, Ref * ref){
	strcpy(ref->type, ref_type);
	strcpy(ref->header, header);
	return true;
}


// add_data determines which type was read by a string comparison
// checks if the data has not been set and sets the data for 
// the refrence.
bool add_data(char * type, char * data, Ref * ref) {

	// general format is to check the type, and then check if the data
	// is empty, tough luck for those refrences that have multiple same data
	// types, then copy the data to the ref is passes both
	
	// also, avoid strcpy, its unsafe
	// it doesn't check the length of the buffers
	// unfortunatly, the options are poor,
	// Microsofts, _s version is apparently not safe, 
	// and other options are not cross platform or are in 
	// later versions of the C standard or are self rolled
	// the current best method is snprintf, but have to be careful about
	// microsofts _snprintf alternative

	if(strcmp(type, "title") == 0) {
		if(strlen(ref->title) == 0){
			strcpy(ref->title, data);
		}
	} else if(strcmp(type, "author") == 0) {
		if(strlen(ref->author) == 0){
			strcpy(ref->author, data);
		}
	} else if(strcmp(type, "journal") == 0) {
		if(strlen(ref->journal) == 0){
			strcpy(ref->journal, data);
		}
	} else if(strcmp(type, "volume") == 0) {
		if(strlen(ref->volume) == 0){
			strcpy(ref->volume, data);
		}
	} else if(strcmp(type, "number") == 0) {
		if(strlen(ref->number) == 0){
			strcpy(ref->number, data);
		}
	} else if(strcmp(type, "pages") == 0) {
		if(strlen(ref->pages) == 0){
			strcpy(ref->pages, data);
		}
	} else if(strcmp(type, "year") == 0) {
		if(strlen(ref->year) == 0){
			strcpy(ref->year, data);
		}
	} else if(strcmp(type, "publisher") == 0) {
		if(strlen(ref->publisher) == 0){
			strcpy(ref->publisher, data);
		}
	} else if(strcmp(type, "booktitle") == 0) {
		if(strlen(ref->booktitle) == 0){
			strcpy(ref->booktitle, data);
		}
	} else if(strcmp(type, "organization") == 0) {
		if(strlen(ref->organization) == 0){
			strcpy(ref->organization, data);
		}
	} else if(strcmp(type, "note") == 0) {
		if(strlen(ref->note) == 0){
			strcpy(ref->note, data);
		}
	} else if(strcmp(type, "howpublished") == 0) {
		if(strlen(ref->howpublished) == 0){
			strcpy(ref->howpublished, data);
		}
	} else {
		fprintf(stderr, "unrecongnized type: %s", type);
		return false;
	}
	
	return true;
}
