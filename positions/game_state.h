#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "basic.h"

struct state {

    uint64_t bitboards[16];
    uint32_t move_list[256];
    uint8_t move_count, turn, epsq, wksc, wqsc, bksc, bqsc;
    
};

// save the current game state, push it onto the game state stack
void PUSH_STATE();

// pop game state from the stack
void POP_STATE();

extern struct state stack[16];
extern uint8_t stk_top;

#endif