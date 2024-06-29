#ifndef BOARD_H
#define BOARD_H

/******************************************************
 * Includes
 ******************************************************/
#include <stdint.h>

/******************************************************
 * Constants
 ******************************************************/
#define ROWS 6
#define COLS 7
#define EMPTY ' '
#define CELL_WIDTH 4

#define ROW_OFFSET 3
#define COL_OFFSET 2

#define COLOR_PAIR_RED 1
#define COLOR_PAIR_GREEN 2

#define ASCII_RED "\033[31m"
#define ASCII_GREEN "\033[32m"
#define ASCII_RESET "\033[0m"

#define ERR_SUCCESS 0
#define ERR_COL_FULL 1

#define NO_WINNER 0
#define WINNER_FOUND 1

#define ANIMATION_DELAY_MS 50

#define BITBOARD_X 0
#define BITBOARD_O 1


/******************************************************
 * Types
 ******************************************************/
typedef struct
{
    uint64_t bitboards[2];                          //!< Store the bitboards for each player
    int height[COLS];  //!< Store the height of each column
    int counter;                                //!< Counter for the number of moves played
    int moves[ROWS * COLS];                   //!< Store the moves/columns played
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