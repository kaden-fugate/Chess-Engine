#include "src/masks.h"
#include "src/game.h"
#include "src/functions.h"
#include "src/engine.h"

#include "positions/basic.h"
#include "positions/fen.h"


int main(){

    init(startpos);
    gen_moves(1);

    char move[100];
    uint8_t best_move = 255;

    while (!checkmate() && !stalemate()) {

        print_board(65);

        if (turn){
            
            printf("(%s TURN):\nscore: %.2lf, ", turn ? "BLACK'S" : "WHITE'S", (float) alpha_beta_min(-CHECKMATE, CHECKMATE,  4, &best_move) / 100.0);
            printf("best move: ");
            idx_to_pos(GET_SRC(move_list[best_move]));
            idx_to_pos(GET_TRGT(move_list[best_move]));
            printf(" (%d)\n", best_move);

            make_move(move_list[best_move]);
        }
        else{

            printf("enter move: ");
            scanf("%s", move);
            player_move(move);
            
        }
        gen_moves(1);
    }

    printf("%s wins!\n", turn ? "Black" : "White");

    
    return 0;

}