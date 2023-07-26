#pragma once 

#include "Board.hpp"
#include "../include/defs.hpp"
#include "hash.hpp"



class MoveMaker{
public:

Board_State board_state;



U64 MakeMove(int move);
void UndoMove(U64 move);
MoveMaker(string FEN=START_POS);
// MoveMaker();
void parse_moves_string(stack<U64> &undoMoves,string moves_string) ;



};