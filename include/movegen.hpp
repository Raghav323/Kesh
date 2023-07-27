#pragma once 

#include "defs.hpp"
#include "Square.hpp"
#include "Board.hpp"
#include <vector>

class MoveGen{
    public:
    U64 attackBoards[2][7] ;
    U64 kingDangerSquares[2] ;

    


    U64 captureBoard[2] ;
    U64 kingCheckingPieces[2] ;

    U64 pinnedPiecesMap[2];

    U64 pushMask [2];
    U64 enPassantCaptureSquare ;

   

   

    int num_checkers[2] ;
 
    void update_attack_boards(Board_State &board_state , int side );
    U64 get_attack_board_for_piece(Square sq ,  PieceType piece , U64 occupancy );
    void update_KingMovesInfo( Board_State &board_state , int side );
    void update_capture_board(Board_State &board_state , int side );
    void update_push_mask( Board_State &BS  , U64 pieceAttack , int side , PieceTypeWithoutColor PT , int sq);
    int  generate_moves(vector<int> &moveList , Board_State &board_state , int side);
    void update_enPasssantInfo(Board_State &board_state , int side);
    void reset();
    void BitmapToMoveList(vector<int> &moveList,int sq , U64 MoveMap ,int EnPassant , bool Promotion  );

    void GenerateMovesForPinned(vector<int> &moveList,Board_State &board_state , int side);
    bool isSqAttacked(Board_State &board_state ,U64 occupancyMap, int sq , int side);
    bool isSqAttacked(Board_State &board_state , int sq , int side , int EnPassanting  );
    int  generate_capture_moves(vector<int> &moveList , Board_State &board_state , int side);

   
   

};