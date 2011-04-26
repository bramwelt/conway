/* life.c : Conway's Game of Life in C */
/* Author: Trevor Bramwell
   Date: 04/20/2011
   Version: 0.1 */
#include "board.h"
#include <stdlib.h>
#include <ncurses.h>

int main(void) {
    Board *b = newBoard(6); //initialize board
    int ch,count;

    initscr(); //initialize window
    keypad(stdscr, TRUE);
    noecho(); // disable echoing of input
    count=0;

    do {
        erase();
        printBoard(b);
        PRINT(" Iter:%i", count);
        refresh();
        updateCells(b);
        changeState(b);
        count++;
    } while((ch = getch()) != 'q');
    
    endwin();
    return 0;
}
