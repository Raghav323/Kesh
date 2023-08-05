#pragma once
#include "Board.hpp"
#include "MoveMaker.hpp"
#include "defs.hpp"
#include "movegen.hpp"
#include "moveorder.hpp"


class Search {
public:
  MoveMaker moveMaker;
  MoveGen movegen;

  MoveOrderer moveOrderer;

  Search(string FEN = START_POS);
  U64 perft(int depth, bool root);
  void resetSearch();
  unordered_map<U64, int> pvTable;
  int get_pv_line(int);
  void searchPos();
  void checkUp();

  int AlphaBeta(int alpha, int beta, int depth);

  int Quiescense(int alpha, int beta);


  std::chrono::time_point<std::chrono::system_clock> starttime ;
    std::chrono::time_point<std::chrono::system_clock> stoptime ;

   
  int depth ;
  bool timeset ;
  int movestogo ;
  int infinite ;
  long nodes;
  bool quit ;
  bool stopped ;
  float fh ;
  float fhf ;

   

};
