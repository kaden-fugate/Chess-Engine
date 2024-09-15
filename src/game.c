#include "game.h"
#include "masks.h"
#include "magic.h"

//
// function will take the position of the knight as well as a bitboard
// representing the location of all pieces of the knights color. function will
// return a bitboard representing all pseudo-valid moves for the given knight.
//
// 8 possible moves:
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
//
uint64_t n_valid_moves(uint8_t pos, uint64_t friendly){

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
    uint8_t board_idx = !(friendly & ~bitboards[allw]) ? wa : ba;

    // move 1, 2, 3, ... respectively
    valid |= (n_loc & mv1_n_mask) << 6;
    valid |= (n_loc & mv1_knp_mask) << 15;
    valid |= (n_loc & mv2_knp_mask) << 17;
    valid |= (n_loc & mv2_n_mask) << 10;
    valid |= (n_loc & mv2_n_mask) >> 6;
    valid |= (n_loc & mv2_knp_mask) >> 15;
    valid |= (n_loc & mv1_knp_mask) >> 17;
    valid |= (n_loc & mv1_n_mask) >> 10;

    bitboards[board_idx] |= valid;
    
    // switch off any bits that represent a square with a friendly piece. we 
    // can do this by negating our friendly_squares bitboard and then doing a
    // bitwise and operation with our valid moves bitboard, thus negating any
    // friendly squares in our bitboard. return the value from here.
    return valid & ~friendly;

}

//
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
//
uint64_t wp_valid_moves(uint8_t pos){

    // shift a bit to the position of the pawn
    uint64_t p_loc = 1ULL << pos, ep = epsq == 64 ? 0x0 : (1ULL << epsq);

    if ( !(p_loc & bitboards[allw]) ) return (uint64_t) 0x0;

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
    uint64_t valid = 0x0, attacks = 0x0;

    // move 1: pawn can move forward one square if it is unoccupied by either
    // color
    valid |= (p_loc << 8) & (bitboards[allw] | bitboards[allb]) ? 0 : p_loc << 8;
    
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
          && !(p_loc << 16 & (bitboards[allw] | bitboards[allb])) // check avail. 
          && valid // check if previous square also available 
          ? p_loc << 16 : 0;


    // move 3: pawn attacks left. we'll need to use the bitmask first then
    // check that an opposing piece is in the correct position
    attacks |= ((p_loc & mv1_knp_mask) << 7);

    // move 4: same as move 3 but with a new mask and a shift of 9 instead of 7
    attacks |= ((p_loc & mv2_knp_mask) << 9);

    // add attacks to valid moves as well as our wa bitboard
    valid |= (attacks & (bitboards[allb] | ep)), bitboards[wa] |= attacks;

    return valid;

}

//
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
//
uint64_t bp_valid_moves(uint8_t pos){

    // shift a bit to the position of the pawn
    uint64_t p_loc = 1ULL << pos, ep = epsq == 64 ? 0x0 : (1ULL << epsq);

    if ( !(p_loc & bitboards[allb]) ) return (uint64_t) 0x0;

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
    uint64_t valid = 0x0, attacks = 0x0;

    // move 1: pawn can move forward one square if it is unoccupied by either
    // color
    valid |= (p_loc >> 8) & (bitboards[allw] | bitboards[allb]) ? 0 : p_loc >> 8;
    
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
          && !(p_loc >> 16 & (bitboards[allw] | bitboards[allb])) // check avail. 
          && valid // check if previous square also available 
          ? p_loc >> 16 : 0;

    // move 3: pawn attacks left. we'll need to use the bitmask first then
    // check that an opposing piece is in the correct position
    attacks |= ((p_loc & mv1_knp_mask) >> 9);

    // move 4: same as move 3 but with a new mask and a shift of 9 instead of 7
    attacks |= ((p_loc & mv2_knp_mask) >> 7);

    valid |= (attacks & (bitboards[allw] | ep)), bitboards[ba] |= attacks;

    return valid;

}

//
//
//
uint64_t b_valid_moves(uint8_t pos, uint64_t friendly, uint64_t opp){

    uint8_t board_idx = !(friendly & ~bitboards[allw]) ? wa : ba;

    uint64_t blockers = bmasks[pos] & (friendly | opp),
             magic = (blockers * b_magic[pos]) >> (64 - b_bits[pos]),
             attack = b_magic_ht[pos][magic];

    bitboards[board_idx] |= attack;
    
    return attack & ~friendly;

}

