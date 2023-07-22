#pragma once 

#include "defs.hpp"

#include "Piece.hpp"


class Square{
    public:
    int squareNo;
    Piece pieceOccupying;
     SquareType squareType;


    Square(int squareNo=NO_SQ);
    Square(int squareNo , Piece pieceOccupying , SquareType squareType);

    

    bool operator==(const Square &other) const ;

    
struct  HashFunction
  {
    size_t operator()(const Square & sq) const;
    };



};



