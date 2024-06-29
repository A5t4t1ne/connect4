#ifndef BOARD_H
#define BOARD_H

/******************************************************
 * Includes
 ******************************************************/
#include <stdint.h>

/******************************************************
 * Constants
 ******************************************************/
#define ROWS 6       //!< Number of rows
#define COLS 7       //!< Number of columns
#define EMPTY ' '    //!< Empty cell character
#define CELL_WIDTH 4 //!< Width of a cell in characters. Includes the first but not the last border.

#define ROW_OFFSET 3
#define COL_OFFSET 2

#define COLOR_PAIR_RED 1   //!< Color pair for player X, used for the color of the pieces
#define COLOR_PAIR_GREEN 2 //!< Color pair for player O, used for the color of the pieces

#define ASCII_RED "\033[31m"   //!< ASCII color code for red
#define ASCII_GREEN "\033[32m" //!< ASCII color code for green
#define ASCII_RESET "\033[0m"  //!< ASCII color code to reset the color

#define ERR_SUCCESS 0  //!< Error code for success
#define ERR_COL_FULL 1 //!< Error code for column full

#define ANIMATION_DELAY_MS 50 //!< Piece drop animation delay in milliseconds

#define BITBOARD_X 0 //!< Bitboard index for player X
#define BITBOARD_O 1 //!< Bitboard index for player O

/******************************************************
 * Types
 ******************************************************/
typedef struct
{
    uint64_t bitboards[2];  //!< Store the bitboards for each player
    int height[COLS];       //!< Store the height of each column
    int counter;            //!< Counter for the number of moves played
    int moves[ROWS * COLS]; //!< Store the moves/columns played
} Board;

typedef enum
{
    PLAYER_X = 0,
    PLAYER_O = 1
} Player;

/******************************************************
 * Function Headers
 ******************************************************/
void reset_board(Board *board);
void draw_board(const Board const *board, int selected_col);
void field_start_pos(int *x, int *y);
int drop_piece(Board *board, int col);
bool is_winner(const long bitboard);

#endif // BOARD_H