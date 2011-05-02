/* life.c : Conway's Game of Life in C */
/* Author: Trevor Bramwell
   Date: 04/20/2011
   Version: 0.1 */
#include "board.h"
#include <stdlib.h>
#include <ncurses.h>

#define BOARD_SIZE 20

void printMenu(void);

int main(void) {
    WINDOW *my_win;
    int x, y;
    int h, w;

    Board *b;
    int ch,count;

    initscr(); //initialize window
    keypad(stdscr, TRUE);
    noecho(); // disable echoing of input

    /* Setup Window */
    h = BOARD_SIZE+4;
    w = (BOARD_SIZE*2)+2;
    getmaxyx(stdscr, y, x);
    my_win = newwin(h, w, (y-h)/2, (x-w)/2);

    /* Setup Board */
    b = newBoard(BOARD_SIZE);
    count=0;
   
    /* Print Command Menu */ 
    refresh();
    printMenu();
    
    do {
        werase(my_win);
        box(my_win, 0, 0);
        printBoard(b, my_win);
        mvwprintw(my_win, h-2, 1, "Iter:%i", count);
        refresh();
        wrefresh(my_win);
        updateCells(b);
        changeState(b);
        count++;
    } while((ch = getch()) != 'q');
    
    deleteBoard(b);
    delwin(my_win);
    endwin();
    return 0;
}

void printMenu(void) {
    WINDOW *win;
    int x, y;
    int h, w;
    
    h = 8;
    w = 20;
    x = (COLS/2)+BOARD_SIZE+2;
    y = (LINES - BOARD_SIZE)/2;

    win = newwin(h, w, y-1, x);
    mvwprintw(win, 0, 0, "COMMANDS");
    mvwprintw(win, 1, 0, "  q: Quit");
    wrefresh(win);
}
