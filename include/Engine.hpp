#include "Board.hpp"
#include "defs.hpp"
#include "movegen.hpp"
#include "MoveMaker.hpp"

class Engine{
    public:
    MoveMaker moveMaker;
    MoveGen movegen ; 
    Engine(string FEN=START_POS);
    U64 perft(int depth, bool root);
    

};
