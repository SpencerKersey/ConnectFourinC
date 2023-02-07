#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "board.h"

/**
 * Print out an error message and exit.
 */
static void fail( char const *message ) {
  fprintf( stderr, "%s\n", message );
  exit( 1 );
}

/**
 * This method intitializes the board
*/
void initializeBoard( ConnectFourBoard *board ) {
    // Map the shared memory into my address space
    board = ( ConnectFourBoard * )malloc( sizeof( ConnectFourBoard ) );
    if ( board == ( ConnectFourBoard * ) - 1 )
        fail( "Can't map shared memory segment into address space" );

    for( int i = 0; i < BOARD_HEIGHT; i++ ) {
        for( int j = 0; j < BOARD_WIDTH; j++ ) {
            board->boardArray[ i ][ j ] = ' ';
        }
    }

    board->currPlayer = 'y';
}

/**
 * This method resets the board to the beginning
*/
void resetBoard( ConnectFourBoard *board ) {
    for( int i = 0; i < BOARD_HEIGHT; i++ ) {
        for( int j = 0; j < BOARD_WIDTH; j++ ) {
            board->boardArray[ i ][ j ] = ' ';
        }
    }

    board->currPlayer = 'y';
}

/**
 * This method frees the board when the program is done using it
*/
void freeBoard( ConnectFourBoard *board ) {
    free( board );
}

/**
 * This method prints out the board to the command-line
*/
void printBoard( ConnectFourBoard *board ) {
    if( board->currPlayer == 'y' ) {
        printf(" Yellow's Turn\n");
    } else {
        printf("  Red's Turn\n");
    }

    for( int i = 0; i < BOARD_HEIGHT; i++ ) {
        for( int j = 0; j < BOARD_WIDTH; j++ ) {
            printf( "|%c", board->boardArray[ i ][ j ] );
        }
        printf("|\n");
    }
}

bool playPiece( ConnectFourBoard *board, int col ) {
    for( int i = BOARD_HEIGHT - 1; i > 0; i-- ) {
        if( board->boardArray[ i ][ col ] == ' ' ) {
            board->boardArray[ i ][ col ] = board->currPlayer;

            if( board->currPlayer == 'y' ) {
                board->currPlayer = 'r';
            } else {
                board->currPlayer = 'y';
            }
            return true;
        }
    }
    return false;
}

bool checkWin( ConnectFourBoard *board ) {
    int piecesInRow = 0;
    int tmpPiecesInRow = 0;

    // Check for win horizontally
    for( int i = 0; i < BOARD_HEIGHT; i++ ) {
        for( int j = 0; j < BOARD_WIDTH; j++ ) {
            if( board->boardArray[ i ][ j ] != ' ' && board->boardArray[ i ][ j ] != board->currPlayer ) {
                tmpPiecesInRow++;
            } else {
                if( tmpPiecesInRow > piecesInRow ) {
                    piecesInRow = tmpPiecesInRow;
                }
                tmpPiecesInRow = 0;
            }
        }
    }
    if( piecesInRow >= 4 ) {
        return true;
    }

    // Check for win vertically
    tmpPiecesInRow = 0;
    for( int i = 0; i < BOARD_WIDTH; i++ ) {
        for( int j = 0; j < BOARD_HEIGHT; j++ ) {
            if( board->boardArray[ j ][ i ] != ' ' && board->boardArray[ j ][ i ] != board->currPlayer ) {
                tmpPiecesInRow++;
            } else {
                if( tmpPiecesInRow > piecesInRow ) {
                    piecesInRow = tmpPiecesInRow;
                }
                tmpPiecesInRow = 0;
            }
        }
    }
    if( piecesInRow >= 4 ) {
        return true;
    }

    // Check for win diagonally, left to right
    tmpPiecesInRow = 0;
    for( int i = 0; i < BOARD_HEIGHT; i++ ) {
        int x = i;
        int y = 0;
        while( x > 0 && y < BOARD_WIDTH ) {
            if( board->boardArray[ x ][ y ] != ' ' && board->boardArray[ x ][ y ] != board->currPlayer ) {
                tmpPiecesInRow++;
            } else {
                if( tmpPiecesInRow > piecesInRow ) {
                    piecesInRow = tmpPiecesInRow;
                }
                tmpPiecesInRow = 0;
            }

            x--;
            y++;
        }
    }
    if( piecesInRow >= 4 ) {
        return true;
    }

    // Check for win diagonally, right to left
    tmpPiecesInRow = 0;
    for( int i = 0; i < BOARD_HEIGHT; i++ ) {
        int x = 0;
        int y = i;
        while( x < BOARD_HEIGHT && y < BOARD_WIDTH ) {
            if( board->boardArray[ x ][ y ] != ' ' && board->boardArray[ x ][ y ] != board->currPlayer ) {
                tmpPiecesInRow++;
            } else {
                if( tmpPiecesInRow > piecesInRow ) {
                    piecesInRow = tmpPiecesInRow;
                }
                tmpPiecesInRow = 0;
            }

            x++;
            y++;
        }
    }
    if( piecesInRow >= 4 ) {
        return true;
    }

    return false;
}

void runBoardTests( ConnectFourBoard *board ) {
    resetBoard( board );

    // Test Horizontal WinCase
    printBoard( board );
    playPiece( 1, board );
    playPiece( 6, board );
    playPiece( 2, board );
    playPiece( 6, board );
    playPiece( 3, board );
    playPiece( 6, board );
    playPiece( 4, board );
    printBoard( board );
    if( checkWin( board ) == true ) {
        printf("Won - working\n");
    } else {
        printf("Lost - not working\n");
    }

    resetBoard( board );

    // Test Vertical WinCase
    printBoard( board );
    playPiece( 2, board );
    playPiece( 3, board );
    playPiece( 2, board );
    playPiece( 3, board );
    playPiece( 2, board );
    playPiece( 3, board );
    playPiece( 2, board );
    printBoard( board );
    if( checkWin( board ) == true ) {
        printf("Won - working\n");
    } else {
        printf("Lost - not working\n");
    }

    resetBoard( board );

    // Test RLDiagonal WinCase
    printBoard( board );
    playPiece( 0, board );
    playPiece( 1, board );
    playPiece( 1, board );
    playPiece( 2, board );
    playPiece( 6, board );
    playPiece( 2, board );
    playPiece( 2, board );
    playPiece( 3, board );
    playPiece( 6, board );
    playPiece( 3, board );
    playPiece( 6, board );
    playPiece( 3, board );
    playPiece( 3, board );
    printBoard( board );
    if( checkWin( board ) == true ) {
        printf("Won - working\n");
    } else {
        printf("Lost - not working\n");
    }

    resetBoard( board );

    // Test LRDiagonal WinCase
    printBoard( board );
    playPiece( 6, board );
    playPiece( 5, board );
    playPiece( 5, board );
    playPiece( 4, board );
    playPiece( 0, board );
    playPiece( 4, board );
    playPiece( 4, board );
    playPiece( 3, board );
    playPiece( 0, board );
    playPiece( 3, board );
    playPiece( 0, board );
    playPiece( 3, board );
    playPiece( 3, board );
    printBoard( board );
    if( checkWin( board ) == true ) {
        printf("Won - working\n");
    } else {
        printf("Lost - not working\n");
    }
}