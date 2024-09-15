#include "functions.h"

//
// basic function that will print the current state of the board
//
void print_board(uint8_t pos){

    printf("    |-------|-------|-------|-------|-------|-------|-------|-------|\n");

    for (int i = 7; i >= 0; i--){

        printf("    |       |       |       |       |       |       |       |       |\n%d   |", i + 1);
        
        for (int j = 0; j < 8; j++){
            
            // debug for printing result of move generation
            if (pos < 64 & (1ULL << pos) & (1ULL << ((i * 8) + j)))
                printf("   ^   |");
            
            // print black pieces
            else if (bitboards[k] & (1ULL << ((i * 8) + j))) {
                printf("   k   |", i, j);
            }
            else if (bitboards[q] & (1ULL << ((i * 8) + j))) {
                printf("   q   |", i, j);
            }
            else if (bitboards[r] & (1ULL << ((i * 8) + j))) {
                printf("   r   |", i, j);
            }
            else if (bitboards[b] & (1ULL << ((i * 8) + j))) {
                printf("   b   |", i, j);
            }
            else if (bitboards[n] & (1ULL << ((i * 8) + j))) {
                printf("   n   |", i, j);
            }
            else if (bitboards[p] & (1ULL << ((i * 8) + j))) {
                printf("   p   |", i, j);
            }
            
            // print white pieces
            else if (bitboards[K] & (1ULL << ((i * 8) + j))) {
                printf("   K   |", i, j);
            }
            else if (bitboards[Q] & (1ULL << ((i * 8) + j))) {
                printf("   Q   |", i, j);
            }
            else if (bitboards[R] & (1ULL << ((i * 8) + j))) {
                printf("   R   |", i, j);
            }
            else if (bitboards[B] & (1ULL << ((i * 8) + j))) {
                printf("   B   |", i, j);
            }
            else if (bitboards[N] & (1ULL << ((i * 8) + j))) {
                printf("   N   |", i, j);
            }
            else if (bitboards[P] & (1ULL << ((i * 8) + j))) {
                printf("   P   |", i, j);
            }

            // print unoccupied space
            else { printf("       |"); }

        }

        printf("\n    |       |       |       |       |       |       |       |       |\n");
        printf("    |-------|-------|-------|-------|-------|-------|-------|-------|\n");

    }
    printf("\n        A       B       C       D       E       F       G       H       \n");

}

// 
// this function just prints a given bitboard. just makes debugging easier
//
void print_bitboard(uint64_t board){

    for (int8_t i = 7; i >= 0; i--){

        for (int8_t j = 0; j < 8; j++){

            printf("   %d   ", (board & (1ULL << (i * 8 + j))) ? 1 : 0);

        }

        printf("\n\n");

    }

    printf("\n");

}

//
//
//
void print_move(uint32_t move) {

    printf("SRC: ");
    idx_to_pos(GET_SRC(move));
    printf("\nTRGT: ");
    idx_to_pos(GET_TRGT(move));
    printf("\nTYPE: %d\nPRO_TYPE: %d\nCAP: %d\nDBL: %d\nEP: %d\nCSTL: %d\n", 
           GET_TYPE(move), GET_PRO_TYPE(move), 
           GET_CAP_FLG(move) ? 1 : 0, GET_DBL_FLG(move) ? 1 : 0, 
           GET_EP_FLG(move) ? 1 : 0, GET_CSTL_FLG(move) ? 1 : 0);

}

//
// this function will parse a string in FEN format. FEN will be passed into
// function as a char *. will fill in all relevant information such as piece
// positions, current turn, castling rights, and en passant squares.
// 
void parse_fen(char *fen){

    uint8_t i, field = 0, cur = 56;
    uint64_t pos_bit;

    for (i = 0; fen[i] != '\0'; i++) {

        // moving to next field in fen
        if (fen[i] == ' ') field++;

        // first field (position parsing)
        else if (field == 0) {

            // check if char is an integer. if so, shift cur square ahead by
            // n squares.
            if ( (int) fen[i] >= 48 && (int) fen[i] <= 57) 
                cur += (((int) fen[i]) - 48);

            // check if char is '/' 
            else if (fen[i] == '/') cur -= 16;

            // char is a piece indicator
            else {

                pos_bit = (1ULL << cur);

                if (fen[i] == 'k') bitboards[k] |= pos_bit;
                else if (fen[i] == 'q') bitboards[q] |= pos_bit;
                else if (fen[i] == 'r') bitboards[r] |= pos_bit;
                else if (fen[i] == 'b') bitboards[b] |= pos_bit;
                else if (fen[i] == 'n') bitboards[n] |= pos_bit;
                else if (fen[i] == 'p') bitboards[p] |= pos_bit;

                else if (fen[i] == 'K') bitboards[K] |= pos_bit;
                else if (fen[i] == 'Q') bitboards[Q] |= pos_bit;
                else if (fen[i] == 'R') bitboards[R] |= pos_bit;
                else if (fen[i] == 'B') bitboards[B] |= pos_bit;
                else if (fen[i] == 'N') bitboards[N] |= pos_bit;
                else if (fen[i] == 'P') bitboards[P] |= pos_bit;

                // check piece color
                if ( (int) fen[i] >= 65 && (int) fen[i] <= 90 ) 
                    bitboards[allw] |= pos_bit;

                else bitboards[allb] |= pos_bit;

                cur++;

            }

        } 
        
        // second field (player turn)
        else if (field == 1) {

            if (fen[i] == 'w') turn = 0;
            else turn = 1;

        }

        // third field (castling rights)
        else if (field == 2) {

            if (fen[i] == 'K') wksc = 1;
            else if (fen[i] == 'Q') wqsc = 1;
            else if (fen[i] == 'k') bksc = 1;
            else if (fen[i] == 'q') bqsc = 1;

        }

        // fourth field (enpassant square)
        else if (field == 3) {
            
            // no enpassant
            if (fen[i] == '-') epsq = 64;
            
            else {

                epsq = (((int) fen[i] - 97)) + (8 * ((int) fen[i + 1] - 49));
                i++;

            }

        }

    }

}

void init(char *fen) {

    for (uint8_t i = 0; i < 16; i++) bitboards[i] = 0x0;
    move_count = turn = wksc = wqsc = bksc = bqsc = 0, epsq = 64;

    parse_fen(fen);

    turn = !turn;
    gen_moves(0);
    turn = !turn;

}

//
// get least significant bit flipped in a given board.
//
uint8_t lsb(uint64_t board) {

    if (!board) return 64;
    for (uint8_t i = 0; i < 64; i++) if (board & (1ULL << i)) return i;

}

//
//
//
void idx_to_pos(uint8_t idx) {

    uint8_t file, rank;
    char *fl_arr = "abcdefgh", *rk_arr = "123456789";

    file = idx % 8, rank = idx / 8;
    printf("%c%c", fl_arr[file], rk_arr[rank]);

}