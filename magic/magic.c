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
// this function will take 'idx', a number of bits, and a mask. the mask will
// be the possible squares where the piece can be blocked at a given position.
// from here, we want to try to create the given index in binary using only
// squares present in the mask.
//
// a rook will be blocked by at most 12 squares at a time. we can treat each
// square blocking the rook as a bit. we can flip these bits on and off to
// represent up to 2^12 numbers (2^12 because there are 12 squares that can all
// be 1 or 0). 
// 
// with this square to binary conversion, we can create a set of blockers for
// the given mask that also converts to the 'idx' given. as a visual example, 
// below we will represent the idx 27 using the rook mask for position 27:
//
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |  + |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |  + |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |  + |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |  + |+ 1 |  * |+ 1 |  + |  + |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |+ 1 |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |+ 1 |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// |    |    |    |    |    |    |    |    |
// |----|----|----|----|----|----|----|----|
// (Figure 1.)
//
// * = rook pos, + = possible blockers, 1 = bits switched on to represent 27
//
// the least significant bit switched on in the mask will represent 2^0 while
// the most significant bit switched on will represent 2^n where n is equal to
// the number of bits switched on in the mask. 
//
// if we take a look at fig. 1, if we represent only the possible blockers in
// binary (strictly excluding any square that are switched off in the mask),
// we can see that there ten possible blockers. because of this, we can 
// represent a number up to the size of 2^10 + 2^9 + ... + 2^ 0 = 2^(11) - 1.
//
// for our example, we want to represent 27. in fig. 1, we can represent the
// current combination of blockers as 0000011011 in binary. when converting, we
// get 2^0 + 2^1 + 2^3 + 2^4 = 1 + 2 + 8 + 16 = 27.
//
// using this method where we create a combination of blockers will make it
// a lot simpler to generate all possible blockers given a specific mask. 
//
// the reason we'll need the number of bits switched on in the mask is because
// we will be counting down from the most significant bit to convert from a
// base-10 number to a binary one.
//
uint64_t idx_to_blocker(uint16_t idx, uint8_t bits, uint64_t mask){

    uint64_t binary = 0x0;
    uint16_t bit_value = (uint16_t) (1ULL << (bits - 1)), sum = 0x0;

    // start at MSB (63), loop down to LSB (0). break if idx equals sum
    for (int8_t cur_bit = 63; cur_bit > 0 && sum != idx; cur_bit--){

        if (mask & (1ULL << cur_bit)){

            if (sum + bit_value <= idx){

                binary |= (1ULL << cur_bit);

                // add to the sum. idx will be successfully created when sum
                // equals the idx we're trying to represent
                sum += bit_value;

            }

            // halve the bit value (this is just how binary works)
            bit_value /= 2;
        }

    }

    return binary;

}

//
// this function will count how many bits are switched on given a bitboard.
// this number will be greater than -1 and less than 65 so we'll only need a 
// uint8_t to represent it.
//
uint8_t count_bits(uint64_t bitboard){

    uint8_t total = 0, i;
    for (i = 0; i < 64; i++) if (bitboard & (1ULL << i)) ++total;

    return total;

}

//
// this function will only be used once then it will be taken out of code and
// never called again. the idea behind this function is that we will be 
// generating all possible blockers for each square and their corresponding 
// valid attacks. we will be doing this for both rooks and bishops.
//
// once calculated, we will print out the blocker and attack positions for
// each square for both rooks and bishops. the idea is that we can output these
// values to a file and use them later without re-computing them.
//
void gen_masks(){

    uint64_t mask;
    uint16_t idx;
    uint8_t pos, rook, bits;

    // calculate square for both rooks and bishops
    for (rook = 0; rook < 2; rook++) {

        // loop through each square on the board
        for (pos = 0; pos < 64; pos++){

            // grab the current mask and count the number of bits in it
            mask = rook ? rmasks[pos] : bmasks[pos];
            bits = count_bits(mask);

            // now we're going to create every different possible blocker
            // combination for a given mask then we'll find the corresponding
            // attack for the position. this will get stored in r/bbmasks and
            // r/bamasks.
            for (idx = 0; idx < (1ULL << bits); idx++){

                // rook specific
                if (rook){
                    rb_masks[pos][idx] = idx_to_blocker(idx, bits, mask);
                    ra_masks[pos][idx] = r_attacks(pos, rb_masks[pos][idx]);
                }

                // bishop specific
                else {
                    bb_masks[pos][idx] = idx_to_blocker(idx, bits, mask);
                    ba_masks[pos][idx] = b_attacks(pos, bb_masks[pos][idx]);
                }

            }

        }

    }

    // the rest of the code in this function is used to print out the data.
    // this will then be used to store the pre-calculated values in our code
    // for later use.
    printf("uint64_t rb_masks[64][4096] = {\n");
    for (pos = 0; pos < 64; pos++){

        bits = count_bits(rmasks[pos]);
        printf("\t{");
        for (idx = 0; idx < (1ULL << bits); idx++){

            if (idx) printf(", ");
            printf("0x%016llx", rb_masks[pos][idx]); 

        }
        if (pos == 63) printf("}\n");
        else printf("},\n");

    }
    printf("};\n");

    printf("uint64_t bb_masks[64][512] = {\n");
    for (pos = 0; pos < 64; pos++){

        bits = count_bits(bmasks[pos]);
        printf("\t{");
        for (idx = 0; idx < (1ULL << bits); idx++){

            if (idx) printf(", ");
            printf("0x%016llx", bb_masks[pos][idx]); 

        }
        if (pos == 63) printf("}\n");
        else printf("},\n");

    }
    printf("};\n");

    printf("uint64_t ra_masks[64][4096] = {\n");
    for (pos = 0; pos < 64; pos++){

        bits = count_bits(rmasks[pos]);
        printf("\t{");
        for (idx = 0; idx < (1ULL << bits); idx++){

            if (idx) printf(", ");
            printf("0x%016llx", ra_masks[pos][idx]); 

        }
        if (pos == 63) printf("}\n");
        else printf("},\n");

    }
    printf("};\n");

    printf("uint64_t ba_masks[64][512] = {\n");
    for (pos = 0; pos < 64; pos++){

        bits = count_bits(bmasks[pos]);
        printf("\t{");
        for (idx = 0; idx < (1ULL << bits); idx++){

            if (idx) printf(", ");
            printf("0x%016llx", ba_masks[pos][idx]); 

        }
        if (pos == 63) printf("}\n");
        else printf("},\n");

    }
    printf("};\n");

}

