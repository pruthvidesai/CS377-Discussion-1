#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLEN 100

struct node {
	// data structure to hold the word
	char *word;	//The word represented by this node
	struct node *next;	//The next word in the list
};

// Read the text from file and store it in a buffer
bool read_text(char *filename, void *buffer, int size_of_buffer)
{
	FILE *input_file = NULL;
	input_file = fopen(filename, "r");

	//memset(buffer, 0, size_of_buffer);

	if (NULL == input_file)
	{
		printf("\n File doesn't exist!\n");
		return true;
	}

	if (size_of_buffer*MAXLEN != fread(buffer, size_of_buffer, MAXLEN, input_file))
	{
		printf("\nRead failed\n");
		return true;
	}

	printf("\n The bytes read are %s \n", buffer);
	fclose(input_file);
}

// Get the next word from the buffer
bool next_word(void *buffer, void *word);

// Insert the word in the linked list
void insert(void *word);

// Note: You can use a helper function to insert. 
// The main purpose of the function is to find the location in existing linked list 
// to insert the new word.

// create the list and return the alphabetically sorted output
int main() {
	//buffer
	char *buffer[MAXLEN];
	read_text("input.txt", buffer, MAXLEN);
}
