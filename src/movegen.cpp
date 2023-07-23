#include "../include/movegen.hpp"
#include "../include/defs.hpp"
#include <array>
#include <new>
#include <vector>
#include "../include/Piece.hpp"


U64 MoveGen::get_attack_board_for_piece(Square sq, PieceType piece,
                                        U64 occupancy) {
  U64 attackBoard = 0ULL;

  switch (piece) {
  case wP:
    attackBoard = pawn_attacks[0][sq.squareNo];
    break;
  case bP:
    attackBoard = pawn_attacks[1][sq.squareNo];
    break;
  case wN:
    attackBoard = knight_attacks[sq.squareNo];
    kingDangerSquares[1] |= attackBoard;
  case bN:
    attackBoard = knight_attacks[sq.squareNo];
    // print_bitboard(attackBoard);
    // cout<<"SQNO:  "<<sq.squareNo<<endl;
    break;
  case bB:
  case wB:
    attackBoard = get_bishop_attacks(sq.squareNo, occupancy);
    break;
  case bR:
  case wR:
    attackBoard = get_rook_attacks(sq.squareNo, occupancy);
    break;
  case wQ:
  case bQ:
    attackBoard |= get_rook_attacks(sq.squareNo, occupancy);
    attackBoard |= get_bishop_attacks(sq.squareNo, occupancy);
    break;
  default:
    break;
  }
  return attackBoard;
}

void MoveGen::update_attack_boards(Board_State &board_state, int side) {
  // enumerate through all piece Types of side and get their attack boards
  U64 attackBoard = 0ULL;
  for (int i = 1; i <= 5; i++) {
    PieceType piece = get_piece_type((PieceTypeWithoutColor)i, side);
    //cout << "PieceType" << piece << endl;
    for (auto sq : board_state.pieceBoard[piece]) {
      //cout << "Piece : " << piece << "Square : " << sq.squareNo << endl;
      U64 pieceAttackBoard = get_attack_board_for_piece(sq, piece, board_state.OccupancyMap);
      
      if (get_bit(pieceAttackBoard, board_state.KingSq[1^side])) {

        kingCheckingPieces[1^side] |= (1ULL << sq.squareNo);
       
        num_checkers[1^side]++;
         if(num_checkers[1^side]==1){
          pushMask[1^side] = rectlookup[sq.squareNo][board_state.KingSq[1^side]];
          // update_push_mask( board_state, pieceAttackBoard , 1^side, (PieceTypeWithoutColor)i , sq.squareNo);
        }
        

      }

      attackBoards[side][i] |= pieceAttackBoard;
          
    }
    attackBoard |= attackBoards[side][i];
  }

  


  attackBoards[side][0] = attackBoard;

  
}

// void MoveGen:: update_push_mask( Board_State &BS , U64 pieceAttack , int side , PieceTypeWithoutColor PT , int sq){
//   // TODO : Make this more efficient and remove branching 
  
//   if(PT==PAWN || PT==KNIGHT ){
//     return ;
//   }

//   if(PT==QUEEN){
//     U64 TempMask1 = (get_bishop_attacks(sq , 0ULL | (1ULL << BS.KingSq[side])) | (1ULL)<<sq ) & get_bishop_attacks(BS.KingSq[side],0ULL | (1ULL << sq ));
//     if (!(get_bit(TempMask1, sq))){
//       TempMask1 = (get_rook_attacks(sq , 0ULL | (1ULL << BS.KingSq[side]))| (1ULL<<sq)) & get_rook_attacks(BS.KingSq[side],0ULL | (1ULL << sq ));
//     }

//     pushMask[side] = TempMask1; 
//     clear_bit(pushMask[side], sq);
//     // clear_bit(pushMask[side], BS.KingSq[side]);
   
    
//   }

//   else if(PT==ROOK){
//     pushMask[side] = get_rook_attacks(sq , 0ULL | (1ULL << BS.KingSq[side])) & get_rook_attacks(BS.KingSq[side],0ULL | (1ULL << sq ));
    
//   }

//   else if(PT==BISHOP){
//     pushMask[side] = get_bishop_attacks(sq , 0ULL | (1ULL << BS.KingSq[side])) & get_bishop_attacks(BS.KingSq[side],0ULL | (1ULL << sq ));
   
