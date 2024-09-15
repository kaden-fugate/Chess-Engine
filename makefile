CC = gcc
CFLAGS = -Wall -g

all: chess magic

magic: magic.o
	$(CC) $(CFLAGS) magic.o -O3 -o gen_magic

chess: main.o game.o functions.o masks.o basic.o game_state.o engine.o
	$(CC) $(CFLAGS) main.o game.o functions.o masks.o basic.o game_state.o engine.o -O3 -o chess

main.o: main.c src/masks.h src/engine.h positions/basic.h 
	$(CC) -c -g -O3 main.c

game.o: src/game.c src/game.h src/magic.h src/functions.h
	$(CC) -c -g -O3 src/game.c

functions.o: src/functions.c src/functions.h positions/basic.h
	$(CC) -c -g -O3 src/functions.c

masks.o: src/masks.c src/masks.h
	$(CC) -c -g -O3 src/masks.c

magic.o: magic/magic.c magic/magic.h
	$(CC) -c -g -O3 magic/magic.c 

basic.o: game_state.o positions/basic.c positions/basic.h
	$(CC) -c -g -O3 positions/basic.c

game_state.o: positions/game_state.c positions/game_state.h positions/basic.h
	$(CC) -c -g -O3 positions/game_state.c

engine.o: src/engine.c src/engine.h
	$(CC) -c -g -O3 src/engine.c

clean: 
	rm -f *.o chess gen_magic