#include "masks.h"

uint64_t mv1_knp_mask = 0xFEFEFEFEFEFEFEFE;
uint64_t mv2_knp_mask = 0x7F7F7F7F7F7F7F7F;

uint64_t mv1_n_mask = 0xFCFCFCFCFCFCFCFC;
uint64_t mv2_n_mask = 0x3F3F3F3F3F3F3F3F;

uint64_t p_wks_msk = 0x60;
uint64_t p_wqs_msk = 0xE;
uint64_t p_bks_msk = 0x6000000000000000;
uint64_t p_bqs_msk = 0xE00000000000000;

uint64_t a_wks_msk = 0x70;
uint64_t a_wqs_msk = 0x1C;
uint64_t a_bks_msk = 0x7000000000000000;
uint64_t a_bqs_msk = 0x1C00000000000000;

uint64_t wksc_msk = 0xA0;
uint64_t wqsc_msk = 0x9;
uint64_t bksc_msk = 0xA000000000000000;
uint64_t bqsc_msk = 0x900000000000000;