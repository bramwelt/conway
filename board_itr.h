#ifndef BOARD_ITR_H
#define BOARD_ITR_H

typedef struct BoardItr {
    Board* board;
    int x;
    int y;
    int line;
} BoardItr;

BoardItr* initBoardItr(BoardItr *boardItr, Board *board);
int hasNext(BoardItr* itr);
Cell* next(BoardItr* itr);

#endif
