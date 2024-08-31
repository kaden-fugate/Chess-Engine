#ifndef GAME_H
#define GAME_H

#include "../positions/basic.h"

void print_board();

uint64_t n_valid_moves(uint8_t, uint64_t);
uint64_t wp_valid_moves(uint8_t);
uint64_t bp_valid_moves(uint8_t);
uint64_t r_valid_moves(uint8_t, uint64_t, uint64_t);
uint64_t b_valid_moves(uint8_t, uint64_t, uint64_t);
uint64_t q_valid_moves(uint8_t, uint64_t, uint64_t);

#endif