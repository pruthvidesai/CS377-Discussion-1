//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
	// data structure to hold the word
	char *word;	//The word represented by this node
	struct node *next;	//The next word in the list
	struct node *prev; // The previous word in the list
};

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

// Get the next word from the buffer
bool next_word(void *buffer, void *word);

// Insert the word in the linked list
void insert(void *word);

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
	
	
	// Write to output file
	char output_file[] = "output.txt";
	write_text(output_file, buffer, size_of_buffer);
	
	// Free memory and exit
	free(buffer);
	return 0;
}
