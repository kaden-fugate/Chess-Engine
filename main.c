#include "src/masks.h"
#include "src/game.h"

#include "positions/basic.h"
#include "positions/fen.h"


int main(){


    parse_fen(test1);
    //print_board(65);
    //printf("\n");

    turn = !turn;
    gen_moves(0);
    turn = !turn;

    uint8_t depth = 3, divide = 1;

    for (uint8_t i = depth; i <= depth; i++) {

        uint64_t total = perft(i, divide);
        divide = 0;
        printf("total moves (%d):\t%d\n", i, total);

    }

    return 0;

}

// startpos:
// off by 0 at depth 6

// test 1:
// off by ~4,000 at depth 3

// test 2:
// off ~34 at depth 6

// test 3:
// off ~250 at depth 3

// test 4:
// off ~200 at depth 3