
#pragma once 

#include "defs.hpp"
#include "Square.hpp"
#include "hash.hpp"


class Board_State{
    public:
    std::vector<Square> piecePlacement = std::vector<Square>(BOARD_SQ,Square(NO_SQ));


    
    bool side;
    int enPas;
    int fiftyMove;
    int castlePerm;

    int ply;
    int hisPly;

    int fullMoves;
    int KingSq[2];

    

    U64 stateKey=0ULL;

    U64 OccupancyMap ;

    U64 OccupancyMapColor[2];

    U64 OccupancyMapBQ[2] ;
    U64 OccupancyMapRQ[2] ;
    U64 OccupancyMapP[2];
    U64 OccupancyMapN[2] ;

    Zobrist hasher; 

    


    // U64 piecesMap[13]={0ULL};

    unordered_set<U64> history;
    
    std::unordered_map<PieceType,unordered_set<Square , Square::HashFunction >> pieceBoard ;

    void printBoard();
 
    Board_State(std::string FEN=START_POS);

    void updatePieceBoard(Square sq , Piece piece , bool add);
    void MovePiece(int from , int to );


    void resetBoard();

    bool isRepetition();
};

