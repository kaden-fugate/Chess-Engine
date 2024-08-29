#include "magic.h"

//
// this function will generate a mask with the directions that a rook can be 
// blocked from. for this, we will need to take which square the rook is on.
// from here, we can set the bits which represent squares that a rook's vision 
// can be blocked on. A1-A7, A1-H1, A7-H7, and H1-H7 will not be included 
// because if the  previous square is left unblocked, we know this square is 
// free to move to excluding if its a friendly piece. we will observe these 
// ranks/files only under the condiditon that the rooks position is contained
// within one of these ranks/files
//
// we can store this bitmap in a hash table for later use. this will make it so
// we know where a rook can be blocked from given any location on the board.
//
// example of a mask gen given a square (square 16):
//
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |  + |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |  + |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |  + |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |  + |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |  * |  + |  + |  + |  + |  + |  + |    |
// |----|----|----|----|----|----|----|----|
// |  + |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
//
// * = position, + = possible blockers
//
uint64_t r_mask(uint8_t pos){

    uint64_t mask = 0x0;
    int8_t x = pos % 8, y = pos / 8, dx, dy; 

    // set possible blocker positions above
    for (dy = y + 1; dy < 7; dy++) mask |= (1ULL << (dy * 8 + x));

    // set possible blocker positions below
    for (dy = y - 1; dy > 0; dy--) mask |= (1ULL << (dy * 8 + x));

    // set possible blocker positions to right
    for (dx = x + 1; dx < 7; dx++) mask |= (1ULL << (y * 8 + dx)); 

    // set possible blocker positions to left
    for (dx = x - 1; dx > 0; dx--) mask |= (1ULL << (y * 8 + dx)); 

    return mask;

}

//
// this function will be the same as r_mask above but for a bishop instead.
// for this, pieces will move diagonally instead of vertically and horizontally
// (as you probably know by now). 
// 
// just as before, this bitmap can be stored in a hash table for quick lookup
// when we use it later. 
//
// example of a mask gen given a square (square 18):
//
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |  + |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |  + |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |  + |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |  + |    |  + |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |  * |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |  + |    |  + |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
//
// * = position, + = possible blockers
//
uint64_t b_mask(uint8_t pos){

    uint64_t mask = 0x0;
    int8_t x = pos % 8, y = pos / 8, dx, dy; 

    // set possible blocker positions to the north-east
    for (dx = x + 1, dy = y + 1; dx < 7 && dy < 7; dx++, dy++) 
        mask |= (1ULL << (dy * 8 + dx));

    // set possible blocker positions to the south-east
    for (dx = x + 1, dy = y - 1; dx < 7 && dy > 0; dx++, dy--) 
        mask |= (1ULL << (dy * 8 + dx));

    // set possible blocker positions to north-west
    for (dx = x - 1, dy = y + 1; dx > 0 && dy < 7; dx--, dy++) 
        mask |= (1ULL << (dy * 8 + dx)); 

    // set possible blocker positions to south-west
    for (dx = x - 1, dy = y - 1; dx > 0 && dy > 0; dx--, dy--) 
        mask |= (1ULL << (dy * 8 + dx)); 

    return mask;

}

//
// this function will take a rooks position as well as its blockers. with this
// we will create a bitmap representing all possible moves for the rook given 
// its position and the position of its blockers.
//
// this is an expensive function so the idea of this is that we're going to
// calculate this attack ahead of time and just lookup the precalculated 
// moveset whenever we want at runtime (using methods implemented below).
//
// example of a bitboard (pos: 27, blockers: 0x8000804080800)
//
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |  + |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |+ 1 |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |+ 1 | 1  |  * |  1 |  1 |  1 |  1 |
// |----|----|----|----|----|----|----|----|
// |    |    |    |+ 1 |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |  + |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
//
// * = position, + = blockers, 1 = square included in bitboard
//
// (just as a note, a square containing '+ 1' is a square where a blocker is 
// present and the square is also included in the bitboard)
//
uint64_t r_attacks(uint8_t pos, uint64_t blockers){

    int8_t x = pos % 8, y = pos / 8, dx, dy;
    uint64_t result = 0x0, observed = 0x0;

    // calculate eastern moves
    for (dx = x + 1; dx < 8; dx++){

        observed = (1ULL << (y * 8 + dx)); 

        result |= observed;
        if (blockers & observed) break;

    }

    // calculate western moves
    for (dx = x - 1; dx >= 0; dx--){

        observed = (1ULL << (y * 8 + dx)); 
        
        result |= observed;
        if (blockers & observed) break;

    }

    // calculate northern moves
    for (dy = y + 1; dy < 8; dy++){

        observed = (1ULL << (dy * 8 + x)); 
        
        result |= observed;
        if (blockers & observed) break;

    }

    // calculate southern moves
    for (dy = y - 1; dy >= 0; dy--){

        observed = (1ULL << (dy * 8 + x)); 
        
        result |= observed;
        if (blockers & observed) break;

    }

    return result;

} 

//
// once again, this function is the same as the above r_attacks but for bishops
// instead. a bitmap with all valid moves from position with given blockers 
// will be returned.
//
// example of a bitboard (pos: 27, blockers: 0x201000002200)
//
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |  1 |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |  1 |    |    |    |  + |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |  1 |    |+ 1 |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |  * |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |  1 |    |  1 |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |+ 1 |    |    |    |+ 1 |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
//
// * = position, + = blockers, 1 = square included in bitboard
//
// (just as a note, a square containing '+ 1' is a square where a blocker is 
// present and the square is also included in the bitboard)
//
uint64_t b_attacks(uint8_t pos, uint64_t blockers){

    int8_t x = pos % 8, y = pos / 8, dx, dy;
    uint64_t result = 0x0, observed = 0x0;

    // calculate north-eastern moves
    for (dx = x + 1, dy = y + 1; dx < 8 && dy < 8; dx++, dy++){

        observed = (1ULL << (dy * 8 + dx)); 

        result |= observed;
        if (blockers & observed) break;

    }

    // calculate north-western moves
    for (dx = x - 1, dy = y + 1; dx >= 0 && dy < 8; dx--, dy++){

        observed = (1ULL << (dy * 8 + dx)); 

        result |= observed;
        if (blockers & observed) break;

    }

    // calculate south-eastern moves
    for (dx = x + 1, dy = y - 1; dx < 8 && dy >= 0; dx++, dy--){

        observed = (1ULL << (dy * 8 + dx)); 

        result |= observed;
        if (blockers & observed) break;

    }

    // calculate south-western moves
    for (dx = x - 1, dy = y - 1; dx >= 0 && dy >= 0; dx--, dy--){

        observed = (1ULL << (dy * 8 + dx)); 

        result |= observed;
        if (blockers & observed) break;

    }

    return result;

} 

// 
// this function just prints a given bitboard. just makes debugging easier
//
void print_bitboard(uint64_t board){

    for (int8_t i = 7; i >= 0; i--){

        for (int8_t j = 0; j < 8; j++){

            if (i * 8 + j == 27) {printf("   *   "); continue;}
            printf("   %d   ", (board & (1ULL << (i * 8 + j))) ? 1 : 0);

        }

        printf("\n\n");

    }

    printf("\n");

}

int main(){

    

    return 0;

}