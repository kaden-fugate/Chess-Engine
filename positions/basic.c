#include "basic.h"

uint64_t moves[256] = { 0 };
uint8_t move_count = 0, turn = 0, epsq = 64;


uint64_t wk   = 0x0,
         wq   = 0x0,
         wr   = 0x0,
         wb   = 0x0,
         wn   = 0x0,
         wp   = 0x0,
         allw = 0x0,
         epw  = 0x0,
         wa   = 0x0;

uint8_t wksc = 0,
        wqsc = 0;

uint64_t bk   = 0x0,
         bq   = 0x0,
         br   = 0x0,
         bb   = 0x0,
         bn   = 0x0,
         bp   = 0x0,
         allb = 0x0,
         epb  = 0x0,
         ba   = 0x0;

uint8_t bksc = 0,
        bqsc = 0;