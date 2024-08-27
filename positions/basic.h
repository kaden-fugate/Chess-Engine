#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// bitboard to represent location of each white piece
extern uint64_t wk;
extern uint64_t wq;
extern uint64_t wr;
extern uint64_t wb;
extern uint64_t wn;
extern uint64_t wp;
extern uint64_t allw;

// bitboard to represent location of each black piece
extern uint64_t bk;
extern uint64_t bq;
extern uint64_t br;
extern uint64_t bb;
extern uint64_t bn;
extern uint64_t bp;
extern uint64_t allb;

#endif