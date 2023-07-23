#include "../include/defs.hpp"
#include "../include/Engine.hpp"


Engine::Engine(string FEN){
moveMaker = MoveMaker(FEN);
movegen=MoveGen();
// cout<<"Engine initialized side : "<<moveMaker.board_state.side<<endl;
}


U64 Engine::perft(int depth , bool root){



   int i;
  U64 cnt=0;
  U64 nodes = 0;
  vector<int> moveList;
  movegen.generate_moves(moveList,moveMaker.board_state, moveMaker.board_state.side);
  //cout<<"DEBUG : "<<n_moves<<endl;

  if (depth == 1){ 
    if(root){
    for(int i=0;i<moveList.size();i++){
        print_move(moveList[i]);
        cout<<" "<<1<<endl;
    }
    }
    return (U64) moveList.size();
  }

  for (i = 0; i < moveList.size(); i++) {
    Board_State B = moveMaker.board_state;
    U64 undo = moveMaker.MakeMove(moveList[i]);

    
    cnt = perft(depth - 1,false);
    
    nodes+=cnt;
    
    // moveMaker.board_state=B;
    moveMaker.UndoMove(undo);

    //cout<<"AFTER UNDO SIDE : "<<moveMaker.board_state.side<<endl;

    if(root){
    print_move(moveList[i]);
    cout<<" "<<cnt<<endl;
    }
  }
  return nodes;

}

