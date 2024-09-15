#ifndef GAME_H
#define GAME_H

#include "../positions/basic.h"
#include "functions.h"

void gen_moves(uint8_t);
void make_move(uint32_t);
void player_move(char *);

uint8_t get_castle(uint8_t);

uint8_t checkmate();
uint8_t stalemate();

uint64_t n_valid_moves(uint8_t, uint64_t);
uint64_t wp_valid_moves(uint8_t);
uint64_t bp_valid_moves(uint8_t);
uint64_t b_valid_moves(uint8_t, uint64_t, uint64_t);
uint64_t r_valid_moves(uint8_t, uint64_t, uint64_t);
uint64_t q_valid_moves(uint8_t, uint64_t, uint64_t);
uint64_t k_valid_moves(uint8_t, uint64_t);

#endif