#ifndef GAME_H
#define GAME_H

#include "../positions/basic.h"

void print_board(uint8_t);
void print_bitboard(uint64_t);

uint64_t n_valid_moves(uint8_t, uint64_t);
uint64_t wp_valid_moves(uint8_t);
uint64_t bp_valid_moves(uint8_t);
uint64_t b_valid_moves(uint8_t, uint64_t, uint64_t);
uint64_t r_valid_moves(uint8_t, uint64_t, uint64_t);
uint64_t q_valid_moves(uint8_t, uint64_t, uint64_t);
uint64_t k_valid_moves(uint8_t, uint64_t);

void gen_moves(uint8_t);
void gen_all_moves();
uint8_t make_move(uint8_t, uint8_t);
uint8_t castling_impeded(uint8_t, uint8_t);
uint64_t gen_castle(uint8_t);
void parse_fen(char *);

#endif