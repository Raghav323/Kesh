#include "../include/Square.hpp"
#include "../include/defs.hpp"



Square::Square(int squareNo) { this->squareNo = squareNo; this->pieceOccupying = Piece(NO_PIECE,BOTH); this->squareType = OFFBOARD; }
Square::Square(int squareNo , Piece pieceOccupying , SquareType s ) { this->squareNo = squareNo; this->pieceOccupying = pieceOccupying; this->squareType = s;}



bool Square::operator==(const Square &other) const {
  return this->squareNo == other.squareNo;
}


 size_t  Square:: HashFunction::operator()(const Square& sq) const
    {
      
      return hash<int>()(sq.squareNo);
}