//
//
//
uint64_t r_valid_moves(uint8_t pos, uint64_t friendly, uint64_t opp){

    uint8_t board_idx = !(friendly & ~bitboards[allw]) ? wa : ba;

    uint64_t blockers = rmasks[pos] & (friendly | opp),
             magic = (blockers * r_magic[pos]) >> (64 - r_bits[pos]),
             attack = r_magic_ht[pos][magic];

    bitboards[board_idx] |= attack;

    return attack & ~friendly;

}

//
//
//
uint64_t q_valid_moves(uint8_t pos, uint64_t friendly, uint64_t opp){

    return r_valid_moves(pos, friendly, opp) 
         | b_valid_moves(pos, friendly, opp);

}

//
// 
//
uint8_t get_castle(uint8_t color) {

    // set masks for color (castling, attack, all pieces)
    uint64_t p_ks_msk = color ? p_bks_msk : p_wks_msk, 
    p_qs_msk = color ? p_bqs_msk : p_wqs_msk,
    a_qs_msk = color ? a_bqs_msk : a_wqs_msk, 
    a_ks_msk = color ? a_bks_msk : a_wks_msk, 
    attack = color ? bitboards[wa] : bitboards[ba],
    all = bitboards[allw] | bitboards[allb],
    king = color ? bitboards[k] : bitboards[K];

    if (king & attack) return none;

    // get castling rights for color. init vars to hold result (qsc, ksc)
    uint8_t ks_r = color ? bksc : wksc, qs_r = color ? bqsc : wqsc, ksc, qsc;
             
    // check that castling is not impeded
    ksc = (ks_r && !(p_ks_msk & all) && !(a_ks_msk & attack)) ? 1 : 0;
    qsc = (qs_r && !(p_qs_msk & all) && !(a_qs_msk & attack)) ? 1 : 0;

    // return which sides can castle
    return (ksc && qsc) ? both : (ksc ? kingside : (qsc ? queenside : none));

}

// - get color for masks 
// - check for pieces/attacks overlapping with given mask 

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

    uint8_t board_idx =  !(friendly & ~bitboards[allw]) ? wa : ba,
            opp_idx = board_idx == wa ? ba : wa;
    uint64_t valid = 0x0;
    uint64_t west = ((1ULL << pos) & mv1_knp_mask),
             east = ((1ULL << pos) & mv2_knp_mask);

    valid |= (west << 7) | (west >> 1) | (west >> 9) 
            |  (east << 9) | (east << 1) | (east >> 7)
            |  ((1ULL << pos) << 8) | ((1ULL << pos) >> 8);

    bitboards[board_idx] |= valid;

    return valid & ~friendly & ~bitboards[opp_idx];

}





