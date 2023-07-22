#include "../include/MoveMaker.hpp"
#include "../include/defs.hpp"


MoveMaker::MoveMaker(string FEN){
    board_state = Board_State(FEN);

    
}


void MoveMaker::MakeMove(int move){
int from = move & 0x3F;
int to = (move >> 6) & 0x3F;

int side = board_state.side;

if((0xC000 & move )== 2){
    Square sq = board_state.piecePlacement[(board_state.enPas+PAWN_PUSH_DIRECTION[1^side])];
    board_state.updatePieceBoard( sq ,sq.pieceOccupying , 0 );
    board_state.MovePiece(from, to);
    
   
}

if((0xC000 & move)==3){

    switch (to) {
    case 2: //WKQC
        board_state.MovePiece(from, to);
        board_state.MovePiece(0, 3);
        break;
    case 6: //WKSC
        board_state.MovePiece(from, to);
        board_state.MovePiece(7, 5);
        break;

    case 58: //BKQC
        board_state.MovePiece(from, to);
        board_state.MovePiece(56, 59);
        break;

    case 62: //BKSC
        board_state.MovePiece(from, to);
        board_state.MovePiece(63, 61);
        break;

    }

}

board_state.castlePerm &= CastlePerm[from];
board_state.castlePerm &= CastlePerm[to];
board_state.enPas = NO_SQ;


}
