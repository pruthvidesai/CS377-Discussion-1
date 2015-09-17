/*************************/
/** ASSIGNMENT OVERVIEW **/
/*************************/

// COURSE: CMPSCI 377 (Operating Systems)
// DATE: 9-17-15
// TEAM MEMBERS: Mary Moser, Pruthvi Desai
// ASSIGNMENT: Lab 1 Warm-Up Exercise
// OBJECTIVE: Read contents of file,
//            sort words alphabetically, output to new file
// INSTRUCTIONS FOR RUNNING: On Linux Machine:
//                           gcc ConsoleApplication2.cpp -o ConsoleApp
//                           ./ConsoleApp

/**************/
/** Includes **/
/**************/

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*********************************************/
/** Node Structure and Associated Functions **/
/*********************************************/

struct node {
	// data structure to hold the word
	char *word;	//The word represented by this node
	char *lcword; //The word in lowercase
	node *next;	//The next word in the list
	node *prev; // The previous word in the list
};

// Convert word to lower case
char *to_lower_case(char *word) {
	int len = strlen(word);
	char *copy = (char *)(malloc(len+1));
	strcpy(copy, word);
	
	int i=0;
	char c;
	for (int i = 0; i < len; i++) {
		copy[i] = tolower(copy[i]);
	}
	return copy;
}

// Create and initialize new node (not attached to any list)
node *new_node(char *word) {
    node *n = (node *)(malloc(sizeof(node)));
	n->word = word;
	n->lcword = to_lower_case(word);
	n->prev = NULL;
	n->next = NULL;
}

// Free node from memory
void free_node (node *n) {
  if (n != NULL) {
    free(n->word);
    free(n);
  }
}

// Free all nodes in list
void free_all_nodes (node *n) {
  if (n != NULL) {
    free_all_nodes(n->next);
    free_node(n);
  }
}

/******************/
/** Reading File **/
/******************/

// Read the text from file and store it in a buffer
bool read_text(char *filename, void *buffer, int size_of_buffer)
{
	FILE *input_file = NULL;
	input_file = fopen(filename, "r");

	if (NULL == input_file)
	{
		printf("\n File doesn't exist!\n");
		return true;
	}

	int read = fread(buffer, (size_t)sizeof(char), (size_t)size_of_buffer, input_file);
	printf("The bytes read are\n[%s]\n", buffer);
	//printf("Pointer size is: %d vs %d\n", size_of_buffer * sizeof(char), read);
	//printf("Sizeof(buffer): %d\n", sizeof(buffer));
	fclose(input_file);
}

// Get file size from input file
int buffer_size(char *filename)
{
	FILE *input_file = fopen(filename, "r");
	fseek(input_file, 0, SEEK_END);
	int size = ftell(input_file);
	//printf("%ld\n", size);
	fclose(input_file);
	return size;
}

/************************/
/** PRINTING FUNCTIONS **/
/************************/
/*PRINT*/
void print_list(node *list_head) {
	for(node *to_print = list_head; to_print != NULL; to_print = to_print->next) {
		printf("%s ", to_print->word);
	}
}


/****************************/
/** Sorting Alphabetically **/
/****************************/


/** REMOVED FOR OPTIMIZED SOLUTION

// Get the next word from the buffer
bool next_word(void *buffer, void *word) {
}
**/

/** REMOVED FOR OPTIMIZED SOLUTION

// Insert the word in the linked list
void insert(void *word);
**/

// Note: You can use a helper function to insert. 
// The main purpose of the function is to find the location in existing linked list 
// to insert the new word.


/** REDEFINION OF FUNCTION: insert **/
node *insert(node *to_insert, node *list_head) {

	char *new_word = to_insert->lcword;

	// If list is empty, make new node head
	if(list_head == NULL) {
		list_head = to_insert;
		return list_head;
	}
	
	// At least one node in list
	
	// Iterate through list to find position
	node *current_node = list_head;
	node *previous = NULL; // Keep track of previous
	while(1) {
	
		char *current_word = current_node->lcword;
		
		// Break if new word comes before current word
		if(strcmp(new_word, current_word) <= 0) {
			break;
		}
		
		// If here, word comes after current
		
		// If current word is tail, add word to tail
		if(current_node->next == NULL) {
			to_insert->next = current_node->next;
			to_insert->prev = current_node;
			current_node->next = to_insert;
			return list_head;
		}
		
		current_node = current_node->next;
	}
	
	// Insert word before current and after current->previous
	// REMINDER: to_insert->prev and list_head->prev are NULL by default
	to_insert->next = current_node;
	to_insert->prev = current_node->prev;
	if(current_node != list_head) { // Inserting in middle
		current_node->prev->next = to_insert;
		current_node->prev = to_insert;
	} else { // Inserting at head
		to_insert->next = list_head;
		list_head->prev = to_insert;
		list_head = to_insert; // Head points to new node
	}
	
	return list_head;
	
} // end insert

/**********************************/
/** Write Results to Output File **/
/**********************************/

// Write to a new file
bool write_text(char *filename, node *list_head)
{
	FILE *output_file;
	output_file = fopen(filename, "wb");
	if(list_head != NULL) { // List not empty
		// Write first word -- no spaces
		fprintf(output_file, "%s", list_head->word);
		// Write rest of list -- words preceded by spaces
		for(node *to_print = list_head->next; to_print != NULL; to_print = to_print->next) {
			fprintf(output_file, " %s", to_print->word);
		}
	}
	fclose(output_file);
	return 0;
}

/**********/
/** Main **/
/**********/

// create the list and return the alphabetically sorted output
int main() {

    // Declare buffer to read from file
	char *buffer;
	
	// Read contents from file
	char input_file[] = "input.txt";
	int size_of_buffer = buffer_size(input_file);
	buffer = (char*) malloc(sizeof(char) * size_of_buffer);
	read_text(input_file, buffer, size_of_buffer);
	buffer[size_of_buffer] = '\0'; // Mark end of string (for safety)
	
	// Define list
	node *list_head = NULL;
	node *to_add;
	
	// $ TESTING ONLY: Print
	printf ("\nSplitting string \"%s\" into tokens:\n",buffer);
	
	// Split words in buffer
	for (char *current_word = strtok(buffer, " "); current_word != NULL; current_word = strtok (NULL, " ")) {
	  
	  // Create new node and add to head
	  to_add = new_node(current_word);
	 
	  // Change position
	  list_head = insert(to_add, list_head);
	  
	}
	
	// $ TESTING ONLY: Print
	printf ("\nWrite following results to file:\n",buffer);
	print_list(list_head);
	printf("\n");
	
	
	// Write to output file
	char output_file[] = "output.txt";
	write_text(output_file, list_head);
	
	// Free memory and exit
	free(buffer);
	return 0;
}
