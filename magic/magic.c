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

int main(){

    for (uint8_t i = 0; i < 64; i++){

        uint64_t r_pos_mask = r_mask(i);
        printf("(%d) r_pos_mask: %llx\n\n", i, r_pos_mask);

        for (int8_t j = 7; j >= 0; j--){

            for (uint8_t k = 0; k < 8; k++){

                printf("   %d   ", (r_pos_mask & (1ULL << (j * 8 + k))) ? 1 : 0);

            }

            printf("\n\n");

        }

        printf("\n\n");

    }


    return 0;

}