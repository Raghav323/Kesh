#include "Board.hpp"
#include "defs.hpp"
#include "movegen.hpp"
#include "MoveMaker.hpp"
#include <unordered_map>

class Engine{
    public:
    MoveMaker moveMaker;
    MoveGen movegen ; 
    Engine(string FEN=START_POS);
    U64 perft(int depth, bool root);
    void resetEngine();
    unordered_map<U64,int > pvTable ;
    

};
