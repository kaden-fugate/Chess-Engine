#include "basic.h"

uint32_t move_list[256] = { 0 };
uint8_t move_count = 0, turn = 0, epsq = 64;

uint64_t bitboards[16] = { 0 };

uint8_t wksc = 0,
        wqsc = 0;

uint8_t bksc = 0,
        bqsc = 0;