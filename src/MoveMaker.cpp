#include "../include/MoveMaker.hpp"
#include "../include/defs.hpp"
#include <stack>


MoveMaker::MoveMaker(string FEN) :board_state(FEN){
    // how to initialize using new in c++

    
    
    
}






void MoveMaker::MakeMove(int move){

   

int from = move & 0x3F;
int to = (move >> 6) & 0x3F;

int side = board_state.side;
U64 undoMove = move | (board_state.fiftyMove << 16) | (board_state.castlePerm << 24) | ((U64)(board_state.enPas) << 28) | ((U64)board_state.piecePlacement[to].pieceOccupying.pieceType << 34) ;

if(((move>>14) & 0x3)==2){
    Square sq = board_state.piecePlacement[(board_state.enPas+PAWN_PUSH_DIRECTION[1^side])];
    board_state.updatePieceBoard( sq ,sq.pieceOccupying , 0 );
      
    
    
   
}

// cout<<"MAKING MOVE : "<<endl;

// cout<<"FROM SQ : "<< (move & 0x3f)<<" TO SQ : "<<((move>>6) & 0x3f)<<" PROMOTION : "<<((move>>12) & 0x3)<<" SPECIAL : "<<((move>>14) & 0x3)<<endl;
// cout<<"\n";

if(((move>>14) & 0x3)==3){
    //cout<<"DEBUG : : "<<to<<endl;
    switch (to) {
    case 2: //WKQC
        //cout<<"HIII"<<endl;
        board_state.MovePiece(0, 3);
        break;
    case 6: //WKSC
        
        board_state.MovePiece(7, 5);
        break;

    case 58: //BKQC
        
        board_state.MovePiece(56, 59);
        break;

    case 62: //BKSC
        
        board_state.MovePiece(63, 61);
        break;

    }

}

// // an undo move will be a 37 bit integer with following format 


// //  0000 0000 0000 0000 0000 
// // first 16 bits for storing move 
// // next 8 for storing fifty moves counter
// // next 4 for storing castle permissions
// next 5 for storing enpassant square
// next 4 for storing captured piece


// // [0000] [000000] [0000] [0000 0000] [0000 0000 0000 0000]

if(board_state.enPas!=NO_SQ){
    board_state.hasher.hashPiece(NO_PIECE, board_state.enPas);
}
board_state.hasher.hashCastle(board_state.castlePerm);
board_state.castlePerm &= CastlePerm[from];
board_state.castlePerm &= CastlePerm[to];
board_state.hasher.hashCastle(board_state.castlePerm);
board_state.enPas = NO_SQ;

board_state.hisPly++;


board_state.fiftyMove++;

if (board_state.piecePlacement[to].pieceOccupying!=NO_PIECE){
    board_state.fiftyMove = 0;
    board_state.updatePieceBoard(board_state.piecePlacement[to], board_state.piecePlacement[to].pieceOccupying, 0);
}

if(board_state.piecePlacement[from].pieceOccupying.pieceType == wP || board_state.piecePlacement[from].pieceOccupying.pieceType == bP){
    board_state.fiftyMove = 0;
    
    if((from - to) == 16 || (from - to) == -16){
        board_state.enPas = (from + to)/2;
    }
    board_state.hasher.hashPiece(NO_PIECE, board_state.enPas);

}  

if(((move>>14) & 0x3)==1){
    board_state.updatePieceBoard(board_state.piecePlacement[from], board_state.piecePlacement[from].pieceOccupying , 0);
    board_state.updatePieceBoard(board_state.piecePlacement[to], Piece((PieceTypeWithoutColor) (((move>>12) & 0x3) + 2) , (color)board_state.side , to), 1);
    
    board_state.side^=1;
    board_state.hasher.hashSide();
    board_state.undoStack.push(undoMove);
    return ;
}

 board_state.MovePiece(from, to); 
 
 // cout<<"SIDE MAKING MOVE IS "<<board_state.side<<endl;
 board_state.side^=1;
board_state.hasher.hashSide();

   

  board_state.undoStack.push(undoMove);
}

