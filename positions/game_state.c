#include "game_state.h"

struct state stack[16] = { 0 };
uint8_t stk_top = 0;

// save the current game state, push it onto the game state stack
void PUSH_STATE()     {                                                       
    memcpy(stack[stk_top].bitboards, bitboards, 128);                         
    memcpy(stack[stk_top].move_list, move_list, 1024);                        
    stack[stk_top].move_count = move_count,                                   
    stack[stk_top].turn = turn,                                               
    stack[stk_top].epsq = epsq,                                               
    stack[stk_top].wksc = wksc,                                               
    stack[stk_top].wqsc = wqsc,                                               
    stack[stk_top].bksc = bksc,                                               
    stack[stk_top].bqsc = bqsc;                                               
    stk_top++;                                                                
}

// pop game state from the stack
void POP_STATE() {
    stk_top--;                                                      
    memcpy(bitboards, stack[stk_top].bitboards, 128);                         
    memcpy(move_list, stack[stk_top].move_list, 1024);                        
    move_count = stack[stk_top].move_count,                                   
    turn = stack[stk_top].turn,                                               
    epsq = stack[stk_top].epsq,                                               
    wksc = stack[stk_top].wksc,                                               
    wqsc = stack[stk_top].wqsc,                                               
    bksc = stack[stk_top].bksc,                                               
    bqsc = stack[stk_top].bqsc;                                               
    memset(&stack[stk_top], 0, 1160);                                                                                           
}