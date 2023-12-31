#include "../include/moveorder.hpp"
#include "../include/Board.hpp"
#include "../include/defs.hpp"




MoveOrderer::MoveOrderer(Board_State* board_state){
    betaCutters = * new vector<unordered_set<int>>(MAX_DEPTH,unordered_set<int>(MAX_BCUTS_STORED));
    alphaImprovers = vector<vector<int>>(13, vector<int>(64, 0));
    // std::fill( &alphaImprovers[0][0], &alphaImprovers[13][0]  , 0ULL );
    this->board_state=board_state;


};

 bool MoveOrderer::comparator:: operator()(int move1 , int move2) const {


    if (move1 == pvMove && move2 != pvMove) {
      return true;
    }

    if (move2 == pvMove && move1 != pvMove) {
      return false;
    }

    int move1_from_piece = ((*piecePlacement)[(move1) & 0x3F]).pieceOccupying.pieceType;
    int move2_from_piece = ((*piecePlacement)[(move2) & 0x3F]).pieceOccupying.pieceType;
    int move1_to_piece = ((*piecePlacement)[(move1>>6) & 0x3F]).pieceOccupying.pieceType;
    int move2_to_piece = ((*piecePlacement)[(move2>>6) & 0x3F]).pieceOccupying.pieceType;

    // if(((*piecePlacement)[(move1>>6) & 0x3F]).pieceOccupying !=NO_PIECE && ((*piecePlacement)[(move2>>6) & 0x3F]).pieceOccupying ==NO_PIECE){
    //     return true;
    // }
    // if(((*piecePlacement)[(move2>>6) & 0x3F]).pieceOccupying !=NO_PIECE && ((*piecePlacement)[(move1>>6) & 0x3F]).pieceOccupying ==NO_PIECE){
    //     return false;
    // }


     if(move1_to_piece!=NO_PIECE || move2_to_piece!=NO_PIECE){
        return (MvvLva[move1_from_piece] [move1_to_piece] > MvvLva[move2_from_piece][move2_to_piece]);
    }

    bool x1 = (*betaCutters)[ply].find(move1) != (*betaCutters)[ply].end();
    bool x2 = (*betaCutters)[ply].find(move2) != (*betaCutters)[ply].end();
    if(x1 && !x2){
        return true;
    }

    if(x2 && !x1){
        return false;
    }


    // cout<<"DEBUG: Alpha Improver Piece FROM SQUARE IS "<<(*piecePlacement)[(move1) & 0x3F].pieceOccupying.pieceType<<endl; 
    return (*alphaImprovers)[((*piecePlacement)[(move1) & 0x3F]).pieceOccupying.pieceType] [(move1>>6) & 0x3F ] > (*alphaImprovers)[(*piecePlacement)[(move2) & 0x3F].pieceOccupying.pieceType][(move2>>6) & 0x3F];


  }

 MoveOrderer::comparator::comparator(int pl, int pvMove, vector<Square> * piecePlacement,
               vector<unordered_set<int>> *betaCutters, vector<vector<int>> * alphaImprovers){

    this->ply=pl;
    this->pvMove=pvMove;
    this->betaCutters=betaCutters;
    this->piecePlacement=piecePlacement;
    this->alphaImprovers=alphaImprovers;
               }
void MoveOrderer::sortMoves(vector<int> &moveList, int pl , int pvMove) {

    
    std::sort(moveList.begin(), moveList.end(),comparator (pl, pvMove, &(board_state->piecePlacement), &betaCutters, &alphaImprovers));
  
  }

void MoveOrderer::reset(){
    betaCutters = * new vector<unordered_set<int>>(MAX_DEPTH,unordered_set<int>(MAX_BCUTS_STORED));
    alphaImprovers = vector<vector<int>>(13, vector<int>(64, 0));
    // std::fill( &alphaImprovers[0][0], &alphaImprovers[13][0]  , 0ULL );
}
