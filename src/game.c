#include "game.h"
#include "masks.h"
#include "magic.h"

// basic function that will print the current state of the board
void print_board(uint8_t pos){

    printf("|-------|-------|-------|-------|-------|-------|-------|-------|\n");

    for (int i = 7; i >= 0; i--){

        printf("|       |       |       |       |       |       |       |       |\n|");
        
        for (int j = 0; j < 8; j++){
            
            // debug for printing result of move generation
            if (pos < 64 & (1ULL << pos) & (1ULL << ((i * 8) + j)))
                printf("   ^   |");
            else if(pos < 64 & (moves[pos]) & (1ULL << ((i * 8) + j)))
                printf("   *   |");
            
            // print black pieces
            else if (bk & (1ULL << ((i * 8) + j))) {
                printf("   k   |", i, j);
            }
            else if (bq & (1ULL << ((i * 8) + j))) {
                printf("   q   |", i, j);
            }
            else if (br & (1ULL << ((i * 8) + j))) {
                printf("   r   |", i, j);
            }
            else if (bb & (1ULL << ((i * 8) + j))) {
                printf("   b   |", i, j);
            }
            else if (bn & (1ULL << ((i * 8) + j))) {
                printf("   n   |", i, j);
            }
            else if (bp & (1ULL << ((i * 8) + j))) {
                printf("   p   |", i, j);
            }
            
            // print white pieces
            else if (wk & (1ULL << ((i * 8) + j))) {
                printf("   K   |", i, j);
            }
            else if (wq & (1ULL << ((i * 8) + j))) {
                printf("   Q   |", i, j);
            }
            else if (wr & (1ULL << ((i * 8) + j))) {
                printf("   R   |", i, j);
            }
            else if (wb & (1ULL << ((i * 8) + j))) {
                printf("   B   |", i, j);
            }
            else if (wn & (1ULL << ((i * 8) + j))) {
                printf("   N   |", i, j);
            }
            else if (wp & (1ULL << ((i * 8) + j))) {
                printf("   P   |", i, j);
            }

            // print unoccupied space
            else { printf("       |"); }

        }

        printf("\n|       |       |       |       |       |       |       |       |\n");
        printf("|-------|-------|-------|-------|-------|-------|-------|-------|\n");

    }

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

// function will take the position of the knight as well as a bitboard
// representing the location of all pieces of the knights color. function will
// return a bitboard representing all pseudo-valid moves for the given knight.
//
// 8 possible moves:
//                                     63rd bit
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    | 2  |    | 3  |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    | 1  |    |    |    | 4  |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    | *  |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    | 8  |    |    |    | 5  |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    | 7  |    | 6  |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
//  0th bit -- left bit shift (<<) will move right and up the board
//
// (Figure 1.)

uint64_t n_valid_moves(uint8_t pos, uint64_t friendly_squares){

    // creates a bitmap representing the location of the knight of interest
    uint64_t n_loc = 1ULL << pos;

    // below here we will be verifying if each of the moves shown in figure 1
    // can be completed. to verify, we can do a bitwise and operation on the
    // knight location bitmap as well as the masks found in src/masks.h. 
    // 
    // in these masks, the 0's represent squares that make a move invalid.
    // we will go through each (of the 8) possible moves and use different
    // masks depending on the type of move to verify its validity.
    //
    // masks for each move:
    //      1 & 8:  mv1_n_mask
    //      2 & 7:  mv1_knp_mask
    //      4 & 5:  mv2_n_mask
    //      3 & 6:  mv2_knp_mask
    //
    // the mask will determine if the knight is in an invalid location. if so,
    // the operation will result in 0. if not, the result will be the postion
    // of the knight.
    //
    // with a non-zero result, we will now need to move the knight to the
    // square for the move we are checking. we will accomplish this with a
    // bitshift that will vary for each different move direction.
    //
    // bitmap to hold our valid moves. we'll init to no valid moves then we can
    // switch on whatever bits represent a valid move.
    uint64_t valid = 0x0;

    // move 1, 2, 3, ... respectively
    valid |= (n_loc & mv1_n_mask) << 6;
    valid |= (n_loc & mv1_knp_mask) << 15;
    valid |= (n_loc & mv2_knp_mask) << 17;
    valid |= (n_loc & mv2_n_mask) << 10;
    valid |= (n_loc & mv2_n_mask) >> 6;
    valid |= (n_loc & mv2_knp_mask) >> 15;
    valid |= (n_loc & mv1_knp_mask) >> 17;
    valid |= (n_loc & mv1_n_mask) >> 10;
    
    // switch off any bits that represent a square with a friendly piece. we 
    // can do this by negating our friendly_squares bitboard and then doing a
    // bitwise and operation with our valid moves bitboard, thus negating any
    // friendly squares in our bitboard. return the value from here.
    return valid & ~friendly_squares;

}

// function will take a number representing the position of the pawn in 
// question. function will return a bitboard representing all pseudo-valid 
// moves for the pawn.
//
// 4 possible moves:
//                                     63rd bit
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    | 2  |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    | 3  | 1  |  4 |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    | *  |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
//  0th bit -- left bit shift (<<) will move right and up the board
//
// (Figure 2.)

uint64_t wp_valid_moves(uint8_t pos){

    // shift a bit to the position of the pawn
    uint64_t p_loc = 1ULL << pos, ep = epsq == 64 ? 0x0 : (1ULL << epsq);

    if ( !(p_loc & allw) ) return (uint64_t) 0x0;

    // for determining the pseudo-valid moves for a pawn, we will use the same
    // method as we used in n_valid_moves. For moves 3 & 4 in figure 2, we will
    // need to use masks to make sure the pawn is in a valid position.
    //
    // masks for each move:
    //      1 & 2:  none
    //      3:      mv1_knp_mask
    //      4:      mv2_knp_mask
    //
    // after our bitwise and operations between our mask and the bitboard 
    // representing the pawn, we will be left with a non-zero bitboard if the
    // pawn is in a valid position. from here we do our shifting.

    // pseduo-valid move bitboard
    uint64_t valid = 0x0;

    // move 1: pawn can move forward one square if it is unoccupied by either
    // color
    valid |= (p_loc << 8) & (allw | allb) ? 0 : p_loc << 8;
    
    // move 2: pawn can jump forward two squares under the following 
    // conditions:
    //
    //      1. square to jump to is unoccupied (we can do this the same way we
    //         did with move 1).
    //      2. square directly ahead (calculated in move 1) is unoccupied
    //      3. pawn has not yet moved (we can do this with a bitwise and 
    //         operation between p_loc and 0x000000000000FF00 which represents
    //         all pawns in their starting position. this will return a 
    //         non-zero bitboard if p_loc is in the starting line of pawns).

    valid |= (p_loc & 0x000000000000FF00) // check if in starting row
          && !(p_loc << 16 & (allw | allb)) // check avail. 
          && valid // check if previous square also available 
          ? p_loc << 16 : 0;


    // move 3: pawn attacks left. we'll need to use the bitmask first then
    // check that an opposing piece is in the correct position
    valid |= ((p_loc & mv1_knp_mask) << 7) & (allb | ep);

    // move 4: same as move 3 but with a new mask and a shift of 9 instead of 7
    valid |= ((p_loc & mv2_knp_mask) << 9) & (allb | ep);

    return valid;

}

// function is the same as the above wp_valid_moves but in the reverse 
// direction. pawns are unique in that each color has unique movesets; this is
// something you don't see in other pieces. that is the reason for the 
// separate functions by color.
//
// 4 possible moves:
//                                     63rd bit
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    | *  |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    | 3  | 1  | 4  |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    | 2  |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
//  0th bit -- left bit shift (<<) will move right and up the board
//
// (Figure 2.)

uint64_t bp_valid_moves(uint8_t pos){

    // shift a bit to the position of the pawn
    uint64_t p_loc = 1ULL << pos, ep = epsq == 64 ? 0x0 : (1ULL << epsq);

    if ( !(p_loc & allb) ) return (uint64_t) 0x0;

    // for determining the pseudo-valid moves for a pawn, we will use the same
    // method as we used in n_valid_moves. For moves 3 & 4 in figure 2, we will
    // need to use masks to make sure the pawn is in a valid position.
    //
    // masks for each move:
    //      1 & 2:  none
    //      3:      mv1_knp_mask
    //      4:      mv2_knp_mask
    //
    // after our bitwise and operations between our mask and the bitboard 
    // representing the pawn, we will be left with a non-zero bitboard if the
    // pawn is in a valid position. from here we do our shifting.

    // pseduo-valid move bitboard
    uint64_t valid = 0x0;

    // move 1: pawn can move forward one square if it is unoccupied by either
    // color
    valid |= (p_loc >> 8) & (allw | allb) ? 0 : p_loc >> 8;
    
    // move 2: pawn can jump forward two squares under the following 
    // conditions:
    //
    //      1. square to jump to is unoccupied (we can do this the same way we
    //         did with move 1).
    //      2. square directly ahead (calculated in move 1) is unoccupied
    //      3. pawn has not yet moved (we can do this with a bitwise and 
    //         operation between p_loc and 0x000000000000FF00 which represents
    //         all pawns in their starting position. this will return a 
    //         non-zero bitboard if p_loc is in the starting line of pawns).

    valid |= (p_loc & 0x00FF000000000000) // check if in starting row
          && !(p_loc >> 16 & (allw | allb)) // check avail. 
          && valid // check if previous square also available 
          ? p_loc >> 16 : 0;

    // move 3: pawn attacks left. we'll need to use the bitmask first then
    // check that an opposing piece is in the correct position
    valid |= ((p_loc & mv1_knp_mask) >> 7) & (allw | ep);

    // move 4: same as move 3 but with a new mask and a shift of 9 instead of 7
    valid |= ((p_loc & mv2_knp_mask) >> 9) & (allw | ep);

    return valid;

}

uint64_t b_valid_moves(uint8_t pos, uint64_t friendly, uint64_t opp){

    uint64_t blockers = bmasks[pos] & (friendly | opp),
             magic = (blockers * b_magic[pos]) >> (64 - b_bits[pos]),
             attack = b_magic_ht[pos][magic];


    return attack & ~(friendly);

}

uint64_t r_valid_moves(uint8_t pos, uint64_t friendly, uint64_t opp){

    uint64_t blockers = rmasks[pos] & (friendly | opp),
             magic = (blockers * r_magic[pos]) >> (64 - r_bits[pos]),
             attack = r_magic_ht[pos][magic];


    return attack & ~(friendly);

}

uint64_t q_valid_moves(uint8_t pos, uint64_t friendly, uint64_t opp){

    return r_valid_moves(pos, friendly, opp) 
         | b_valid_moves(pos, friendly, opp);

}

//
// 8 possible moves:
//                                     63rd bit
// |----|----|----|----|----|----|----|----|
// |    |    |  1 |  2 |  3 |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |  8 | *  |  4 |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |  7 |  6 |  5 |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
//  0th bit -- left bit shift (<<) will move right and up the board
//
// (Figure 2.)
//
uint64_t k_valid_moves(uint8_t pos, uint64_t friendly){

    uint64_t valid = 0x0;
    uint64_t west = ((1ULL << pos) & mv1_knp_mask),
             east = ((1ULL << pos) & mv2_knp_mask);

    valid |= (west << 7) | (west >> 1) | (west >> 9) 
          |  (east << 9) | (east << 1) | (east >> 7)
          |  ((1ULL << pos) << 8) | ((1ULL << pos) >> 8);

    return valid & ~friendly;

}

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

                if (fen[i] == 'k') bk |= pos_bit;
                else if (fen[i] == 'q') bq |= pos_bit;
                else if (fen[i] == 'r') br |= pos_bit;
                else if (fen[i] == 'b') bb |= pos_bit;
                else if (fen[i] == 'n') bn |= pos_bit;
                else if (fen[i] == 'p') bp |= pos_bit;

                else if (fen[i] == 'K') wk |= pos_bit;
                else if (fen[i] == 'Q') wq |= pos_bit;
                else if (fen[i] == 'R') wr |= pos_bit;
                else if (fen[i] == 'B') wb |= pos_bit;
                else if (fen[i] == 'N') wn |= pos_bit;
                else if (fen[i] == 'P') wp |= pos_bit;

                // check piece color
                if ( (int) fen[i] >= 65 && (int) fen[i] <= 90 ) 
                    allb |= pos_bit;

                else allw |= pos_bit;

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

                printf("fen[i]: %c\n", fen[i]);
                epsq = (((int) fen[i] - 97)) + (8 * ((int) fen[i + 1] - 49));
                i++;

            }

        }

    }

}