//
// this function will generate all moves possible on the current board. we're
// going to need to make a few assumptions about the state of the game as of
// entering the function. firstly, it's important to think about the fact that 
// we only need to generate moves for the side whose turn it is.
//
// to avoid having to generate all of the enemy attacks to check for things
// like ability to castle (such as in the case where an enemy piece is looking
// at one of the castling squares), we will assume that they have already been
// generated before entering gen_moves.
//
// we can put all of the moves that we generate into 'moves' which is an array
// of 256 uint64_t's found in basic.c/.h. this array is size 256 as im assuming
// that there is no position where more than 256 moves are available for some
// given color. 
//
// moves can be encoded as 32 bit integers. here's how a move will be encoded
// as a 32 bit int (only 24 bits will be used):
//
// bits    information stored in bits    mask used to extract information
// 000000 |source square,      6 bits|  |            0x3F                |
// 000000 |target square,      6 bits|  |            0xFC0               |
// 0000   |piece type,         4 bits|  |            0xF000              |
// 0000   |promoted to,        4 bits|  |            0xF0000             |
// 0      |capture flag,       1 bit |  |            0x100000            |
// 0      |double push flag,   1 bit |  |            0x200000            |
// 0      |enpassant flag,     1 bit |  |            0x400000            |
// 0      |castle flag,        1 bit |  |            0x800000            |
//                         
// 24 total bits needed to encode all of this information.  
//  
void gen_moves(uint8_t legal){

    move_count = 0;

    uint8_t piece, opp = turn ? allw : allb, friendly = turn ? allb : allw,
            source, target, start = turn ? k : K, end = turn ? p : P,
            prm_flg, cap_flg, dbl_flg, ep_flg, cstl_flg, promote, is_legal;
    
    uint32_t move;

    uint64_t board, moves;

    // clear past attacks when updating moves
    bitboards[turn ? ba : wa] = 0x0;

    // iterate through all pieces
    for (piece = start; piece <= end; piece++) {

        board = bitboards[piece];
        
        // generate each move for each piece, add to the move list.
        while (board) {

            source = lsb(board);
            
            // king moves
            if (piece == K || piece == k) {

                moves = k_valid_moves(source, bitboards[friendly]);

            }

            // queen moves
            else if (piece == Q || piece == q) {

                moves = q_valid_moves(source, bitboards[friendly], 
                                      bitboards[opp]);

            }

            // rook moves
            else if (piece == R || piece == r) {

                moves = r_valid_moves(source, bitboards[friendly], 
                                      bitboards[opp]);

            }

            // bishop moves
            else if (piece == B || piece == b) {

                moves = b_valid_moves(source, bitboards[friendly], 
                                      bitboards[opp]);

            }

            // knight moves
            else if (piece == N || piece == n) {

                moves = n_valid_moves(source, bitboards[friendly]);

            }

            // white pawn moves
            else if (piece == P) {

                moves = wp_valid_moves(source);

            }

            // black pawn moves
            else if (piece == p) {

                moves = bp_valid_moves(source);

            }

            // we can stop here if we only need pseudo-legal moves
            if (!legal) { board &= ~(1ULL << source); continue; }

            // add all generated moves to the list
            while (moves) {


                prm_flg = 0, cap_flg = 0, dbl_flg = 0, ep_flg = cstl_flg = 0;
                
                // get the target pos of the move and remove it from the
                // bitboard
                target = lsb(moves);
                moves &= ~(1ULL << target);

                // check if promotion
                if ((piece == P && target >= 56) || (piece == p && target <= 7)) 
                    prm_flg = 1;

                // check if capture
                if ((1ULL << target) & bitboards[opp]) cap_flg = 1;

                // check if double pawn jump
                if ((piece == P || piece == p) 
                 && (target - source == 16 || target - source == -16)) 
                    dbl_flg = 1;

                // check if en passant
                if (target == epsq && (piece == P || piece == p)) ep_flg = 1;

                // add to the move list
                if (!prm_flg){

                    move = ENCODE(source, target, piece, none, cap_flg, 
                           dbl_flg, ep_flg, cstl_flg);

                    PUSH_STATE();
                    make_move(move);

                    is_legal = !(bitboards[turn ? ba : wa] 
                                & bitboards[turn ? K : k]) ? 1 : 0;

                    POP_STATE();

                    if (is_legal) {
                        move_list[move_count] = move;
                        move_count++;
                    }
                    
                }

                // in the case of promotions, we'll need to add 4 moves
                else {
                    for (promote = start + 1; promote < end; promote++){
                        move = ENCODE(source, target, piece, promote, cap_flg, 
                        dbl_flg, ep_flg, cstl_flg);

                        PUSH_STATE();
                        make_move(move);

                        is_legal = !(bitboards[turn ? ba : wa] 
                                & bitboards[turn ? K : k]) ? 1 : 0;

                        POP_STATE();

                        if (is_legal){
                            move_list[move_count] = move;
                            move_count++;
                        }
                    }
                }

            }

            board &= ~(1ULL << source);

        }

    }

    if (!legal) return;

    // generate castling moves, add them to the move_list
    uint8_t castle = get_castle(turn);
    if (castle == both || castle == kingside) {
        move_list[move_count] = ENCODE((turn ? 60 : 4), (turn ? 62 : 6), 
                                (turn ? 6 : 0), none, 0, 0, 0, 1);
        move_count++;
    }
    if (castle == both || castle == queenside) {
        move_list[move_count] = ENCODE((turn ? 60 : 4), (turn ? 58 : 2), 
                                (turn ? 6 : 0), none, 0, 0, 0, 1);
        move_count++;
    }

}

