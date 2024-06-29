/******************************************************
 * main.c
 *
 * Created on: 28.06.2024
 *
 * Author: David Jäggli
 *
 * Description: A simple console-based Connect Four game.
 *
 * Usage: Depending on the current active user, use either the arrow keys to move the cursor left and right
 * and drop a piece, or use the keys 'a', 's', 'd' to move the cursor left, drop a piece, and move the cursor right, respectively.
 * The game will automatically switch between two players, 'X' and 'O'.
 * Press 'r' to restart the game, and 'q' to quit.
 ******************************************************/

/******************************************************
 * Includes
 ******************************************************/
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ncurses.h>

#include "board.h"
#include "log.h"

/******************************************************
 * Main Function
 ******************************************************/
int main()
{
    log_init();

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    Board board;
    reset_board(&board);

    int selected_col = 0;
    draw_board(&board, selected_col);

    // char players[2] = {'X', 'O'};
    int ch;
    bool running = true;
    while (running && (ch = getch()) != 'q')
    {
        switch (ch)
        {
        case KEY_UP:
            // printw("Up arrow key pressed\n");
            break;
        case KEY_DOWN:
            if (drop_piece(&board, selected_col) == ERR_COL_FULL)
                break;

            char winner = 0;
            if (is_winner(board.bitboards[0]))
                winner = 'X';
            else if (is_winner(board.bitboards[1]))
                winner = 'O';

            if (winner)
            {
                int x, y;
                field_start_pos(&x, &y);
                mvprintw(y - 3, x - 10, "Player %c wins! Press 'q' to quit or 'r' to restart.", winner);
                refresh();
                running = false;
                while ((ch = getch()) != 'q' && ch != 'r')
                    ;
                if (ch == 'r')
                {
                    reset_board(&board);
                    running = true;
                }
            }
            break;
        case KEY_LEFT:
            selected_col = (selected_col - 1 + COLS) % COLS;
            break;
        case KEY_RIGHT:
            selected_col = (selected_col + 1) % COLS;
            break;
        case 'r':
            reset_board(&board);
            draw_board(&board, 0);
            break;
        default:
            break;
        }
        draw_board(&board, selected_col);
    }

    endwin();

    log_end(true);

    return 0;
}
