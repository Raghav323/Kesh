#include "../include/Search.hpp"
#include "../include/defs.hpp"
#include "../include/evaluate.hpp"
#include "../include/misc.hpp"

#define MATE 29000

Search::Search(string FEN)
    : moveMaker(FEN), movegen(), moveOrderer(&moveMaker.board_state) {
      resetSearch();
        pvTable.clear();
        pvTable.reserve(PVTABLESIZE);

  // this->depth = depth;
  // cout << endl;
  // cout << "Search created" << endl;
  // cout << "---------------------------------" << endl;
}

int Search::get_pv_line(int pvDepth) {

  cout << " pv ";
  int count =0;
  while (pvTable.find(moveMaker.board_state.stateKey) != pvTable.end() && count<pvDepth) {

    int move = pvTable[moveMaker.board_state.stateKey];
    // if(move==0){
    //   break;
    // }
    print_move(move);
    cout << " ";
    moveMaker.MakeMove(move);
    moveMaker.board_state.ply++;

    moveMaker.board_state.registerMove();

    count++;
    // cout<< "STATE KEY : "<<moveMaker.board_state.stateKey<<endl;
    // cout<<"PLY : "<<moveMaker.board_state.ply<<endl;

  }
  cout << endl;

  while (moveMaker.board_state.ply > 0) {
    moveMaker.board_state.registerUndoMove();
    moveMaker.UndoMove();
    moveMaker.board_state.ply--;

  }

  return pvTable[moveMaker.board_state.stateKey];
}

U64 Search::perft(int depth, bool root) {

  int i;
  U64 cnt = 0;
  U64 nodes = 0;
  vector<int> moveList;
  std::chrono::time_point<std::chrono::system_clock> start =
      chrono::system_clock::now();
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
    moveMaker.board_state.ply++;
    moveMaker.board_state.registerMove();

    cnt = perft(depth - 1, false);

    nodes += cnt;

    // moveMaker.board_state=B;
    moveMaker.board_state.registerUndoMove();
    moveMaker.UndoMove();
    moveMaker.board_state.ply--;


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
  //        << " Time Elapsed: " << elapsed_seconds.count() << "s Depth: " <<
  //        depth
  //        << endl
  //        << endl;
  // }
  return nodes;
}

void Search::resetSearch() {
  moveMaker.board_state.ply = 0;
  nodes = 0;
  starttime = chrono::system_clock::now();
  stopped = false;
  fh = 0;
  fhf = 0;
  timeset=false;
  quit=false;
  
};

void Search::checkUp() {
  // check if time up
  if(timeset && (chrono::system_clock::now() > stoptime)  ){
    stopped=true;
  }

   if (InputWaiting()) {
        stopped = true;
        std::string input;
        std::getline(std::cin, input);
        if (input.length() > 0) {
            if (input == "quit") {
                quit = true;
            }
        }
       // cin.ignore(numeric_limits<streamsize>::max(), '\n');

    }
}

void Search::searchPos() {
  // resetSearch();
  // moveMaker.board_state.ply = 0;

  moveOrderer = MoveOrderer(&moveMaker.board_state);
  if(pvTable.size()>PVTABLESIZE-1000){
    pvTable.clear();
    // pvTable.reserve(PVTABLESIZE);
    }
  // moveOrderer.reset();
 
  int bestScore = -INT_MAX;
  int bestmove = 0;

  for (int d = 1; d <= depth; d++) {
    
    bestScore = AlphaBeta(-INT_MAX, INT_MAX, d);
    // cout<<"DEBUG 3"<<endl;
    if (stopped) {
      break;
    }

    
    cout << "info score cp " << bestScore << " depth "
         << d  << " nodes " << nodes << " time " << (chrono::duration_cast<chrono::milliseconds>((chrono::system_clock::now() - starttime) )).count();
    bestmove = get_pv_line(d);

    // if (fh != 0)
    //   cout << "Ordering : " << (fhf / fh) << endl;
    
  }

  cout<<"bestmove ";print_move(bestmove);cout<<endl;
}

