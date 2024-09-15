#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../positions/basic.h"
#include "game.h"

void print_board(uint8_t);
void print_bitboard(uint64_t);
void parse_fen(char *);
void init(char *);
uint8_t lsb(uint64_t);
void idx_to_pos(uint8_t);
void print_move(uint32_t);

// this macro will quickly encode information about a move into a 32bit integer
#define ENCODE(src, trgt, type, pro_type, cap_flg, dbl_flg, ep_flg, cstl_flg) \
    (src)               |                                                     \
    (trgt << 6)         |                                                     \
    (type << 12)        |                                                     \
    (pro_type << 16)    |                                                     \
    (cap_flg << 20)     |                                                     \
    (dbl_flg << 21)     |                                                     \
    (ep_flg << 22)      |                                                     \
    (cstl_flg << 23)                                                          \

#define GET_SRC(move)      (  move & 0x3F            )
#define GET_TRGT(move)     ( (move & 0xFC0   ) >> 6  )
#define GET_TYPE(move)     ( (move & 0xF000  ) >> 12 )
#define GET_PRO_TYPE(move) ( (move & 0xF0000 ) >> 16 )
#define GET_CAP_FLG(move)  ( (move & 0x100000) >> 20 )
#define GET_DBL_FLG(move)  ( (move & 0x200000) >> 21 )
#define GET_EP_FLG(move)   ( (move & 0x400000) >> 22 )
#define GET_CSTL_FLG(move) ( (move & 0x800000) >> 23 )

#endif