#pragma once 
#include "defs.hpp"


class Piece{
       public:

       PieceType  pieceType;
       
       int pieceSquare;
      
       Piece(PieceTypeWithoutColor pieceType, color pieceColor , int pieceSquare = NO_SQ);
       Piece();
       Piece( PieceType pieceType, int pieceSquare=NO_SQ);
       color get_piece_color() ;
       bool operator==(const Piece &other) const;
       bool operator!=(const Piece &other) const;
       
       bool isPieceEmpty();
       bool isPiecePawn();
       bool isPieceKnight();
       bool isPieceBishop();
       bool isPieceRook();
       bool isPieceQueen();
       bool isPieceKing();
       bool isPieceWhite();
       bool isPieceBlack();
       bool isPieceBoth();
       bool isPieceSameColor(Piece other);
       bool isPieceSameType(Piece other);
};