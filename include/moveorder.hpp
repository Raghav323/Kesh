#pragma once

#include "Board.hpp"
#include "Square.hpp"
#include "defs.hpp"

#include <unordered_set>
#include <vector>

class MoveOrderer {
public:
  class comparator {
    public:
    int ply;
    int pvMove;
    vector<unordered_set<int>> *betaCutters;
    int alphaImprovers[13][64];
    vector<Square> *piecePlacement;
    

  public:
    comparator(int depth, int pvMove, vector<Square> * piecePlacement,
               vector<unordered_set<int>> *betaCutters, int alphaImprovers[13][64]);
    bool operator()(int move1, int move2) const;
  };

  MoveOrderer(Board_State *board_state);
  vector<unordered_set<int>> betaCutters;

  int alphaImprovers[13][64];
  Board_State *board_state;

   void registerAlphaImprover(int move, int depth, int score) {


    alphaImprovers[board_state->piecePlacement[(move) & 0x3F].pieceOccupying.pieceType]
                  [(move >> 6) & 0x3F] = (depth + (score) / 10);
  }

   void registerBetaCutter(int move, int depth) {
    if(betaCutters[depth].size()<MAX_BCUTS_STORED){
    betaCutters[depth].insert(move);
    }
  }

  void sortMoves(vector<int> &moveList, int pl , int pvMove);
};