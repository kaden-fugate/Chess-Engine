#include "src/masks.h"
#include "src/game.h"

#include "positions/basic.h"

int main(){

    parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - h8");

    print_board(65);

    return 0;

}
