#include "../include/Search.hpp"
#include "../include/defs.hpp"
#include "../include/evaluate.hpp"
#include <climits>


#define MATE 29000

Search::Search(string FEN , int depth) : moveMaker(FEN), movegen() {

  
  this->depth=depth;
  // cout << endl;
  // cout << "Search created" << endl;
  // cout << "---------------------------------" << endl;
}

int Search::get_pv_line(){

  cout<<"PV LINE : ";
while (pvTable.find(moveMaker.board_state.stateKey)!=pvTable.end()){
    
    int move = pvTable[moveMaker.board_state.stateKey];
    print_move(move);
    cout<<" ";
    moveMaker.MakeMove(move);
    moveMaker.board_state.registerMove();
    
    
}cout<<endl;

while(moveMaker.board_state.ply>0){
  
    moveMaker.UndoMove();
    moveMaker.board_state.registerUndoMove();
}

return pvTable[moveMaker.board_state.stateKey];

}

U64 Search::perft(int depth, bool root) {

  int i;
  U64 cnt = 0;
  U64 nodes = 0;
  vector<int> moveList;
  std::chrono::time_point<std::chrono::system_clock> start = chrono::system_clock::now();
  movegen.generate_moves(moveList, moveMaker.board_state,
                         moveMaker.board_state.side);
  // cout<<"DEBUG : "<<n_moves<<endl;

  if (depth == 1) {
    if (root) {
      for (int i = 0; i < moveList.size(); i++) {
        print_move(moveList[i]);
        cout << " " << 1 << endl;
      }
      cout << endl << endl;
    }
    return (U64)moveList.size();
  }

  for (i = 0; i < moveList.size(); i++) {
   // Board_State B = moveMaker.board_state;
     moveMaker.MakeMove(moveList[i]);
    moveMaker.board_state.registerMove();

    cnt = perft(depth - 1, false);

    nodes += cnt;

   // moveMaker.board_state=B;
    moveMaker.UndoMove();
    moveMaker.board_state.registerUndoMove();

    // cout<<"AFTER UNDO SIDE : "<<moveMaker.board_state.side<<endl;

    if (root) {
      print_move(moveList[i]);
      cout << " " << cnt << endl;
    }
  }

  // if (root) {
  //   std::chrono::duration<double> elapsed_seconds =
  //       (chrono::system_clock::now()) - start;
  //   cout << "Perft Complete :- Nodes Visited : " << nodes
  //        << " Time Elapsed: " << elapsed_seconds.count() << "s Depth: " << depth
  //        << endl
  //        << endl;
  // }
  return nodes;
}

void Search::resetSearch() {
  pvTable.clear();
  pvTable.reserve(130000);
  moveMaker.board_state.ply=0;
  nodes=0;
  starttime = chrono::system_clock::now();
  stopped=0;
  fh=0;
  fhf=0;

};

void Search::checkUp(){
  //check if time up 
}

void Search::searchPos(){
  resetSearch();
  int bestScore = INT_MIN;
  int bestmove = 0;


  for(int d=1;d<=depth;d++){
    cout<<"--------------------------------------------------------------"<<endl;
    bestScore = AlphaBeta(-2147483647,2147483647,d);

    // out of time ?? 


    bestmove=get_pv_line();
    cout<<"INFO score  "<<bestScore<<" bestmove "<< bestmove<<" depth "<<d+1<<" nodes "<<nodes<<endl;
    
    if(fh!=0)
      cout<<"Ordering : "<<(fhf/fh) <<endl;
     cout<<"--------------------------------------------------------------"<<endl;
  }
}

int Search::AlphaBeta(int alpha , int beta , int depth){

  // cout<<"current depth in recursive function is : "<<depth<<endl;
  if(depth==0){

   
    nodes++;
    return evalPos(moveMaker.board_state);
  }

  nodes++;
  if(moveMaker.board_state.ply>MAX_DEPTH-1){
    return evalPos(moveMaker.board_state);
  }

  if(moveMaker.board_state.fiftyMove>=100 ){
    // cout<<"DEBUG 0"<<endl;
    return 0;
  }

 vector<int> moveList;
 int score = -2147483647;
 int bestMove = 0;
  int oldAlpha = alpha;
movegen.generate_moves(moveList, moveMaker.board_state,
                         moveMaker.board_state.side);

// cout<<"Depth :  "<<depth<< "Number of moves generated : "<<moveList.size()<<endl;
for (int i = 0; i < moveList.size(); i++) {
    // Board_State B = moveMaker.board_state;
     moveMaker.MakeMove(moveList[i]);
      score =  moveMaker.board_state.isRepetition() ? 0 : -AlphaBeta(-beta,-alpha,depth-1) ;

    moveMaker.board_state.registerMove();




    // moveMaker.board_state.printBoard();
    // cout<<"Score : "<<score<<endl<<endl;

    // moveMaker.board_state=B;
    moveMaker.UndoMove();
    moveMaker.board_state.registerUndoMove();

    if(score>alpha){
    if(score>=beta){
      // cout<<"Depth :  "<<depth<<"Alpha value : "<<alpha<<" Score : "<<score<<endl;
      // cout<<"Depth :  "<<depth<<"Beta value : "<<beta<<" Score : "<<score<<endl;
      if(i==0){
        fhf++;
      }
      fh++;
      return beta;
    }

    //cout<<"Alpha changed from : "<<alpha<<" to : "<<score<<endl;
    alpha = score;

    bestMove = moveList[i];
    }
}

if(moveList.size()==0){
  if(movegen.num_checkers[moveMaker.board_state.side]){
    cout<<"DEBUG 2"<<endl;
    return -MATE + moveMaker.board_state.ply;
  }else{
    cout<<"DEBUG 3"<<endl;
    return 0;
  }
}

if(alpha!=oldAlpha){
  // cout<<"HIIIIIIIIII"<<endl;
  pvTable[moveMaker.board_state.stateKey] = bestMove;
}

return alpha;



}