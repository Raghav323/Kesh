#include "Board.hpp"
#include "MoveMaker.hpp"
#include "defs.hpp"
#include "movegen.hpp"
#include <unordered_map>

class Search {
public:
  MoveMaker moveMaker;
  MoveGen movegen;
  Search(string FEN = START_POS,int depth=1);
  U64 perft(int depth, bool root);
  void resetSearch();
  unordered_map<U64, int> pvTable;
  int get_pv_line();
  void searchPos();
  void checkUp();

  int AlphaBeta(int alpha, int beta, int depth);

  int Quiescense(int alpha, int beta);


  std::chrono::time_point<std::chrono::system_clock> starttime ;
  std::chrono::time_point<std::chrono::system_clock> stoptime ;
  int depth ;
  int timeset ;
  int movestogo ;
  int infinite ;
  long nodes;
  int quit ;
  int stopped ;
  float fh ;
  float fhf ;

};
