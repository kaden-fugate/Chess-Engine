#include "game.h"

void print_board(){

    printf("|-------|-------|-------|-------|-------|-------|-------|-------|\n");

    for (int i = 7; i >= 0; i--){

        printf("|       |       |       |       |       |       |       |       |\n|");
        
        for (int j = 0; j < 8; j++){
            
            if (bk & (1ULL << ((i * 8) + j))) {
                printf("   K   |", i, j);
            }
            else if (bq & (1ULL << ((i * 8) + j))) {
                printf("   Q   |", i, j);
            }
            else if (br & (1ULL << ((i * 8) + j))) {
                printf("   R   |", i, j);
            }
            else if (bb & (1ULL << ((i * 8) + j))) {
                printf("   B   |", i, j);
            }
            else if (bn & (1ULL << ((i * 8) + j))) {
                printf("   N   |", i, j);
            }
            else if (bp & (1ULL << ((i * 8) + j))) {
                printf("   P   |", i, j);
            }

            else if (wk & (1ULL << ((i * 8) + j))) {
                printf("   k   |", i, j);
            }
            else if (wq & (1ULL << ((i * 8) + j))) {
                printf("   q   |", i, j);
            }
            else if (wr & (1ULL << ((i * 8) + j))) {
                printf("   r   |", i, j);
            }
            else if (wb & (1ULL << ((i * 8) + j))) {
                printf("   b   |", i, j);
            }
            else if (wn & (1ULL << ((i * 8) + j))) {
                printf("   n   |", i, j);
            }
            else if (wp & (1ULL << ((i * 8) + j))) {
                printf("   p   |", i, j);
            }

            else { printf("       |"); }

        }

        printf("\n|       |       |       |       |       |       |       |       |\n");
        printf("|-------|-------|-------|-------|-------|-------|-------|-------|\n");

    }

}