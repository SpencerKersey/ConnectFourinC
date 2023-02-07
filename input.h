/** 
    @file input.h
    @author Spencer G Kersey (sgkersey)
    This component reads in a line of text which can be arbitraryly large as it uses a
    dynamically sized array.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/** Holds the multiplier for enlargening the capacity */
#define CAP_MULT 2

/** Holds the initial capcity for the string and list */
#define INIT_CAPACITY 5

/**
 * This function reads a single line of input from the given file and returns it as a string
 * inside a block of dynamically allocated memory. You can use this function to read commands
 * from the user and to read employee descriptions from an employee list file. Inside the
 * function, you should implement a resizable array to read in a line of text that could be
 * arbitrarily large. If there's no more input to read, this function should return NULL.
 * Since this function returns a pointer to dynamically allocated memory, some other code will
 * be responsible for eventually freeing that memory (to avoid a memory leak).
 *
 * @param fp is the file to read from
 */
char *readCommand( FILE *fp );

char *readInteger( FILE *fp );
