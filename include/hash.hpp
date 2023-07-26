#pragma once
#include "../include/defs.hpp"

class Zobrist {
public:
  U64 pieceKeys[64][13];
  U64 sideKey;
  U64 castleKeys[16];
  U64 *sKey;

  std::mt19937_64 gen;
  std::uniform_int_distribution<unsigned long long> dis;

  Zobrist(U64 *posKey);

  void  hashSide() ;

  void  hashCastle(int castlePerm);

  void  hashPiece(PieceType piece, int sq);

};