//   }

//   else{
//     cout<<"ERROR"<<endl;
//   }

  
// }
void MoveGen::update_KingMovesInfo(vector<int>& MoveList , Board_State &board_state, int side) {
  

  for (auto sq : board_state.pieceBoard[get_piece_type(BISHOP, side ^ 1)]) {
    kingDangerSquares[side] |= get_bishop_attacks(
        sq.squareNo, board_state.OccupancyMap & ~(1ULL << board_state.KingSq[side]));
  }

  for (auto sq : board_state.pieceBoard[get_piece_type(ROOK, side ^ 1)]) {
    kingDangerSquares[side] |= get_rook_attacks(
        sq.squareNo, board_state.OccupancyMap & ~(1ULL << board_state.KingSq[side]));
  }

  for (auto sq : board_state.pieceBoard[get_piece_type(QUEEN, side ^ 1)]) {
    kingDangerSquares[side] |= get_bishop_attacks(
        sq.squareNo, board_state.OccupancyMap & ~(1ULL << board_state.KingSq[side]));
    kingDangerSquares[side] |= get_rook_attacks(
        sq.squareNo, board_state.OccupancyMap & ~(1ULL << board_state.KingSq[side]));
  }

  kingDangerSquares[side] |= attackBoards[side ^ 1][1];
  kingDangerSquares[side] |= attackBoards[side ^ 1][2];
  kingDangerSquares[side] |= king_attacks[board_state.KingSq[1^side]];

  U64 King_Moves =   king_attacks[board_state.KingSq[side]] &
      ~(board_state.OccupancyMapColor[side] | kingDangerSquares[side]) ;
  


  BitmapToMoveList(MoveList,board_state.KingSq[side] , King_Moves ,NO_SQ , false);

  // moveList.push_back(make_pair(Piece(KING,(color) side,board_state.KingSq[side]), Moves[side][KING][0]));



  // attackBoards[side][KING] = King_Moves;
  attackBoards[side][0] |= King_Moves;
}



void MoveGen::update_capture_board(Board_State &board_state , int side ){


  




  if(num_checkers[side]==0){
    captureBoard[side] = attackBoards[side][0] & board_state.OccupancyMapColor[side^1];
    pushMask[side]=(~0ULL) & (~board_state.OccupancyMapColor[side]);
  }
  else{
    captureBoard[side] = attackBoards[side][0] & kingCheckingPieces[side];
  }



}


// void MoveGen::update_push_board(bad_alloc &boa)


