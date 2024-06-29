/******************************************************
 * main.c
 *
 * Created on: 28.06.2024
 *
 * Author: David Jäggli
 *
 * Description: A file containing all the logic for the game board.
 *
 ******************************************************/

/******************************************************
 * Includes
 ******************************************************/
#include <ncurses.h>

#include "board.h"
#include "log.h"

/******************************************************
 * Globals
 ******************************************************/
/**
 * The default game board configuration.
 */
const Board defaultBoard = {
    .bitboards = {0},
    .counter = 0,
    .moves = {0},
    .height = {0, 7, 14, 21, 28, 35, 42}};

/******************************************************
 * Function Definitions
 ******************************************************/
/**
 * Reset the game board to the default configuration and clear the screen.
 * @param board The current board
 */
void reset_board(Board *board)
{
    *board = defaultBoard;

    clear();
}

/**
 * Draw the game board.
 * The argument @ref selected_col is used to put the cursor above the selected column.
 * @param board The current board
 * @param selected_col The selected column
 */
void draw_board(const Board const *board, int selected_col)
{
    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    int start_y = (max_y - ROWS) / 2;
    int start_x = (max_x - COLS * CELL_WIDTH) / 2;

    // clear first two lines
    for (int i = 0; i < 2; i++)
    {
        mvprintw(start_y - 2 + i, start_x, "                              ");
    }

    selected_col = (selected_col + COLS) % COLS; // insurance :)
    int curr_cursor_x = start_x + selected_col * CELL_WIDTH + 2;
    mvprintw(start_y - 2, curr_cursor_x, "|");
    mvprintw(start_y - 1, curr_cursor_x, "v");

    int bb_bit = 0, coord_x = 0, coord_y = 0;
    for (int y = 5; y >= 0; y--)
    {
        for (int x = 0; x < COLS; x++)
        {
            bb_bit = (x * 7) + y;

            coord_x = start_x + x * CELL_WIDTH;
            coord_y = start_y + (5 - y);

            mvprintw(coord_y, coord_x, "| ");
            if (board->bitboards[0] & (1l << bb_bit))
            {
                attron(COLOR_PAIR(1));
                mvprintw(coord_y, coord_x + 2, "X ");
                attroff(COLOR_PAIR(1));
            }
            else if (board->bitboards[1] & (1l << bb_bit))
            {
                attron(COLOR_PAIR(2));
                mvprintw(coord_y, coord_x + 2, "O ");
                attroff(COLOR_PAIR(2));
            }
            else
            {
                mvprintw(coord_y, coord_x + 2, "   ");
            }
        }
        mvprintw(coord_y, coord_x + CELL_WIDTH, "|");
    }

    mvprintw(start_y + ROWS, start_x, "+---------------------------+");

    refresh();
}

/**
 * Calculate the starting position of the field.
 * The field will be centered on the screen. Used in @ref draw_board().
 * @param x The x position
 * @param y The y position
 */
void field_start_pos(int *x, int *y)
{
    int max_y = 0, max_x = 0;
    getmaxyx(stdscr, max_y, max_x);

    *x = (max_x - COLS * CELL_WIDTH) / 2;
    *y = (max_y - ROWS) / 2;
}

/**
 * Drop a piece in a column
 * @param board The current board
 * @param col The column to drop the piece in
 * @return int Error code
 */
int drop_piece(Board *board, int col)
{
    if (col < 0 || col >= COLS || board->height[col] > (ROWS * col * 7))
        return ERR_COL_FULL;

    board->bitboards[board->counter & 1] |= 1l << board->height[col];
    board->moves[board->counter] = col;
    board->counter++;
    board->height[col]++;

    draw_board(board, col);

    return ERR_SUCCESS;

    // TODO: Implement animation

    // int i;
    // for (i = 0; i < ROWS; i++)
    // {
    //     if (board[i][col] != EMPTY)
    //     {
    //         break;
    //     }
    //     board[i][col] = piece;
    //     draw_board(board, col);
    //     refresh();
    //     usleep(ANIMATION_DELAY_MS * 1000);
    //     board[i][col] = ' ';
    // }
    // if (i == 0)
    // {
    //     return ERR_COL_FULL;
    // }
    // else
    // {
    //     board[i - 1][col] = piece; // Place the piece at the final position
    //     return ERR_SUCCESS;
    // }
}

/**
 * List all possible moves
 * @param board The current board
 * @return int* A list of possible moves
 */
int *list_moves(const Board *board)
{
    int cols[COLS] = {0};
    for (size_t i = 0; i < COLS; i++)
    {
        if (board->height[i] < 7 * i)
            cols[i] = 1;
    }
    return cols;
}

/**
 * Check if a bitboard contains 4 in a row
 * @param bitboard The bitboard of the player you want to check
 * @return bool
 */
bool is_winner(const long bitboard)
{
    int directions[4] =
        {
            1, // vertical
            7, // horizontal
            6, // \-diagonal
            8  // /-diagonal
        };

    long bb;
    for (size_t i = 0; i < 4; i++)
    {
        bb = bitboard & (bitboard >> directions[i]);
        if ((bb & (bb >> (2 * directions[i]))) != 0)
            return true;
    }

    return false;
}