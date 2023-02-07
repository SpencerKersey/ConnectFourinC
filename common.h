// Height of the playing area.
#define BOARD_HEIGHT 6

// Width of the playing area.
#define BOARD_WIDTH 7

// Make the board struct and typedef it for the future
typedef struct ConnectFourBoardStruct
{
  char boardArray[ 6 ][ 7 ];
  char currPlayer;
} ConnectFourBoard;
