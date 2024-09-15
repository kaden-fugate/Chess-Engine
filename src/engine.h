#ifndef ENGINE_H
#define ENGINE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "game.h"

#define CHECKMATE 100000

#define Q_SCR 900
#define R_SCR 510
#define B_SCR 333
#define N_SCR 320
#define P_SCR 100

uint64_t perft(uint8_t, uint8_t);
int32_t evaluate();
int32_t alpha_beta_max(int32_t, int32_t, uint8_t, uint8_t*);
int32_t alpha_beta_min(int32_t, int32_t, uint8_t, uint8_t*);


#endif