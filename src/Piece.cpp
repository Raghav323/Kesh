#include "../include/defs.hpp"
#include "../include/Piece.hpp"


  Piece::Piece( PieceType pieceType , int pieceSquare) {
    this->pieceType = pieceType;
    this->pieceSquare= pieceSquare;
  }

  Piece::Piece( PieceTypeWithoutColor pieceType, color pieceColor , int pieceSquare) {
    this->pieceType = get_piece_type(pieceType, (int)pieceColor);
    this->pieceSquare= pieceSquare;
  }

  Piece::Piece() {
    this->pieceType = NO_PIECE;
    this->pieceSquare= NO_SQ;
  }

  color Piece::get_piece_color() {
    if(pieceType==NO_PIECE) return BOTH;
    if(pieceType <=6) return WHITE;
    else return BLACK;
  }


  bool Piece::operator==(const Piece &other) const {
    return (this->pieceType == other.pieceType );
  }

  bool Piece::operator!=(const Piece &other) const {
    return (this->pieceType != other.pieceType );
  }


  bool Piece::isPieceEmpty() { return (this->pieceType == NO_PIECE); }

  bool Piece::isPiecePawn() {
    return (this->pieceType == wP || this->pieceType == bP);
  }

  bool Piece::isPieceKnight() {
    return (this->pieceType == wK || this->pieceType == bK);
  }

  bool Piece::isPieceBishop() {
    return (this->pieceType == wB || this->pieceType == bB);
  }

  bool Piece::isPieceRook() {
    return (this->pieceType == wR || this->pieceType == bR);
  }

  bool Piece::isPieceQueen() {
    return (this->pieceType == wQ || this->pieceType == bQ);
  }

  bool Piece::isPieceKing() {
    return (this->pieceType == wK || this->pieceType == bK);
  }

  bool Piece::isPieceWhite() { return (this->pieceType <=6); }

  bool Piece::isPieceBlack() { return (this->pieceType >=7); }

  

  bool Piece::isPieceSameColor(Piece other) {
    return (!((this->pieceType <=6)^(other.pieceType <=6)));
  }

  bool Piece::isPieceSameType(Piece other) {
    return (this->pieceType == other.pieceType);
  }
