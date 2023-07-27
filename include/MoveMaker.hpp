#pragma once 

#include "Board.hpp"
#include "../include/defs.hpp"
#include "hash.hpp"



class MoveMaker{
public:

Board_State board_state;



void MakeMove(int move);
void UndoMove();
MoveMaker(string FEN=START_POS);
// MoveMaker();
void parse_moves_string(vector<int>& , string moves_string) ;



};