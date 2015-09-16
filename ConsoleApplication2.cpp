#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*********************************************/
/** Node structure and associated functions **/
/*********************************************/

struct node {
	// data structure to hold the word
	char *word;	//The word represented by this node
	char *lcword; //The word in lowercase
	struct node *next;	//The next word in the list
	struct node *prev; // The previous word in the list
};


struct linked_list {
	// data structure to hold the head of list
	struct node *head;

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
struct node *new_node(char *word) {
    struct node *n = (struct node *)(malloc(sizeof(struct node)));
	n->word = word;
	n->lcword = to_lower_case(word);
	n->prev = NULL;
	n->next = NULL;
}

// Free node from memory
void free_node (struct node *n) {
  if (n != NULL) {
    free(n->word);
    free(n);
  }
}

// Free all nodes in list
void free_all_nodes (struct node *n) {
  if (n != NULL) {
    //assert(n->prev == NULL);
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
void print_list(struct node *list_head) {
	for(struct node *to_print = list_head; to_print != NULL; to_print = to_print->next) {
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

/** REDEFINED FOR OPTIMIZED SOLUTION

// Insert the word in the linked list
void insert(void *word);
**/



/** REDEFINION OF FUNCTION: insert **/
struct node *insert(struct node *word_node, struct node *list_head) {
	char *new_word = word_node->lcword;
	printf("\n-------------------\nAdding word: %s\n", new_word);

	// If list is empty, make new node head
	if(list_head == NULL) {
		printf("---- No list; add as head\n");
		list_head = word_node;
		return list_head;
	}
	
	// At least one node in list
	
	// Iterate through list to find position
	struct node *current_node = list_head;
	
	/*struct node *prev_node = NULL;
	/*do {
		if(( strcmp((new_word), (current_word)) < 0 )) {
			// New word comes before current word
			
		}
	} while(current_node->next == NULL);
	while(strcmp((new_word), (current_word)) < 0) {
		if(current_word->next != NULL) { // No words after current
			break;
		}
		
	}
	
	if(current_node->prev == NULL) { // New word precedes head
		printf("-- Add new word to head\n");
		// Update head
		list_head->prev = word_node;
		word_node->next = list_head;
		list_head = word_node;
		// REMINDER: word_node->prev is NULL by default
	}*/
	
	
	//struct node *after = current_node->next;
	//for(current_node = list_head; current_node->next != NULL; current_node = current_node->next) {
	for(current_node = list_head; strcmp((new_word), (current_node->lcword)) >= 0; current_node = current_node->next) {
	
		char *current_word = current_node->lcword;
		printf("-- Currently looking at: %s\n", current_word);
		
		// Update pointers
		
		// If word is smaller than current, 
		//if( strcmp((new_word), (current_word)) < 0 ) {
		//	printf("---- New word is smaller... end loop \n");
		//	current_word->prev
		//	break;
		//}
		
		// If current node is last in list, don't update
		if(current_node->next == NULL) {
			break;
		}
		
		printf("---- New word is larger... \n");
	}
	
	if(current_node->prev == NULL) { // New word precedes head
		printf("-- Add new word to head\n");
		// Update head
		list_head->prev = word_node;
		word_node->next = list_head;
		list_head = word_node;
		// REMINDER: word_node->prev is NULL by default
	} else { // Insert after head
		struct node *after_current = current_node->next;
		current_node->next = word_node;
		word_node->prev = current_node;
		word_node->next = after_current;
		if(after_current != NULL) {
			printf("-- After current is the word: %s\n", after_current->word);
			after_current->prev = word_node;
		}
		
		
	}
	
	/*for(current_node = list_head; strcmp((new_word), (current_node->lcword)) >= 0; current_node = current_node->next) {
	
		char *current_word = current_node->lcword;
		printf("-- Currently looking at: %s\n", current_word);
		
		// If in loop, word to insert comes after current word
		printf("---- New word is larger... \n");
		
		// If current node is last in list, don't update
		if(current_node->next == NULL) {
			word_node->prev = current_node;
			word_node->next = current_node->next;
			current_node->next = word_node;
			return list_head;
		}
		
		
	}
	
	// If in loop, word to insert comes before current
	printf("---- New word is prior... \n");
	word_node->prev = current_node->prev; // NULL if head
	word_node->next = current;
	if(current_node != list_head) { // Middle
		current->prev->next = word_node;
		current->prev = 
	}*/
	
	
	
	/*if(current_node == NULL) { // Reached end of list
		current_node = current_node->prev;
	}
	// Update pointers
	struct node *after_current = current_node->next;
	current_node->next = word_node;
	word_node->prev = current_node;
	word_node->next = after_current;
	
	if(current_node->prev == NULL) { // New word precedes head
		printf("-- Add new word to head\n");
		// Update head
		list_head->prev = word_node;
		word_node->next = list_head;
		list_head = word_node;
		// REMINDER: word_node->prev is NULL by default
	} else { // Insert after head
		struct node *after_current = current_node->next;
		current_node->next = word_node;
		word_node->prev = current_node;
		word_node->next = after_current;
		if(after_current != NULL) {
			printf("-- After current is the word: %s\n", after_current->word);
			after_current->prev = word_node;
		}
		
		
	}*/
	
	
	printf("\nNew List: ");
	print_list(list_head);
	printf("\n\n");
	return list_head;
	
	
} // end insert





/**********************************/
/** Write Results to Output File **/
/**********************************/

// Write to a new file
bool write_text(char *filename, void *buffer, int size_of_buffer)
{
	FILE *output_file;
	output_file = fopen(filename, "wb");
	fwrite(buffer, (size_t)sizeof(char), (size_t)size_of_buffer, output_file);
	fclose(output_file);
	return 0;
}

// Note: You can use a helper function to insert. 
// The main purpose of the function is to find the location in existing linked list 
// to insert the new word.

// create the list and return the alphabetically sorted output
int main() {

    // Declare buffer to read from file
	char *buffer;
	
	// Read contents from file
	char input_file[] = "input.txt";
	int size_of_buffer = buffer_size(input_file);
	buffer = (char*) malloc(sizeof(char) * size_of_buffer);
	read_text(input_file, buffer, size_of_buffer);
	buffer[size_of_buffer] = '\0'; // Mark end of string
	printf("The bytes read are\n[%s]\n", buffer);
	
	// Define list
	struct node *list_head = NULL;
	struct linked_list *list_of_words = (struct linked_list*) malloc(sizeof(linked_list));
	struct node *to_add;
	
	printf ("Splitting string \"%s\" into tokens:\n",buffer);
	
	// Split words in buffer
	for (char *current_word = strtok(buffer, " "); current_word != NULL; current_word = strtok (NULL, " ")) {
	  
	  // Create new node and add to head
	  to_add = new_node(current_word);
	  
	  /*if(list_head == NULL) {
		list_head = to_add;
	  } else {
		struct node *temp = list_head;
		list_head = to_add;
		list_head->next = temp;
	  }*/
	  
	  
	  // Change position
	  list_head = insert(to_add, list_head);
	  //insert(to_add, list_of_words);
	}
	
	/*PRINT*/
	for(struct node *to_print = list_head; to_print != NULL; to_print = to_print->next) {
		printf("%s ", to_print->word);
	}
	
	printf("\n'hi' compared to 'bi' is: %d", strcmp("hi","bi"));
	
	
	// Write to output file
	char output_file[] = "output.txt";
	write_text(output_file, buffer, size_of_buffer);
	
	// Free memory and exit
	free(buffer);
	return 0;
}