int Search::Quiescense(int alpha, int beta) {
      // cout<<"DEBUGGGG"<<endl;

  if((nodes & 2047)==0){
    checkUp();
  }

  nodes++; 

  
  if (moveMaker.board_state.ply > MAX_DEPTH - 1) {
    return evalPos(moveMaker.board_state);
  }

  int score = evalPos(moveMaker.board_state);

  if (score >= beta) {
    return beta;
  }

  if (score > alpha) {
    alpha = score;
  }

  int bestMove = 0;
  int oldAlpha = alpha;
  score = -INT_MAX;
  vector<int> moveList;
  movegen.generate_capture_moves(moveList, moveMaker.board_state,
                                 moveMaker.board_state.side);
  
  pvTable.find(moveMaker.board_state.stateKey)!=pvTable.end() ? moveOrderer.sortMoves(moveList, moveMaker.board_state.ply,pvTable.at(moveMaker.board_state.stateKey)) : moveOrderer.sortMoves(moveList, moveMaker.board_state.ply , 0);
  
  // cout<<"INSIDE QUIESCENCE "<<endl;
  // print_Move_list(moveList);cout<<endl;
  for (int i = 0; i < moveList.size(); i++) {
    // Board_State B = moveMaker.board_state;
    moveMaker.MakeMove(moveList[i]);
    moveMaker.board_state.ply++;
    moveMaker.board_state.registerMove();

    score = -Quiescense(-beta, -alpha);


    // moveMaker.board_state.printBoard();
    // cout<<"Score : "<<score<<endl<<endl;

    // moveMaker.board_state=B;
    moveMaker.board_state.registerUndoMove();

    moveMaker.UndoMove();
        moveMaker.board_state.ply--;


    if(stopped){
      return 0;
    }

    if (score > alpha) {
      if (score >= beta) {
        // cout<<"Depth :  "<<depth<<"Alpha value : "<<alpha<<" Score :
        // "<<score<<endl; cout<<"Depth :  "<<depth<<"Beta value : "<<beta<<"
        // Score : "<<score<<endl;
        // if (i == 0) {
        //   // fhf++;
        // }
        // fh++;
        return beta;
      }

      // cout<<"Alpha changed from : "<<alpha<<" to : "<<score<<endl;
      alpha = score;

      bestMove = moveList[i];
    }
  }

  if (alpha != oldAlpha ) {
   //  cout<<"TABLE SIZE IS :  "<<pvTable.size() <<endl;
    pvTable[moveMaker.board_state.stateKey] = bestMove;
  }

  return alpha;
}





int Search::AlphaBeta(int alpha, int beta, int depth) {
  nodes++;
  
  if (moveMaker.board_state.ply > MAX_DEPTH - 1) {
    return evalPos(moveMaker.board_state);
  }

  if (moveMaker.board_state.fiftyMove >= 100) {
    // cout<<"DEBUG 0"<<endl;
    return 0;
  }
  if (depth == 0) {

    
    //return evalPos(moveMaker.board_state);
    return Quiescense(alpha, beta);
  }

  if((nodes & 2047)==0){
    checkUp();
    
  }

  
  
  vector<int> moveList;
  int score = -INT_MAX;
  int bestMove = 0;
  int oldAlpha = alpha;
  movegen.generate_moves(moveList, moveMaker.board_state,
                         moveMaker.board_state.side);


  //moveOrderer.heapifyMoves(moveList, moveMaker.board_state.ply,pvTable[moveMaker.board_state.stateKey]);

  pvTable.find(moveMaker.board_state.stateKey)!=pvTable.end() ? moveOrderer.sortMoves(moveList, moveMaker.board_state.ply,pvTable.at(moveMaker.board_state.stateKey)) : moveOrderer.sortMoves(moveList, moveMaker.board_state.ply , 0);



  // print_Move_list(moveList);


  for(int i=0;i<moveList.size();i++){
    int currentMove = moveList[i];
    // int currentMove = moveList.back();moveList.pop_back();
    // int currentMove = moveOrderer.popMove(moveList, moveMaker.board_state.ply,pvTable[moveMaker.board_state.stateKey]);
    moveMaker.MakeMove(currentMove);
    moveMaker.board_state.ply++;
    if( moveMaker.board_state.isRepetition()){
      // cout<<("IS A REPETITION !!!")<<endl;
        //cout<<"Current Move : ";print_move(currentMove);cout<<" Depth : "<<depth<<endl;

      score =0;
      moveMaker.board_state.registerMove();
    }
    else{
      moveMaker.board_state.registerMove();
      score = -AlphaBeta(-beta, -alpha, depth - 1);
      
    }
   

    
    moveMaker.board_state.registerUndoMove();
    moveMaker.UndoMove();
    moveMaker.board_state.ply--;

    if(stopped){
      return 0;
    }

    if (score > alpha) {

      if (score >= beta) {

        // if (i == 0) {
        //   // fhf++;
        // }
        // fh++;
        moveOrderer.registerBetaCutter(currentMove, moveMaker.board_state.ply);
        return beta;
      }
      bestMove = currentMove;
              // cout<<"DEBUGGGG"<<endl;
      //cout<<"BEST SCORE : "<<score<<" Depth : "<<depth<<" BEST MOVE :";print_move(bestMove);cout<<endl;
        

      moveOrderer.registerAlphaImprover(bestMove, depth, score - alpha);
              // cout<<"DEBUGGGG2"<<endl;

      alpha = score;
    }
 
  }

  if (moveList.size() == 0) {
    if (movegen.num_checkers[moveMaker.board_state.side]) {
      // cout << "DEBUG 2" << endl;
      cout<<"MATE IN "<<moveMaker.board_state.ply<<" MOVES"<<endl;
      moveMaker.board_state.printBoard();
      return -MATE + moveMaker.board_state.ply;
    } else {
      // cout << "DEBUG 3" << endl;
      return 0;
    }
  }

  if (alpha != oldAlpha ) {
    // cout<<"HIIIIIIIIII"<<endl;
    // cout<<"TABLE SIZE IS :  "<<pvTable.size() <<endl;
    pvTable[moveMaker.board_state.stateKey] = bestMove;
  }

  return alpha;
}