int MoveGen:: generate_moves(vector<int> &moveList , Board_State &board_state , int side){

  reset();
  update_attack_boards(board_state ,0);
  update_attack_boards(board_state ,1);
  update_KingMovesInfo(moveList,board_state, side);
  update_enPasssantInfo(board_state, side);
  update_capture_board(board_state, side);


  if(num_checkers[side]>1){return moveList.size();;}

  GenerateMovesForPinned(moveList,board_state , side);

  // if(num_checkers[side]!=0){
  // //update_push_mask(board_state, side);
  // }

  // get all pawn pieces 

  for(auto sq : board_state.pieceBoard[get_piece_type(PAWN,side)]){
    int sqNo = sq.squareNo;
    if(get_bit(pawn_attacks[side][sqNo],board_state.enPas)){
      // cout<<"EPASCAP" <<enPassantCaptureSquare<<endl;
       //cout<<"DEBUG "<<"IS ATTACKED ??  "<<isSqAttacked(board_state, (board_state.OccupancyMap|(1ULL<<board_state.enPas)) & (~((1ULL<<sqNo) | (enPassantCaptureSquare))), board_state.KingSq[side], side)<<endl;
      // cout<<"DEBUG 3 : "<<endl;
      
     // print_bitboard((board_state.OccupancyMap|(1ULL<<board_state.enPas)) & (~ ((1ULL<<sqNo) | enPassantCaptureSquare )));
      if(  ( ( (enPassantCaptureSquare & captureBoard[side])!=0ULL) | (get_bit(pushMask[side], board_state.enPas) ) )  && (!isSqAttacked(board_state, board_state.KingSq[side], side,sqNo))  ){
        BitmapToMoveList(moveList,sqNo , board_state.enPas  , board_state.enPas , false);
      }


      
      
    }

  
    if(!get_bit(pinnedPiecesMap[side],sqNo)){
      
      BitmapToMoveList(moveList,sqNo , (pawn_attacks[side][sqNo] & captureBoard [side]) | (get_pawn_moves(sqNo, side, board_state.OccupancyMap ) & pushMask[side]),NO_SQ , (48<=sqNo && sqNo<=55 && side==WHITE) || (8<=sqNo && sqNo<=15 && side==BLACK));

    }

    

  }

  // get all knight pieces

  for(auto sq : board_state.pieceBoard[get_piece_type(KNIGHT,side)]){
    int sqNo = sq.squareNo;
    if(get_bit(pinnedPiecesMap[side],sqNo)){
      continue;
    }

    BitmapToMoveList(moveList,sqNo , (knight_attacks[sqNo] & ( captureBoard[side] | pushMask[side])),NO_SQ , false);
  }

  // get all bishop pieces

  for(auto sq : board_state.pieceBoard[get_piece_type(BISHOP,side)]){
    int sqNo = sq.squareNo;
    if(get_bit(pinnedPiecesMap[side],sqNo)){
      continue;
    }

    BitmapToMoveList(moveList,sqNo , (get_bishop_attacks(sqNo , board_state.OccupancyMap) & ( captureBoard[side] | pushMask[side])),NO_SQ , false);
  }

  // get all rook pieces

  for(auto sq : board_state.pieceBoard[get_piece_type(ROOK,side)]){
    int sqNo = sq.squareNo;
    if(get_bit(pinnedPiecesMap[side],sqNo)){
      continue;
    }
    BitmapToMoveList(moveList, sqNo , (get_rook_attacks(sqNo , board_state.OccupancyMap) & ( captureBoard[side] | pushMask[side])),NO_SQ , false);
  }

  // get all queen pieces

  for(auto sq : board_state.pieceBoard[get_piece_type(QUEEN,side)]){
    int sqNo = sq.squareNo;
    if(get_bit(pinnedPiecesMap[side],sqNo)){
      continue;
    }
    BitmapToMoveList(moveList , sqNo , (get_bishop_attacks(sqNo , board_state.OccupancyMap) | get_rook_attacks(sqNo , board_state.OccupancyMap)) & ( captureBoard[side] | pushMask[side]),NO_SQ , false);
  }

  // castle moves 
  //cout<<"CASTLE PERMISSIONS " <<board_state.castlePerm<<endl;
  if(side==WHITE){
    if((board_state.castlePerm & WKCA) && ((board_state.OccupancyMap & 0x0000000000000060ULL)==0 && (kingDangerSquares[side] & 0x0000000000000060ULL)==0) && ((num_checkers[side])==0)){
          moveList.push_back(4 |(6<<6) | (1<<15) | (1<<14) );
      
    }

    if ((board_state.castlePerm & WQCA) && ((board_state.OccupancyMap & 0x000000000000000eULL)==0 && (kingDangerSquares[side] & 0x000000000000000eULL )==0) && ((num_checkers[side])==0)){

          moveList.push_back(4 |(2<<6) | (1<<15) | (1<<14) );
          
      
    }
  }

  else{
    //cout<<"DEBUG CASTLE  "<<((board_state.OccupancyMap & 0x6000000000000000ULL)==0 && (kingDangerSquares[side] & 0x6000000000000000ULL)==0)<<endl;
    if((board_state.castlePerm & BKCA) && ((board_state.OccupancyMap & 0x6000000000000000ULL)==0 && (kingDangerSquares[side] & 0x6000000000000000ULL)==0) && ((num_checkers[side])==0)){

           moveList.push_back(60 |(62<<6) | (1<<15) | (1<<14) );
         
    }

    if((board_state.castlePerm & BQCA) && ((board_state.OccupancyMap & 0x0e00000000000000ULL)==0 && (kingDangerSquares[side] & 0x0e00000000000000ULL)==0) && ((num_checkers[side])==0)){
      {
          moveList.push_back(60 |(58<<6) | (1<<15) | (1<<14) );
          
      
    }
  }


  }

  return moveList.size();



}

 void MoveGen::update_enPasssantInfo(Board_State &board_state , int side){
   if(board_state.enPas>0 && ( pawn_attacks[1^side][board_state.enPas] | board_state.OccupancyMapColor[side])){
    
    enPassantCaptureSquare = 1ULL << (board_state.enPas+PAWN_PUSH_DIRECTION[1^side]) ; 
    attackBoards[side][0] |= (enPassantCaptureSquare);
    attackBoards[side][PAWN] |= (enPassantCaptureSquare);

  }


 };

 void MoveGen::BitmapToMoveList(vector<int>& moveList , int sq , U64 MoveMap ,int EnPassantSQ , bool Promotion ){

 // 00  00   000000  000000
 /// A move needs 16 bits to be stored
/// bit  0- 5: destination square (from 0 to 63)
/// bit  6-11: origin square (from 0 to 63)
/// bit 12-13: promotion piece type - 2 (from KNIGHT-2 to QUEEN-2)
/// bit 14-15: special move flag: promotion (1), en passant (2), castling (3)
///  EN-PASSANT bit is set only when a pawn can be captured

  if (Promotion){
    while(MoveMap){
    int to = pop_1st_bit(&MoveMap);
    int move = sq |(to<<6) | (1<<14) ;
    moveList.push_back(move);
    moveList.push_back(move | (1<<12));
    moveList.push_back(move | (1<<13));
    moveList.push_back(move | (1<<12) | (1<<13));
    
  }



  }

  if(EnPassantSQ!=NO_SQ){
    moveList.push_back(sq |(EnPassantSQ<<6) | (1<<15)  );
    return ; 
  }

  while(MoveMap){
    int to = pop_1st_bit(&MoveMap);
    moveList.push_back(sq |(to<<6)  );
    
  }




 }


