#pragma once 

#include "Board.hpp"
#include "../include/defs.hpp"



class MoveMaker{
public:

Board_State board_state;
U64 MakeMove(int move);
void UndoMove(U64 move);
MoveMaker(string FEN);
MoveMaker();
void parse_moves_string(string moves_string) ;



};