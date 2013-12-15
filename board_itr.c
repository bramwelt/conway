#include "board.h"
#include "board_itr.h"

BoardItr* initBoardItr(BoardItr* boardItr, Board *board)
{
    boardItr->board = board;
    boardItr->x = 0;
    boardItr->y = 0;
    return boardItr;
}

int hasNext(BoardItr* itr)
{
    int size = itr->board->size;
    return (itr->x != size) && (itr->y != size);
}

Cell* next(BoardItr* itr)
{
    Cell* n;
    if (itr->x == itr->board->size) return NULL;
        
    n = &(itr->board->array[itr->x][itr->y]);
    if (itr->y != itr->board->size) {
        ++(itr->y);
    } else {
        ++(itr->x);
        itr->y = 0;
    }
    return n;
}
