
#pragma once 

#include "defs.hpp"
#include "Square.hpp"


class Board_State{
    public:
    std::vector<Square> piecePlacement = std::vector<Square>(BOARD_SQ,Square(NO_SQ));


    
    bool side;
    int enPas;
    int fiftyMove;
    int castlePerm = 0;

    int ply;
    int hisPly;

    int fullMoves;
    int KingSq[2]={NO_SQ};

    

    U64 posKey;

    U64 OccupancyMap = 0ULL;

    U64 OccupancyMapColor[2] = {0ULL};

    U64 OccupancyMapBQ[2] = {0ULL};
    U64 OccupancyMapRQ[2] = {0ULL};
    U64 OccupancyMapP[2] = {0ULL};
    U64 OccupancyMapN[2] = {0ULL};


    // U64 piecesMap[13]={0ULL};
    
    std::unordered_map<PieceType,unordered_set<Square , Square::HashFunction >> pieceBoard ;

    void printBoard();
 
    Board_State(std::string FEN=START_POS);

    void updatePieceBoard(Square sq , Piece piece , bool add);
    void MovePiece(int from , int to );



};

