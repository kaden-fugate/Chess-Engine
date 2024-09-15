#include "engine.h"

int8_t wk_pos[64] = {
    20,  30,  10,  0,   0,   10,  30,  20,  
    20,  20,  0,   0,   0,   0,   20,  20,  
    -10, -20, -20, -20, -20, -20, -20, -10,   
    -20, -30, -30, -40, -40, -30, -30, -20,   
    -30, -40, -40, -50, -50, -40, -40, -30,   
    -30, -40, -40, -50, -50, -40, -40, -30,   
    -30, -40, -40, -50, -50, -40, -40, -30,   
    -30, -40, -40, -50, -50, -40, -40, -30
};
int8_t wq_pos[64] = {
    -20, -10, -10, -5,  -5,  -10, -10, -20,   
    -10, 0,   5,   0,   0,   0,   0,   -10,   
    -10, 5,   5,   5,   5,   5,   0,   -10,   
    0,   0,   5,   5,   5,   5,   0,   0,   
    -5,  0,   5,   5,   5,   5,   0,   -5,   
    -10, 0,   5,   5,   5,   5,   0,   -10,   
    -10, 0,   0,   0,   0,   0,   0,   -10,   
    -20, -10, -10, -5,  -5,  -10, -10, -20
};

int8_t wr_pos[64] = {
    0,   0,   0,   5,   5,   0,   0,   0,   
    -5,  0,   0,   0,   0,   0,   0,   -5,   
    -5,  0,   0,   0,   0,   0,   0,   -5,   
    -5,  0,   0,   0,   0,   0,   0,   -5,   
    -5,  0,   0,   0,   0,   0,   0,   -5,   
    -5,  0,   0,   0,   0,   0,   0,   -5,   
    5,   10,  10,  10,  10,  10,  10,  5,   
    0,   0,   0,   0,   0,   0,   0,   0
};
int8_t wb_pos[64] = {
    -20,   -10, -10, -10, -10, -10, -10, -20,   
    -10,   5,   0,   0,   0,   0,   5,   -10,   
    -10,   10,  10,  10,  10,  10,  10,  -10,   
    -10,   0,   10,  10,  10,  10,  0,   -10,   
    -10,   5,   5,   10,  10,  5,   5,   -10,   
    -10,   0,   5,   10,  10,  5,   0,   -10,   
    -10,   0,   0,   0,   0,   0,   0,   -10,   
    -20,   -10, -10, -10, -10, -10, -10, -20  
};
int8_t wn_pos[64] = {
    -50,   -40, -30, -30, -30, -30, -40, -50,   
    -40,   -20, 0,   5,   5,   0,   -20, -40,   
    -30,   5,   10,  15,  15,  10,  5,   -30,   
    -30,   0,   15,  20,  20,  15,  0,   -30,   
    -30,   5,   15,  20,  20,  15,  5,   -30,   
    -30,   0,   10,  15,  15,  10,  0,   -30,   
    -40,   -20, 0,   0,   0,   0,   -20, -40,   
    -50,   -40, -30, -30, -30, -30, -40, -50  
};
int8_t wp_pos[64] = {
    0,   0,   0,   0,   0,   0,   0,   0,   
    5,   10,  10,  -20, -20, 10,  10,  5,   
    5,   -5,  -10, 0,   0,   -10, -5,  5,   
    0,   0,   0,   20,  20,  0,   0,   0,   
    5,   5,   10,  25,  25,  10,  5,   5,   
    10,  10,  20,  30,  30,  20,  10,  10,  
    50,  50,  50,  50,  50,  50,  50,  50,  
    0,   0,   0,   0,   0,   0,   0,   0  
};