void MoveGen:: GenerateMovesForPinned(vector<int>& MoveList , Board_State &board_state , int side){


U64 pinner = xrayRookAttacks(board_state.OccupancyMap,board_state.OccupancyMapColor[side] , board_state.KingSq[side]) & board_state.OccupancyMapRQ[1^side]  ;
while ( pinner ) {
   int sq  = pop_1st_bit(&pinner);
    U64 pinnedMap = rectlookup[sq][board_state.KingSq[side]] & board_state.OccupancyMapColor[side];
    
   pinnedPiecesMap[side] |= pinnedMap;
   int pinnedSq = pop_1st_bit(&pinnedMap);
   switch (board_state.piecePlacement[pinnedSq].pieceOccupying.pieceType) {
    case bB:
    case wB: 

    BitmapToMoveList(MoveList,pinnedSq , rectlookup[sq][board_state.KingSq[side]] & (get_bishop_attacks(pinnedSq , board_state.OccupancyMap) & ( captureBoard[side] | pushMask[side])),NO_SQ , false);
    break;


    case wP:
    case bP:
    BitmapToMoveList(MoveList,pinnedSq , rectlookup[sq][board_state.KingSq[side]] & ((pawn_attacks[side][pinnedSq] & captureBoard [side]) | (get_pawn_moves(pinnedSq, side, board_state.OccupancyMap ) & pushMask[side])),NO_SQ , false);
    break;


    case wR:
    case bR:
    BitmapToMoveList(MoveList,pinnedSq , rectlookup[sq][board_state.KingSq[side]] & (get_rook_attacks(pinnedSq , board_state.OccupancyMap) & ( captureBoard[side] | pushMask[side])),NO_SQ, false);
    break;

    case wQ:
    case bQ:
    BitmapToMoveList(MoveList,pinnedSq , rectlookup[sq][board_state.KingSq[side]] & ((get_bishop_attacks(pinnedSq , board_state.OccupancyMap) | get_rook_attacks(pinnedSq, board_state.OccupancyMap)) & ( captureBoard[side] | pushMask[side])),NO_SQ , false);
    break;

    default:
    
    break;
   }
}
pinner = xrayBishopAttacks(board_state.OccupancyMap,board_state.OccupancyMapColor[side] , board_state.KingSq[side]) & board_state.OccupancyMapBQ[1^side];
while ( pinner ) {


    int sq  = pop_1st_bit(&pinner);
    U64 pinnedMap = rectlookup[sq][board_state.KingSq[side]] & board_state.OccupancyMapColor[side];
    
   pinnedPiecesMap[side] |= pinnedMap;
   int pinnedSq = pop_1st_bit(&pinnedMap);
   switch (board_state.piecePlacement[pinnedSq].pieceOccupying.pieceType) {
    case bB:
    case wB: 

    BitmapToMoveList(MoveList,pinnedSq , rectlookup[sq][board_state.KingSq[side]] & (get_bishop_attacks(pinnedSq , board_state.OccupancyMap) & ( captureBoard[side] | pushMask[side])),NO_SQ , false);
    break;


    case wP:
    case bP:

    
    BitmapToMoveList(MoveList,pinnedSq , (rectlookup[sq][board_state.KingSq[side]] & (    (pawn_attacks[side][pinnedSq] & captureBoard [side]) |   (get_pawn_moves(pinnedSq, side, board_state.OccupancyMap ) & pushMask[side])  )  ) ,NO_SQ , false);
    break;


    case wR:
    case bR:
    BitmapToMoveList(MoveList,pinnedSq , rectlookup[sq][board_state.KingSq[side]] & (get_rook_attacks(pinnedSq , board_state.OccupancyMap) & ( captureBoard[side] | pushMask[side])),NO_SQ, false);
    break;

    case wQ:
    case bQ:
    BitmapToMoveList(MoveList,pinnedSq , rectlookup[sq][board_state.KingSq[side]] & ( (get_bishop_attacks(pinnedSq , board_state.OccupancyMap) | get_rook_attacks(pinnedSq, board_state.OccupancyMap)) & ( captureBoard[side] | pushMask[side])),NO_SQ , false);
    break;

    default:
    
    break;
   }


}



}


