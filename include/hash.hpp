#pragma once
#include "../include/defs.hpp"

class Zobrist {
public:
  U64 pieceKeys[64][13];
  U64 sideKey;
  U64 castleKeys[16];
  

  std::mt19937_64 gen;
  std::uniform_int_distribution<unsigned long long> dis;

  Zobrist();

U64  hashSide(U64 stateKey) ;

  U64  hashCastle(U64 stateKey,int castlePerm);

  U64  hashPiece(U64 stateKey ,PieceType piece, int sq);

};