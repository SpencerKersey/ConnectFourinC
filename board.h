#include "common.h"

/**
 * This method intitializes the board
*/
void initializeBoard( ConnectFourBoard *board );

/**
 * This method resets the board to the beginning
*/
void resetBoard( ConnectFourBoard *board );

/**
 * This method frees the board when the program is done using it
*/
void freeBoard( ConnectFourBoard *board );

/**
 * This method prints out the board to the command-line
*/
void printBoard( ConnectFourBoard *board );

bool playPiece( ConnectFourBoard *board, int col );

bool checkWin( ConnectFourBoard *board );

void runBoardTests( ConnectFourBoard *board );