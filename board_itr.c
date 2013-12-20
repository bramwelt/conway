/*
 * Board Iterator
 */
#include "board.h"
#include "board_itr.h"

BoardItr* initBoardItr(BoardItr* boardItr, Board *board)
{
    boardItr->board = board;
    boardItr->x = 0;
    boardItr->y = 0;
    boardItr->endrow = 0;
    return boardItr;
}

int hasNext(BoardItr* itr)
{
    return ((itr->x < itr->board->size) && (itr->y < itr->board->size));
}

Cell* next(BoardItr* itr)
{
    Cell* cell = &(itr->board->array[itr->x][itr->y]);

    if (itr->y < (itr->board->size-1)) {
        ++(itr->y);
        itr->endrow = 0;
    } else {
        ++(itr->x);
        itr->y = 0;
        itr->endrow = 1;
    }
    return cell;
}