void make_move(uint32_t move) {

    // necessary data about the move that's being made
    uint8_t source = GET_SRC(move), target = GET_TRGT(move), 
            type = GET_TYPE(move), pro_type = GET_PRO_TYPE(move),
            cap_flg = GET_CAP_FLG(move), dbl_flg = GET_DBL_FLG(move),
            ep_flg = GET_EP_FLG(move), cstl_flg = GET_CSTL_FLG(move),
            all = turn ? allb : allw, opp = turn ? allw : allb;

    uint64_t src_brd = (1ULL << source), trgt_brd = (1ULL << target);

    // reset enpassant square. this will be set later in this function if a
    // pawn double jump occured.
    epsq = 64;

    // take care of castle flags:

    // if src or trgt is a rook, this side can no longer castle as the piece 
    // either moved or was captured.
    if (!source || !target || type == K) wqsc = 0;
    if (source == 7 || target == 7 || type == K) wksc = 0;
    if (source == 56 || target == 56 || type == k) bqsc = 0;
    if (source == 63 || target == 63 || type == k) bksc = 0;

    // move piece from src to target (manipulate all and piece bitboards)
    bitboards[all]  ^= src_brd;
    bitboards[type] ^= src_brd;
    bitboards[all]  ^= trgt_brd;
    bitboards[type] ^= trgt_brd;

    // take care of promotions
    if (pro_type != none) {

        bitboards[type] ^= trgt_brd;
        bitboards[pro_type] ^= trgt_brd;

    }

    // take care of captures
    if (cap_flg) {

        uint8_t opp_type;

        // get captured pieces type
        if (turn) opp_type =  (bitboards[Q] & trgt_brd) ? Q :
                         (bitboards[R] & trgt_brd) ? R :
                         (bitboards[B] & trgt_brd) ? B :
                         (bitboards[N] & trgt_brd) ? N : P;

        else opp_type = (bitboards[q] & trgt_brd) ? q :
                             (bitboards[r] & trgt_brd) ? r :
                             (bitboards[b] & trgt_brd) ? b :
                             (bitboards[n] & trgt_brd) ? n : p;

        // remove enemy piece
        bitboards[opp_type] ^= trgt_brd;
        bitboards[opp] ^= trgt_brd;


    }

    // take care of en passant capture
    if (ep_flg) {

        uint64_t ep_brd;

        // find the pawn that's en-passant'd
        if (turn) ep_brd = trgt_brd << 8;
        else ep_brd = trgt_brd >> 8;

        // remove pawn from opp bitboards
        bitboards[opp] ^= ep_brd;
        bitboards[turn ? P : p] ^= ep_brd;

    }

    // set epsq if pawn did double jump
    if (dbl_flg) {

        if (turn) epsq = target + 8;
        else epsq = target - 8;

    }

    // move rook if king castled
    if (cstl_flg) {
        
        uint64_t mask;

        if (target == 2) mask = wqsc_msk;
        else if (target == 6) mask = wksc_msk;
        else if (target == 58) mask = bqsc_msk;
        else if (target == 62) mask = bksc_msk;

        bitboards[turn ? r : R] ^= mask;
        bitboards[all] ^= mask;

    }

    // we'll need to update our own attack squares as the piece that we moved
    // will be attacking new squares.
    gen_moves(0);

    // last thing to do is switch turns, clear previous attacks, and generate
    // new attacks. this will be for checking that our move does not put our
    // king in check.
    turn = !turn;
    bitboards[turn ? ba : wa] = 0x0;
    gen_moves(0);

}

//
//
//
uint8_t checkmate() {

    if (move_count) return 0;

    uint64_t king = turn ? bitboards[k] : bitboards[K],
             attack = turn ? bitboards[wa] : bitboards[ba];

    if (king & attack) return 1;
    return 0;

}

//
//
//
uint8_t stalemate() {

    if (move_count) return 0;

    uint64_t king = turn ? bitboards[k] : bitboards[K],
             attack = turn ? bitboards[wa] : bitboards[ba];

    if (king & attack) return 0;
    return 1;

}

void player_move(char *move) {

    uint8_t from = (((int) move[0]) - 97) + ((int) move[1] - 49) * 8,
            to = (((int) move[2]) - 97) + ((int) move[3] - 49) * 8;
            
    for (int8_t i = 0; i < move_count; i++) {

        if (from == GET_SRC(move_list[i]) && to == GET_TRGT(move_list[i]))
            make_move(move_list[i]);

    }

}