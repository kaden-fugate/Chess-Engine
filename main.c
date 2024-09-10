#include "src/masks.h"
#include "src/game.h"

#include "positions/basic.h"
#include "positions/fen.h"


int main(){


    parse_fen(test4);
    //print_board(65);
    //printf("\n");

    turn = !turn;
    gen_moves(0);
    turn = !turn;

    uint8_t depth = 5, divide = 0;

    for (uint8_t i = 1; i <= depth; i++) {

        uint64_t total = perft(i, i == depth);
        printf("total moves (%d):\t%d\n", i, total);

    }

    return 0;

}

// startpos:
// off by 0 at depth 6

// test 1:
// off by 0 at depth 5

// test 2:
// off 0 at depth 7

// test 3:
// off 0 at depth 6

// test 4:
// off 0 at depth 5