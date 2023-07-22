#pragma once 

#include "defs.hpp"
#include "Square.hpp"
#include "Board.hpp"

class MoveGen{
    public:
    U64 attackBoards[2][7] =  {0ULL};
    U64 kingDangerSquares[2] = {0ULL};

    vector<int> moveList ;


    U64 captureBoard[2] = {0ULL};
    U64 kingCheckingPieces[2] = {0ULL};

    U64 pinnedPiecesMap[2] = {0ULL};

    U64 pushMask [2] = {~0ULL};
    U64 enPassantCaptureSquare = 0ULL;

    int numCheckers = 0;

   

    int num_checkers[2] = {0};
 
    void update_attack_boards(Board_State &board_state , int side );
    U64 get_attack_board_for_piece(Square sq ,  PieceType piece , U64 occupancy );
    void update_KingMovesInfo(Board_State &board_state , int side );
    void update_capture_board(Board_State &board_state , int side );
    void update_push_mask( Board_State &BS  , U64 pieceAttack , int side , PieceTypeWithoutColor PT , int sq);
    void  generate_moves(Board_State &board_state , int side);
    void update_enPasssantInfo(Board_State &board_state , int side);
    void reset();
    void BitmapToMoveList(int sq , U64 MoveMap ,int EnPassant , bool Promotion  );

    void GenerateMovesForPinned(Board_State &board_state , int side);
    bool isSqAttacked(Board_State &board_state ,U64 occupancyMap, int sq , int side);
    bool isSqAttacked(Board_State &board_state , int sq , int side , int EnPassanting  );
   

};