int8_t bk_pos[64] = {
    -30, -40, -40, -50, -50, -40, -40, -30,   
    -30, -40, -40, -50, -50, -40, -40, -30,   
    -30, -40, -40, -50, -50, -40, -40, -30,   
    -30, -40, -40, -50, -50, -40, -40, -30,   
    -20, -30, -30, -40, -40, -30, -30, -20,   
    -10, -20, -20, -20, -20, -20, -20, -10,   
    20,  20,  0,   0,   0,   0,   20,  20,  
    20,  30,  10,  0,   0,   10,  30,  20
};
int8_t bq_pos[64] = {
    -20, -10, -10, -5, -5,   -10, -10, -20,   
    -10, 0,   0,   0,   0,   0,   0,   -10,   
    -10, 0,   5,   5,   5,   5,   0,   -10,   
    -5,  0,   5,   5,   5,   5,   0,   -5,   
    0,   0,   5,   5,   5,   5,   0,   0,   
    -10, 5,   5,   5,   5,   5,   0,   -10,   
    -10, 0,   5,   0,   0,   0,   0,   -10,   
    -20, -10, -10, -5,  -5,  -10, -10, -20
};

int8_t br_pos[64] = {
    0,   0,   0,   0,   0,   0,   0,   0,   
    5,   10,  10,  10,  10,  10,  10,  5,   
    -5,   0,   0,   0,   0,   0,   0,   -5,   
    -5,   0,   0,   0,   0,   0,   0,   -5,   
    -5,   0,   0,   0,   0,   0,   0,   -5,   
    -5,   0,   0,   0,   0,   0,   0,   -5,   
    -5,   0,   0,   0,   0,   0,   0,   -5,   
    0,   0,   0,   5,   5,   0,   0,   0
};
int8_t bb_pos[64] = {
    -20,   -10,   -10,   -10,   -10,   -10,   -10,   -20,   
    -10,   0,   0,   0,   0,   0,   0,   -10,   
    -10,   0,   5,   10,  10,  5,   0,   -10,   
    -10,   5,   5,   10,  10,  5,   5,   -10,   
    -10,   0,   10,  10,  10,  10,  0,   -10,   
    -10,   10,  10,  10,  10,  10,  10,  -10,   
    -10,   5,   0,   0,   0,   0,   5,   -10,   
    -20,   -10,   -10,   -10,   -10,   -10,   -10,   -20
};
int8_t bn_pos[64] = {
    -50,   -40,   -30,   -30,   -30,   -30,   -40,   -50,   
    -40,   -20,   0,   0,   0,   0,   -20,   -40,   
    -30,   0,   10,  15,  15,  10,  0,   -30,   
    -30,   0,   15,  20,  20,  15,  0,   -30,   
    -30,   0,   15,  20,  20,  15,  0,   -30,   
    -30,   5,   10,  15,  15,  10,  5,   -30,   
    -40,   -20,   0,   5,   5,   0,   -20,   -40,   
    -50,   -40,   -30,   -30,   -30,   -30,   -40,   -50
};
int8_t bp_pos[64] = {
    0,   0,   0,   0,   0,   0,   0,   0,   
    50,  50,  50,  50,  50,  50,  50,  50,  
    10,  10,  20,  30,  30,  20,  10,  10,  
    5,   5,   10,  25,  25,  10,  5,   5,   
    0,   0,   0,   20,  20,  0,   0,   0,   
    5,   -5,   -10,   0,   0,   -10,   -5,   5,   
    5,   10,  10,  -20,   -20,   10,  10,  5,   
    0,   0,   0,   0,   0,   0,   0,   0
};

//
//
//
uint64_t perft(uint8_t depth, uint8_t divide) {

    // generate all moves for the current player, put in move list
    gen_moves(1);

    // if depth is 1, simply return the number of moves
    if (depth == 1 && !divide) return move_count;
    else if(depth == 0) return 1ULL;

    uint64_t sum = 0, result, sum2 = 0;

    // loop through each move, make it, call perft(depth - 1) on new position,
    // unmake the move, repeat.
    for (uint8_t i = 0; i < move_count; i++) {
        
        PUSH_STATE();

        uint32_t move = move_list[i];
        make_move(move);
        result = perft(depth - 1, 0);

        // for debugging moves
        // if (i != 14) result = perft(depth - 1, 0); 
        // else {
        //     if (depth == 3) print_board(65);
        //     result = perft(depth - 1, depth == 3 ? 1 : 0); 
        //     if (depth == 3) printf("total moves (%d):\t%d\n", depth - 1, result);
        // }

        sum += result;

        POP_STATE();

        if (divide == 1){
            uint8_t pro_type = GET_PRO_TYPE(move);
            char type_char = '\0';

            if (pro_type != none){
               type_char = (!pro_type || pro_type == 6) ? 'k' : type_char;
               type_char = (pro_type == 1 || pro_type == 7) ? 'q' : type_char;
               type_char = (pro_type == 2 || pro_type == 8) ? 'r' : type_char;
               type_char = (pro_type == 3 || pro_type == 9) ? 'b' : type_char;
               type_char = (pro_type == 4 || pro_type == 10) ? 'n' : type_char;
            }

            // for printing % calculated - used for testing deep depths
            // printf("[%.2lf] %s", (float) 100*(((float)(i+1)) / ((float)move_count)), (float) 100*(((float)(i+1)) / ((float)move_count)) < (float)10 ? "  " : " ");
            
            // for printing index of move - used for debugging
            //printf("[%d] %s", i, i > 9 ? " " : "  ");

            idx_to_pos(GET_SRC(move_list[i]));
            idx_to_pos(GET_TRGT(move_list[i]));
            printf("%c", type_char);
            printf(": %d\n", result);
        }

    }

    return sum;

}

