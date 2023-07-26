#include "../include/defs.hpp"
#include "../include/Engine.hpp"


Engine::Engine(string FEN) :moveMaker(FEN) , movegen(){

resetEngine();
cout<<endl;
cout << "Engine created" << endl;
cout<<"---------------------------------"<<endl;
}


U64 Engine::perft(int depth , bool root){



   int i;
  U64 cnt=0;
  U64 nodes = 0;
  vector<int> moveList;
  auto start = chrono::system_clock::now();
  movegen.generate_moves(moveList,moveMaker.board_state, moveMaker.board_state.side);
  //cout<<"DEBUG : "<<n_moves<<endl;

  if (depth == 1){ 
    if(root){
    for(int i=0;i<moveList.size();i++){
        print_move(moveList[i]);
        cout<<" "<<1<<endl;
    }cout<<endl<<endl;
    }
    return (U64) moveList.size();
  }

  for (i = 0; i < moveList.size(); i++) {
    //Board_State B = moveMaker.board_state;
    U64 undo = moveMaker.MakeMove(moveList[i]);

    
    cnt = perft(depth - 1,false);
    
    nodes+=cnt;
    
    //moveMaker.board_state=B;
    moveMaker.UndoMove(undo);

    //cout<<"AFTER UNDO SIDE : "<<moveMaker.board_state.side<<endl;

    if(root){
    print_move(moveList[i]);
    cout<<" "<<cnt<<endl;
    }
  }

  if(root){
    std::chrono::duration<double> elapsed_seconds = (chrono::system_clock::now())-start;
  cout<<"Perft Complete :- Nodes Visited : "<<nodes<<" Time Elapsed: "\
  <<elapsed_seconds.count()<<"s Depth: "<<depth<<endl<<endl;
  }
  return nodes;

  

}


void Engine::resetEngine(){
  pvTable.clear();
  pvTable.reserve(130000);
};