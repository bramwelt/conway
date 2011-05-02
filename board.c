/* board.c : Game of Life Board implementation */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "board.h"

/* Initialize the board means to allocate memory to the struct
     and set the initial state of characters. */
void initBoard(Board *board, int size) {
    int i;
    board->size = size;
    board->array = (Cell**) malloc(sizeof(Cell*) * size);
    assert(board->array != 0);
    for(i = 0; i < size; i++) {
        board->array[i] = (Cell*) malloc(sizeof(Cell) * size);
        assert(board->array[i] != 0);
    }
    /* TODO: find way to select seed or not seed */
    seedBoard(board);
}

/* New Board creates a new board, initializes it and
     returns. */
Board* newBoard(int size) {
    Board* b = (Board *) malloc( sizeof(Board) );
    assert(b != 0);

    initBoard(b, size);
    return b;
}

/* Free board will free up the memory the board
     has taken control of and reset the size. */
void freeBoard(Board *board){
    int i;
    for(i = 0; i < board->size; i++) {
        if(board->array[i] != 0) {
            free(board->array[i]);
        }
    }
    if(board->array != 0) {
        free(board->array);
    }
    board->size = 0;
}

/* Delete board will free up the board along with the
     memory the board itself takes up. */
void deleteBoard(Board *board) {
    freeBoard(board);
    free(board);
}

/* Output the state of the boards characters */
void printBoard(Board *board, WINDOW *win) {
    int i,j;
    int x,y, initx, inity;
    getyx(win, inity, initx);
    y = inity+1;
    for(i = 0; i < board->size; i++) {
        x = initx+1;
        for(j = 0; j < board->size; j++) {
            if(board->array[i][j].state & 1) {
                mvwaddch(win, y, x++, ALIVE_CHAR);
            } else { 
                mvwaddch(win, y, x++, DEAD_CHAR);
            }
            mvwaddch(win, y, x++, ' ');
        }
        wmove(win, ++y, x);
    }
}

/* Setup the board to randomly have either
     a cell be dead or alive. */
void seedBoard(Board *board) {
    int i, j, herp;
    srand(time(NULL));
    for(i = 0; i < board->size; i++) {
        for(j = 0; j < board->size; j++) {
            herp = rand() % board->size;
            if(herp % 2 == 1) {
                board->array[i][j].state = ALIVE;
            } else {
                board->array[i][j].state = DEAD;
            }
        }
    } 
}

/* Check a given cell to see if it is alive or dead */
int _cellIsAlive(Board *board, int i, int j) {
    assert(board != 0);
    assert(i >= 0 && i < board->size);
    assert(j >= 0 && i < board->size);

    return board->array[i][j].state == ALIVE;
}

/* Taking a board and a callback function,
     perform the callback function 'update' on 
     each cell of the board. */
void eachCell(Board *board, void (*each)(Board*, int, int)) {
    int i, j;
    for(i = 0; i < board->size; i++) {
        for(j = 0; j < board->size; j++) {
            each(board, i, j);
        }
    }   
}

void _changeState(Board *board, int i, int j) {
    Cell *tmp;
    tmp = &board->array[i][j];

    tmp->state = tmp->next_state;
}

/* Change the state of the cell to next iteration */
void changeState(Board *board) {
    assert(board != 0);
    eachCell(board, _changeState);
}

/**
 * Live Cells:
 *  A cell with less than two neighboors dies.          (lonely)
 *  A cell with greater than three neighboors dies.     (overcrowd)
 * Dead Cells:
 *  A cell with exactly three neighboors comes to life. (friendly)
 */
void _scanCells(Board *board, int i, int j) {
    int k,l,count;
    Cell *tmp, *tmp_count;

    count = 0;

    /* Count up number of live neighbors */
    for(k=i-1; k<i+2; k++) {
        for(l=j-1; l<j+2; l++) {
            if(!(k < 0 || l < 0) && !(k >= board->size || l >= board->size) && !(k == i && l == j)) {
                tmp_count = &board->array[k][l];
                if(tmp_count->state == ALIVE) {
                    count++; 
                }
            }
        }
    }

    /* Set next state for each Cell */
    tmp = &board->array[i][j]; 
    if(tmp->state == ALIVE) {
        if(count < 2) {
            tmp->next_state = DEAD; 
        } else if(count > 3) {
            tmp->next_state = DEAD;
        } else {
            tmp->next_state = ALIVE;
        }
    } else {
        if(count == 3) {
            tmp->next_state = ALIVE;
        }
    }
}

void updateCells(Board *board) {
    assert(board != 0);
    eachCell(board, _scanCells);
}