uint64_t rand_64uint(){

    uint64_t upper32 = ((((uint64_t) random()) & 0xFFFF) << 16) 
                     | (((uint64_t) random()) & 0xFFFF);

    uint64_t lower32 = ((((uint64_t) random()) & 0xFFFF) << 16) 
                     | (((uint64_t) random() )& 0xFFFF);

    return (uint64_t) ((uint64_t) upper32 << 32) | (uint64_t) lower32;

}

//
// given a square 
uint8_t make_magic(uint8_t pos, uint8_t rook){

    uint64_t a[4096], b[4096], used[4096];
    uint64_t magic, attempt, mask = rook ? rmasks[pos] : bmasks[pos];
    uint16_t i, magic_key;
    uint8_t bits = rook ? r_bits[pos] : b_bits[pos], fail;

    for (i = 0; i < (1ULL << bits); i++) {

        b[i] = idx_to_blocker(i, bits, mask);
        a[i] = rook ? r_attacks(pos, b[i]) : b_attacks(pos, b[i]);
        

    }

    for (attempt = 0; attempt < 1000000; attempt++) {

        magic = rand_64uint() & rand_64uint() & rand_64uint();

        // check that magic number leaves 7 or more bits switched in the 8 most
        // significant bits when multiplied by the mask. not sure of the 
        // significance of this; i saw this used in Tord Romstads proposal to
        // find magic numbers here: chessprogramming.org/Looking_for_Magics
        if(count_bits((mask  * magic) & 0xFF00000000000000ULL) < 6) continue;

        for (i = 0; i < (1ULL << bits); i++) used[i] = 0ULL;

        for (i = 0, fail = 0; !fail && i < (1ULL << bits); i++) {

            magic_key = (int) ((b[i] * magic) >> (64 - bits));

            if (used[magic_key] != 0ULL) fail = 1;
            else used[magic_key] = a[i];

        }

        if (!fail) {
            if (rook) r_magic[pos] = magic;
            else b_magic[pos] = magic;

            for (i = 0; i < (1ULL << bits); i++) {
                if (rook) r_magic_ht[pos][i] = used[i];
                else b_magic_ht[pos][i] = used[i];
            }
            
            return 1;
        }

    }

    return 0;    

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

int main(){

    srandom(time(NULL));

    uint8_t i, success, rook, bits;
    uint16_t j, idx;

    for (rook = 0; rook < 2; rook++){

        for (i = 0; i < 64; i++) {

            do{ success = make_magic(i, rook); } 
            while(!success);

        }

    }

    printf("uint64_t r_magic[64] = {\n");
    for (j = 0; j < 64; j++) {
        if (j && j % 3 == 0) printf(", \n\t");
        else if (j) printf(", ");
        else printf("\t");
        printf("0x%016llx", r_magic[j]);
    }
    printf("\n};\n");

    printf("uint64_t b_magic[64] = {\n");
    for (j = 0; j < 64; j++) {
        if (j && j % 3 == 0) printf(", \n\t");
        else if (j) printf(", ");
        else printf("\t");
        printf("0x%016llx", b_magic[j]);
    }
    printf("\n};\n");

    printf("uint64_t r_magic_ht[64][4096] = {\n");
    for (j = 0; j < 64; j++){

        bits = count_bits(rmasks[j]);
        printf("\t{");
        for (idx = 0; idx < (1ULL << bits); idx++){

            if (idx) printf(", ");
            printf("0x%016llx", r_magic_ht[j][idx]); 

        }
        if (j == 63) printf("}\n");
        else printf("},\n");

    }
    printf("};\n");
    
    printf("uint64_t b_magic_ht[64][512] = {\n");
    for (j = 0; j < 64; j++){

        bits = count_bits(bmasks[j]);
        printf("\t{");
        for (idx = 0; idx < (1ULL << bits); idx++){

            if (idx) printf(", ");
            printf("0x%016llx", b_magic_ht[j][idx]); 

        }
        if (j == 63) printf("}\n");
        else printf("},\n");

    }
    printf("};\n");
    
    return 0;

}