/** 
    @file input.c
    @author Spencer G Kersey (sgkersey)
    This component reads in a line of text which can be arbitraryly large as it uses a
    dynamically sized array.
*/

#include "input.h"

char *readCommand( FILE *fp )
{
    // Allocate a string with a small, initial capacity.
    int capacity = INIT_CAPACITY;
    char *output = ( char * ) malloc( capacity * sizeof( char ) + 1 );

    // Number of characters we're currently using.
    int len = 0;
  
    // Read from this file until we reach end-of-file, storing all characters
    // in buffer. Keep enlarging the buffer as needed until it contails the
    // contents of the whole file.
    char current;
    while( fscanf( fp, "%c", &current ) == 1 ) {
        // Exit loop if it reaches a newline character or EOF
        if( current == '\n' || current == EOF || current == ' ' ) {
            break;
        }

        // If the buffer is not large enough to hold the new char then resize the buffer
        if( len >= capacity ) {
            capacity *= CAP_MULT;
            output = realloc( output, capacity * sizeof( char ) + 1 );

            // Make sure realloc was successful, and if not then exit the program
            if( output == NULL ) {
                free( output );
                exit( EXIT_FAILURE );
            }
        }
        output[ len++ ] = current;
    }

    // Return null if there is nothing more or output the command as a string
    if( len == 0 ) {
        free( output );
        return NULL;
    }
    output[ len ] = '\0';
    return output;
}

char *readInteger( FILE *fp )
{
    // Create an integer to hold the final number
    int output = 0;

    // Multiplier to get the correct number to add.
    int mult = 1;
  
    // Read from this file until we reach end-of-file, storing all characters
    // in buffer. Keep enlarging the buffer as needed until it contails the
    // contents of the whole file.
    char current;
    while( fscanf( fp, "%c", &current ) == 1 ) {
        // Exit loop if it reaches a newline character or EOF
        if( current == '\n' || current == EOF || current == ' ' ) {
            // Return null if there is nothing more or output the command as a string
            if( mult == 1 )
                return NULL;
            break;
        }

        output += ( ( current - 48 ) * mult );
        mult *= 10;
    }

    return output;
}


