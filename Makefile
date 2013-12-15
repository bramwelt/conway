default: board_itr.o board.o life.o
	gcc -Wall board_itr.o board.o life.o -o bin/life -lncurses

board.o:
	gcc -Wall -c board.c

life.o:
	gcc -Wall -c life.c

board_itr.o:
	gcc -Wall -c board_itr.c
