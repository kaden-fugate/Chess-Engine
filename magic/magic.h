#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// rook blocker mask for each possible square
uint64_t rmasks[64] = {
    0x000101010101017e, 0x000202020202027c, 0x000404040404047a,
    0x0008080808080876, 0x001010101010106e, 0x002020202020205e,
    0x004040404040403e, 0x008080808080807e, 0x0001010101017e00,
    0x0002020202027c00, 0x0004040404047a00, 0x0008080808087600,
    0x0010101010106e00, 0x0020202020205e00, 0x0040404040403e00,
    0x0080808080807e00, 0x00010101017e0100, 0x00020202027c0200,
    0x00040404047a0400, 0x0008080808760800, 0x00101010106e1000,
    0x00202020205e2000, 0x00404040403e4000, 0x00808080807e8000,
    0x000101017e010100, 0x000202027c020200, 0x000404047a040400,
    0x0008080876080800, 0x001010106e101000, 0x002020205e202000,
    0x004040403e404000, 0x008080807e808000, 0x0001017e01010100,
    0x0002027c02020200, 0x0004047a04040400, 0x0008087608080800,
    0x0010106e10101000, 0x0020205e20202000, 0x0040403e40404000,
    0x0080807e80808000, 0x00017e0101010100, 0x00027c0202020200,
    0x00047a0404040400, 0x0008760808080800, 0x00106e1010101000,
    0x00205e2020202000, 0x00403e4040404000, 0x00807e8080808000,
    0x007e010101010100, 0x007c020202020200, 0x007a040404040400,
    0x0076080808080800, 0x006e101010101000, 0x005e202020202000,
    0x003e404040404000, 0x007e808080808000, 0x7e01010101010100,
    0x7c02020202020200, 0x7a04040404040400, 0x7608080808080800,
    0x6e10101010101000, 0x5e20202020202000, 0x3e40404040404000,
    0x7e80808080808000
};

// bishop blocker mask for each possible square
uint64_t bmasks[64] = {
    0x0040201008040200, 0x0000402010080400, 0x0000004020100a00,
    0x0000000040221400, 0x0000000002442800, 0x0000000204085000,
    0x0000020408102000, 0x0002040810204000, 0x0020100804020000,
    0x0040201008040000, 0x00004020100a0000, 0x0000004022140000,
    0x0000000244280000, 0x0000020408500000, 0x0002040810200000,
    0x0004081020400000, 0x0010080402000200, 0x0020100804000400,
    0x004020100a000a00, 0x0000402214001400, 0x0000024428002800,
    0x0002040850005000, 0x0004081020002000, 0x0008102040004000,
    0x0008040200020400, 0x0010080400040800, 0x0020100a000a1000,
    0x0040221400142200, 0x0002442800284400, 0x0004085000500800,
    0x0008102000201000, 0x0010204000402000, 0x0004020002040800,
    0x0008040004081000, 0x00100a000a102000, 0x0022140014224000,
    0x0044280028440200, 0x0008500050080400, 0x0010200020100800,
    0x0020400040201000, 0x0002000204081000, 0x0004000408102000,
    0x000a000a10204000, 0x0014001422400000, 0x0028002844020000,
    0x0050005008040200, 0x0020002010080400, 0x0040004020100800,
    0x0000020408102000, 0x0000040810204000, 0x00000a1020400000,
    0x0000142240000000, 0x0000284402000000, 0x0000500804020000,
    0x0000201008040200, 0x0000402010080400, 0x0002040810204000,
    0x0004081020400000, 0x000a102040000000, 0x0014224000000000,
    0x0028440200000000, 0x0050080402000000, 0x0020100804020000,
    0x0040201008040200
};