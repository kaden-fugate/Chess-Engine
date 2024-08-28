CC = gcc
CFLAGS = -Wall -g

all: chess

chess: main.o game.o masks.o basic.o
	$(CC) $(CFLAGS) main.o game.o masks.o basic.o -o chess

main.o: main.c src/masks.h positions/basic.h
	$(CC) -c -g main.c

game.o: src/game.c src/game.h
	$(CC) -c -g src/game.c

masks.o: src/masks.c src/masks.h
	$(CC) -c -g src/masks.c

basic.o: positions/basic.c positions/basic.h
	$(CC) -c -g positions/basic.c

clean: 
	rm -f main.o chess