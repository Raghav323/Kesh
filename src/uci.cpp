#include "../include/defs.hpp"
#include "../include/Search.hpp"






void parseGo(const std::string& s, Search* chessSearch) {
    int depth = -1, movestogo = 30, movetime = -1;
    int time = -1, inc = 0;
    // cout<<"DEBUG"<<endl;
    chessSearch->resetSearch();    
        // cout<<"DEBUG2"<<endl;


    size_t pos = 0;

   

    if ((pos = s.find("binc")) != std::string::npos && chessSearch->moveMaker.board_state.side == BLACK) {
        inc = std::stoi(s.substr(pos + 5));
    }

    if ((pos = s.find("winc")) != std::string::npos && chessSearch->moveMaker.board_state.side == WHITE) {
        inc = std::stoi(s.substr(pos + 5));
    }

    if ((pos = s.find("wtime")) != std::string::npos && chessSearch->moveMaker.board_state.side == WHITE) {
        time = std::stoi(s.substr(pos + 6));
    }

    if ((pos = s.find("btime")) != std::string::npos && chessSearch->moveMaker.board_state.side == BLACK) {
        time = std::stoi(s.substr(pos + 6));
    }

    if ((pos = s.find("movestogo")) != std::string::npos) {
        movestogo = std::stoi(s.substr(pos + 10));
    }

    if ((pos = s.find("movetime")) != std::string::npos) {
        movetime = std::stoi(s.substr(pos + 9));
    }

    if ((pos = s.find("depth")) != std::string::npos) {
        depth = std::stoi(s.substr(pos + 6));
    }

    if (movetime != -1) {
        time = movetime;
        movestogo = 1;
    }

    // cout<<"hi"<<endl;
    chessSearch->starttime = std::chrono::system_clock::now();
    chessSearch->depth = depth;

    if (time != -1) {
        chessSearch->timeset = true;
        time /= movestogo;
        time -= 50;
        chessSearch->stoptime = chessSearch->starttime + std::chrono::milliseconds(time + inc);
    }

    if (depth == -1) {
        chessSearch->depth = MAX_DEPTH;
    }

    // cout<<"DEBUG :"<<"BTIME IS : "<<time<<endl;

    

    /*std::cout  <<"time: " << time
              <<" start: " << chessSearch->starttime.time_since_epoch().count()
              << " stop: " << chessSearch->stoptime.time_since_epoch().count()
              << " depth: " << chessSearch->depth << " timeset: " << chessSearch->timeset << std::endl;*/

    //  Search chessSeach(START_POS);
    // chessSearch.depth=2;
    chessSearch->searchPos();
    
}


void parsePosition(string s , Search *chessSearch){

    int index = s.find("moves");

      if (index == string::npos)
        index = s.length();


    if(s.substr(9,8)=="startpos"){
        // cout<<"HI"<<endl;
        chessSearch->moveMaker.board_state =   Board_State(START_POS);
    }
    else{
        if (s.substr(9,3)!="fen"){
        chessSearch->moveMaker.board_state =   Board_State(START_POS);
        // we will need to init search as otherwise pvtable is not getting cleared 
        // solution is to add a clear function in resetSearch and call that i guess

        }
        else{
                    chessSearch->moveMaker.board_state =   Board_State(s.substr(13,index-13));

          

           
        }
    }
    if (index != s.length()) {
        s = s.substr(index + 6);
        vector<int> moves;
        chessSearch->moveMaker.parse_moves_string(moves, s);
        for (auto move : moves) {
            chessSearch->moveMaker.MakeMove(move);
            // chessSearch->moveMaker.board_state.ply++;
            chessSearch->moveMaker.board_state.registerMove();
        }
    }

    chessSearch->moveMaker.board_state.printBoard();
};

void uci_loop(){
        flush(cout);
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string input ;
        cout<<"id name "<<NAME<<endl;
        cout<<"id author Raghav"<<endl;
        cout<<"uciok"<<endl;

        Search *chessSearch = new Search(START_POS);
        while(true){
            flush(cout);
            getline(cin,input);

            
            


            if(input=="" || input=="\n"){
                continue;
            }

            if(input.substr(0,7)=="isready"){
                cout<<"readyok"<<endl;
            }

            else if(input.substr(0,8)=="position"){
                parsePosition(input,chessSearch);
            }

            else if(input.substr(0,10)=="ucinewgame"){
                parsePosition("position startpos",chessSearch);
            }

            else if(input.substr(0,2)=="go"){
                parseGo(input,chessSearch);
            }

            else if(input.substr(0,4)=="quit"){
                chessSearch->quit=true;
                break;
            }

            else if (input.substr(0,3)=="uci"){
                cout<<"id name "<<NAME<<endl;
                cout<<"id author Raghav"<<endl;
                cout<<"uciok"<<endl;
            }

            else if(input.substr(0,5)=="perft"){
                cout<<endl<<chessSearch->perft(input[6]-'0',true)<<endl;
            }
            

            if(chessSearch!=nullptr && chessSearch->quit){
                chessSearch->quit=true;
                break;
            }

            // cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }

        chessSearch->pvTable.clear();
}