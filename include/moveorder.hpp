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
    
    // cout<<"DEBUG ::: "<<((move) & 0x3F)<<" "<<((move >> 6) & 0x3F)<<endl;
    alphaImprovers[board_state->piecePlacement[(move) & 0x3F].pieceOccupying.pieceType]
                  [(move >> 6) & 0x3F] = (depth + (score) / 10);

    // for(int rank = RANK_8; rank >= RANK_1; rank--){
    //         for(int file = FILE_A; file <= FILE_H; file++){
    //             int sq = FR2SQ(file,rank);
    //             cout<<sq<<endl;
    //             Square sqi = (*board_state).piecePlacement[sq];
    //         }
    //         std::cout << std::endl;
    //     }
    
  }

   void registerBetaCutter(int move, int depth) {
    if(betaCutters[depth].size()<MAX_BCUTS_STORED){
    betaCutters[depth].insert(move);
    }
  }

  void sortMoves(vector<int> &moveList, int pl , int pvMove);
  void reset();
  void inline heapifyMoves(vector<int> &moveList, int pl , int pvMove) {

    std::make_heap(moveList.begin(), moveList.end(),comparator (pl, pvMove, &(board_state->piecePlacement), &betaCutters, alphaImprovers));
  }

  

int inline popMove(vector<int> &moveList, int pl , int pvMove) {

    std::pop_heap(moveList.begin(), moveList.end(),comparator (pl, pvMove, &(board_state->piecePlacement), &betaCutters, alphaImprovers));
    int mv = moveList.back();
    moveList.pop_back();
    return mv;
  }


};