#include "src/masks.h"
#include "src/game.h"

#include "positions/basic.h"
#include "positions/fen.h"


int main(){


    parse_fen(test2);

    print_board(65);

    turn = !turn;
    gen_moves();
    turn = !turn;
    gen_moves();
    
    printf("\n");
    for (int i = 0; i < move_count; i++){

        printf("(%d): ", i);
        idx_to_pos(GET_SRC(move_list[i]));
        idx_to_pos(GET_TRGT(move_list[i]));
        printf(" %d %d %d-%d-%d-%d\n", GET_TYPE(move_list[i]), GET_PRO_TYPE(move_list[i]), GET_CAP_FLG(move_list[i]) ? 1 : 0, GET_DBL_FLG(move_list[i]) ? 1 : 0, GET_EP_FLG(move_list[i]) ? 1 : 0, GET_CSTL_FLG(move_list[i]) ? 1 : 0);
    
    }

    printf("move count: %d\n", move_count);

    return 0;

}
