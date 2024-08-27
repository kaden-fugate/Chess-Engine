#ifndef MASKS_H
#define MASKS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// hexadecimal representations of the below boards:
//
//  mv1_knp_mask:
//
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
//           0  1  1  1  1  1  1  1
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
uint64_t mv1_knp_mask = 0x7F7F7F7F7F7F7F7F;
uint64_t mv2_knp_mask = 0xFEFEFEFEFEFEFEFE;

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
uint64_t mv1_n_mask = 0x3F3F3F3F3F3F3F3F;
uint64_t mv2_n_mask = 0xFCFCFCFCFCFCFCFC;

#endif