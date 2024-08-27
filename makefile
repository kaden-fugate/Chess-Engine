CC = gcc
CFLAGS = -Wall -g

all: chess

chess: main.o game.o basic.o
	$(CC) $(CFLAGS) main.o game.o basic.o -o chess

main.o: main.c src/masks.h positions/basic.h
	$(CC) -c main.c

game.o: src/game.c src/game.h
	$(CC) -c src/game.c

basic.o: positions/basic.c positions/basic.h
	$(CC) -c positions/basic.c

clean: 
	rm -f main.o chess