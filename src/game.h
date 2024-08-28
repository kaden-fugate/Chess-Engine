#ifndef GAME_H
#define GAME_H

#include "../positions/basic.h"

void print_board();
uint64_t n_valid_moves(uint8_t pos, uint64_t friendly_squares);

#endif