bool MoveGen::isSqAttacked(Board_State &board_state , int sq , int side , int EnPassanting = -1 ){

  if(EnPassanting!=-1){

    U64 fake_occupancy = (board_state.OccupancyMap|(1ULL<<board_state.enPas)) & (~ ((1ULL<<EnPassanting) | (enPassantCaptureSquare))) ; 

    return ((get_bishop_attacks(sq, fake_occupancy) & board_state.OccupancyMapBQ[1^side]) \ 
  | (get_rook_attacks(sq, fake_occupancy) & board_state.OccupancyMapRQ[1^side]) \
  | (pawn_attacks[side][sq] & (board_state.OccupancyMapP[1^side] &(~(enPassantCaptureSquare)) ) )  \
  | (knight_attacks[sq] & board_state.OccupancyMapN[1^side]));
  }
  // cout<<"OCCUPANCY MAP DEBUG : "<<endl;
  // print_bitboard(occupancyMap);
  return ((get_bishop_attacks(sq, board_state.OccupancyMap) & board_state.OccupancyMapBQ[1^side]) \ 
  | (get_rook_attacks(sq, board_state.OccupancyMap) & board_state.OccupancyMapRQ[1^side]) \
  | (pawn_attacks[side][sq] & board_state.OccupancyMapP[1^side])  \
  | (knight_attacks[sq] & board_state.OccupancyMapN[1^side]));
}



 // optimization to do :Remove Attack Boards for every single piece except the one for whole board 
 // optimize set bit clear bit functions with lookup tables of U64 

 // optimize every left shift by lookup tables 

 // remove looping through all pieces and making attack mask . Attack mask is used only for king 
 // danger squares and capture board . Both of which can be calculated by putting piece on square king and using occupancy 
 // remove square class and use int instead 

void MoveGen:: reset(){ 
    // cout<<"DEBUG : RESET "<<sizeof(attackBoards)<<endl;
    std::fill( &attackBoards[0][0], &attackBoards[2][0]  , 0ULL );
    std::fill( kingDangerSquares, kingDangerSquares+2, 0ULL );
    
    std::fill( &captureBoard[0], &captureBoard[2], 0ULL );
    std::fill( &kingCheckingPieces[0], &kingCheckingPieces[2], 0ULL );
    std::fill( &pinnedPiecesMap[0], &pinnedPiecesMap[2], 0ULL );
    std::fill( &pushMask[0], &pushMask[2], ~0ULL );
    enPassantCaptureSquare = 0ULL;
    std::fill( &num_checkers[0], &num_checkers[2], 0 );


   
    }