//
// for the time being, the evaluation function will be relatively simple. it
// will take into account each piece and a pieces value in relation to its 
// place on the board.
//
int32_t evaluate() {

    uint64_t boards[12] = { 
        bitboards[0], bitboards[1], bitboards[2],  bitboards[3], 
        bitboards[4], bitboards[5], bitboards[6],  bitboards[7], 
        bitboards[8], bitboards[9], bitboards[10], bitboards[11]
    };

    uint8_t counts[12] = { 0 };
    uint8_t idx;

    int32_t eval = 0, bonus = 0, prev = 0;

    for (uint8_t piece = K; piece <= p; piece++) {

        while (boards[piece]){

            prev = bonus;

            idx = lsb(boards[piece]);
            
            boards[piece] &= ~(1ULL << idx);
            counts[piece]++;
            
            if (piece == K)      bonus += wk_pos[idx];
            else if (piece == Q) bonus += wq_pos[idx];
            else if (piece == R) bonus += wr_pos[idx];
            else if (piece == B) bonus += wb_pos[idx];
            else if (piece == N) bonus += wn_pos[idx];
            else if (piece == P) bonus += wp_pos[idx];

            else if (piece == k) bonus += bk_pos[idx];
            else if (piece == q) bonus -= bq_pos[idx];
            else if (piece == r) bonus -= br_pos[idx];
            else if (piece == b) bonus -= bb_pos[idx];
            else if (piece == n) bonus -= bn_pos[idx];
            else if (piece == p) bonus -= bp_pos[idx];


        }
    }

    eval = (counts[Q] - counts[q]) * Q_SCR
         + (counts[R] - counts[r]) * R_SCR
         + (counts[B] - counts[b]) * B_SCR
         + (counts[N] - counts[n]) * N_SCR
         + (counts[P] - counts[p]) * P_SCR;

    return eval + bonus;

}

int32_t alpha_beta_max(int32_t alpha, int32_t beta, uint8_t depth, uint8_t *best_mv) {

    if (checkmate()) return -CHECKMATE;
    else if (stalemate()) return 0;
    else if ( !depth ) return evaluate();

    int32_t score;
    for (uint16_t i = 0; i < move_count; i++) {

        PUSH_STATE();

        make_move(move_list[i]);
        gen_moves(1);
        score = alpha_beta_min( alpha, beta, depth - 1, 0x0);

        POP_STATE();

        if (score >= beta) return beta;

        if (score > alpha) {
            alpha = score;
            if (best_mv) *best_mv = i;
        }

    }

    return alpha;

}

int32_t alpha_beta_min(int32_t alpha, int32_t beta, uint8_t depth, uint8_t *best_mv) {

    if (checkmate()) return CHECKMATE;
    else if (stalemate()) return 0;
    else if ( !depth ) return evaluate();

    int32_t score;
    for (uint16_t i = 0; i < move_count; i++) {

        PUSH_STATE();

        make_move(move_list[i]);
        gen_moves(1);
        score = alpha_beta_max( alpha, beta, depth - 1, 0x0);

        POP_STATE();

        if (score <= alpha) return alpha;

        if (score < beta) {
            beta = score;
            if (best_mv) *best_mv = i;
        }

    }

    return beta;

}