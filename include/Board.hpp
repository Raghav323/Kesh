
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
    int numPieces[13];

    int eval[2];
    

    U64 stateKey=0ULL;

    U64 OccupancyMap ;

    U64 OccupancyMapColor[2];

    U64 OccupancyMapBQ[2] ;
    U64 OccupancyMapRQ[2] ;
    U64 OccupancyMapP[2];
    U64 OccupancyMapN[2] ;

    Zobrist hasher; 

    


    // U64 piecesMap[13]={0ULL};

    unordered_map<U64,int> history;
    stack<U64> undoStack;
    
    std::unordered_map<PieceType,unordered_set<Square , Square::HashFunction >> pieceBoard ;

    void printBoard();
 
    Board_State(std::string FEN=START_POS);

    void updatePieceBoard(Square sq , Piece piece , bool add);
    void MovePiece(int from , int to );


    void resetBoard();

    bool isRepetition();
    void increment_evalPos(Square sq , Piece piece , bool add,bool endgame);

    void  inline registerUndoMove(){history[stateKey]-=1; if(history[stateKey]==0){history.erase(stateKey);}};
    void inline registerMove(){
        if (history.find(stateKey) == history.end()){
            history[stateKey]=0;
        } 
        history[stateKey]+=1;
    };
};

