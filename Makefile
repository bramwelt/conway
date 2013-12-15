CC = gcc

default: board_itr.o board.o life.o
	$(CC) -Wall board_itr.o board.o life.o -o bin/life -lncurses

board:
	$(CC) -Wall -c board.c

life:
	$(CC) -Wall -c life.c

board_itr:
	$(CC) -Wall -c board_itr.c
