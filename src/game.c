#include "game.h"
#include "masks.h"

// basic function that will print the current state of the board
void print_board(){

    printf("|-------|-------|-------|-------|-------|-------|-------|-------|\n");

    uint64_t vwnm = n_valid_moves(1, wk | wq | wr | wb | wn | wp);
    uint64_t vbnm = n_valid_moves(57, bk | bq | br | bb | bn | bp);
    
    uint64_t vwpm = wp_valid_moves(45);
    uint64_t vbpm = bp_valid_moves(52);    

    for (int i = 7; i >= 0; i--){

        printf("|       |       |       |       |       |       |       |       |\n|");
        
        for (int j = 0; j < 8; j++){
            
            // debug for printing result of move generation
            if (vwpm & (1ULL << ((i * 8) + j))){
                printf("   +   |");
            }
            else if (vbpm & (1ULL << ((i * 8) + j))){
                printf("   -   |");
            }
            else if (vwnm & (1ULL << ((i * 8) + j))){
                printf("   *   |");
            }
            else if (vbnm & (1ULL << ((i * 8) + j))){
                printf("   /   |");
            }
            
            // print black pieces
            else if (bk & (1ULL << ((i * 8) + j))) {
                printf("   K   |", i, j);
            }
            else if (bq & (1ULL << ((i * 8) + j))) {
                printf("   Q   |", i, j);
            }
            else if (br & (1ULL << ((i * 8) + j))) {
                printf("   R   |", i, j);
            }
            else if (bb & (1ULL << ((i * 8) + j))) {
                printf("   B   |", i, j);
            }
            else if (bn & (1ULL << ((i * 8) + j))) {
                printf("   N   |", i, j);
            }
            else if (bp & (1ULL << ((i * 8) + j))) {
                printf("   P   |", i, j);
            }
            
            // print white pieces
            else if (wk & (1ULL << ((i * 8) + j))) {
                printf("   k   |", i, j);
            }
            else if (wq & (1ULL << ((i * 8) + j))) {
                printf("   q   |", i, j);
            }
            else if (wr & (1ULL << ((i * 8) + j))) {
                printf("   r   |", i, j);
            }
            else if (wb & (1ULL << ((i * 8) + j))) {
                printf("   b   |", i, j);
            }
            else if (wn & (1ULL << ((i * 8) + j))) {
                printf("   n   |", i, j);
            }
            else if (wp & (1ULL << ((i * 8) + j))) {
                printf("   p   |", i, j);
            }

            // print unoccupied space
            else { printf("       |"); }

        }

        printf("\n|       |       |       |       |       |       |       |       |\n");
        printf("|-------|-------|-------|-------|-------|-------|-------|-------|\n");

    }

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
    uint64_t p_loc = 1ULL << pos;

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
    valid |= ((p_loc & mv1_knp_mask) << 7) & allb;

    // move 4: same as move 3 but with a new mask and a shift of 9 instead of 7
    valid |= ((p_loc & mv2_knp_mask) << 9) & allb;

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
    uint64_t p_loc = 1ULL << pos;

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
    valid |= ((p_loc & mv1_knp_mask) >> 7) & allw;

    // move 4: same as move 3 but with a new mask and a shift of 9 instead of 7
    valid |= ((p_loc & mv2_knp_mask) >> 9) & allw;

    return valid;

}