void MoveMaker::UndoMove(){

    if(board_state.undoStack.empty()){
        cout<<"ERROR : CANNOT UNDO FROM START POSITION !"<<endl<<endl;
        return ;
    }
    U64 move = board_state.undoStack.top();board_state.undoStack.pop();
    int from = move & 0x3F;
    int to = (move >> 6) & 0x3F;

    int side = board_state.side;

    board_state.history.erase(board_state.stateKey);


    if(((move>>14) & 0x3)==3){
        switch (to) {
        case 2: //WKQC
            board_state.MovePiece(3, 0);
            break;
        case 6: //WKSC
            board_state.MovePiece(5, 7);
            break;

        case 58: //BKQC
            board_state.MovePiece(59, 56);
            break;

        case 62: //BKSC
            board_state.MovePiece(61, 63);
            break;

        }

    }
    if(board_state.enPas!=NO_SQ){
        board_state.hasher.hashPiece(NO_PIECE, board_state.enPas);
    }
    board_state.hasher.hashCastle(board_state.castlePerm);
    board_state.castlePerm = (move >> 24) & 0xF;
    board_state.hasher.hashCastle(board_state.castlePerm);
    board_state.fiftyMove = (move >> 16) & 0xFF;
    board_state.enPas = ((move >> 28) & 0x3F) ;
    int capturedPiece = (move >> 34) & 0xF;
    board_state.hisPly--;

    board_state.fullMoves=board_state.ply/2;

    if(board_state.enPas!=NO_SQ){
        board_state.hasher.hashPiece(NO_PIECE, board_state.enPas);
    }

    if(((move>>14) & 0x3)==1){
        color pawnC= board_state.piecePlacement[to].pieceOccupying.get_piece_color();

        board_state.updatePieceBoard(board_state.piecePlacement[to], board_state.piecePlacement[to].pieceOccupying , 0);
        board_state.updatePieceBoard(board_state.piecePlacement[from], Piece(PAWN , pawnC , from), 1);
        if (capturedPiece!=NO_PIECE){
        board_state.updatePieceBoard(board_state.piecePlacement[to], Piece((PieceType) capturedPiece , to), 1);
        }
        board_state.side^=1;
        board_state.hasher.hashSide();
        return ;
    }

    board_state.MovePiece(to, from);

    if (capturedPiece!=NO_PIECE){
        board_state.updatePieceBoard(board_state.piecePlacement[to], Piece((PieceType) capturedPiece , to), 1);
    }

    // if (board_state.piecePlacement[from].pieceOccupying!=NO_PIECE){
    //     board_state.updatePieceBoard(board_state.piecePlacement[from], board_state.piecePlacement[from].pieceOccupying, 0);
    // }

    // if(board_state.piecePlacement[to].pieceOccupying.pieceType == wP || board_state.piecePlacement[to].pieceOccupying.pieceType == bP){
    //     if((from - to) == 16 || (from - to) == -16){
    //         board_state.updatePieceBoard(board_state.piecePlacement[(from + to)/2], board_state.piecePlacement[(from + to)/2].pieceOccupying, 0);
    //     }
    // }  

    // cout<<"DEBUG : "<<side<<endl;
    // cout<<"ENPASSANT SQUARE IS AFTER UNDO :  "<<board_state.enPas<<endl;
    if(((move>>14) & 0x3)==2){
        board_state.updatePieceBoard(board_state.piecePlacement[(board_state.enPas+PAWN_PUSH_DIRECTION[side])] , Piece(PAWN,(color)side,(board_state.enPas+PAWN_PUSH_DIRECTION[side])  ) , 1 );
    }



board_state.side^=1;
board_state.hasher.hashSide();





}

void MoveMaker::parse_moves_string(vector<int> & MoveList , string moves_string=""  ) {
   
  int i = 0;
  while (i < moves_string.length()) {
    if (moves_string[i] != ' ') {
    //cout<<"I IS "<<i<<"CHAR IS"<<moves_string[i]<<endl;

      int from = (moves_string[i] - 'a') + (moves_string[i + 1] - '1') * 8;
      int to = (moves_string[i + 2] - 'a') + (moves_string[i + 3] - '1') * 8;
      i += 4;
      if ((i<moves_string.length())&&(moves_string[i] == 'Q' || moves_string[i] == 'N' || moves_string[i] == 'R' || moves_string[i] == 'B' || moves_string[i] == 'q' || moves_string[i] == 'n' || moves_string[i] == 'r' || moves_string[i] == 'b')) {
        //cout<<"HERE ! "<<endl;
        MoveList.push_back(from | (to << 6) | (notation[moves_string[i]]<<12) | (1 << 14));
       
        
        
        
        i += 1;
      }

      else {
        int move = from + (to << 6);
        if(board_state.enPas!=NO_SQ){
            if((board_state.piecePlacement[from].pieceOccupying.pieceType==wP |
            board_state.piecePlacement[from].pieceOccupying.pieceType==bP
            ) && to==board_state.enPas){
                move|=2<<14;
            }
        }

        if(board_state.piecePlacement[from].pieceOccupying.pieceType==wK | board_state.piecePlacement[from].pieceOccupying.pieceType==bK){
            if((from-to==2) || (from-to==-2)){
                move|=3<<14;
            }
           
        }
        MoveList.push_back(move);
        
        
      }

    } else {
      i++;
    }
  }
}