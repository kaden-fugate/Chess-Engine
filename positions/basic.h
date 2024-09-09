#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "game_state.h"

// values for indexing into the array of pieces bitboards
// white pieces
#define K 0
#define Q 1
#define R 2
#define B 3
#define N 4 
#define P 5

// black pieces
#define k 6
#define q 7
#define r 8
#define b 9
#define n 10
#define p 11

// all pieces for a color
#define allw 12
#define allb 13

// all attacks for a color
#define wa 14
#define ba 15

// identifiers for checking castling rights. 'none' will have value 15 as it is
// also used to identify piece/promotion type when encoding moves. 15 has the
// binary value 1111 which is an invalid piece identifier (0-11).
#define none 15
#define kingside 1
#define queenside 2
#define both 3



extern uint32_t move_list[256];
extern uint8_t move_count;
extern uint8_t turn;
extern uint8_t epsq;

extern uint64_t bitboards[16];

extern uint8_t wksc, wqsc;
extern uint8_t bksc, bqsc;

#endif