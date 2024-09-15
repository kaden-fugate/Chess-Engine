#ifndef MASKS_H
#define MASKS_H

#include <stdint.h>

// hexadecimal representations of the below boards:
//
//  mv1_knp_mask:
//                               MSB
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//          LSB
//
//  mv2_knp_mask:
//
//           1  1  1  1  1  1  1  0
//           1  1  1  1  1  1  1  0
//           1  1  1  1  1  1  1  0
//           1  1  1  1  1  1  1  0
//           1  1  1  1  1  1  1  0
//           1  1  1  1  1  1  1  0
//           1  1  1  1  1  1  1  0
//           1  1  1  1  1  1  1  0
//
extern uint64_t mv1_knp_mask;
extern uint64_t mv2_knp_mask;

// hexadecimal representations of the below boards:
//
//  mv1_n_mask:
//
//           0  0  1  1  1  1  1  1
//           0  0  1  1  1  1  1  1
//           0  0  1  1  1  1  1  1
//           0  0  1  1  1  1  1  1
//           0  0  1  1  1  1  1  1
//           0  0  1  1  1  1  1  1
//           0  0  1  1  1  1  1  1
//           0  0  1  1  1  1  1  1
//
//  mv2_n_mask:
//
//           1  1  1  1  1  1  0  0
//           1  1  1  1  1  1  0  0
//           1  1  1  1  1  1  0  0
//           1  1  1  1  1  1  0  0
//           1  1  1  1  1  1  0  0
//           1  1  1  1  1  1  0  0
//           1  1  1  1  1  1  0  0
//           1  1  1  1  1  1  0  0
//
extern uint64_t mv1_n_mask;
extern uint64_t mv2_n_mask;

extern uint64_t p_wks_msk;
extern uint64_t p_wqs_msk;
extern uint64_t p_bks_msk;
extern uint64_t p_bqs_msk;
extern uint64_t a_wks_msk;
extern uint64_t a_wqs_msk;
extern uint64_t a_bks_msk;
extern uint64_t a_bqs_msk;


extern uint64_t wksc_msk;
extern uint64_t wqsc_msk;
extern uint64_t bksc_msk;
extern uint64_t bqsc_msk;



#endif