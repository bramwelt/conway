/* board.h : Game of Life Board template */
#include <ncurses.h>
#ifndef BOARD_H
#define BOARD_H

#define DEAD 0 
#define ALIVE !(DEAD)
#define DEAD_CHAR  ' '
#define ALIVE_CHAR '+'

typedef struct Cell {
    int state;
    int next_state;
} Cell;

typedef struct Board {
    int size;
    Cell** array;
} Board; 

void initBoard(Board *board, int size);
void freeBoard(Board *board);
Board* newBoard(int size);
void deleteBoard(Board *board);

void eachCell(Board *board, void (*each)(Board*, int, int));
void changeState(Board *board);
void updateCells(Board *board);

void printBoard(Board *board, WINDOW *win);
void seedBoard(Board *board);
void testState(Board *board);
#endif
