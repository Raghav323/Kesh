#pragma once 

#include "Board.hpp"
#include "../include/defs.hpp"



class MoveMaker{
public:

Board_State board_state;
void MakeMove(int move);

MoveMaker(string FEN);



};