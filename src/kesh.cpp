#include "../include/Board.hpp"
#include "../include/MoveMaker.hpp"
#include "../include/Piece.hpp"
#include "../include/Search.hpp"
#include "../include/Square.hpp"
#include "../include/defs.hpp"
#include "../include/movegen.hpp"




#define TEST_FEN "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define TEST_FEN_2 "4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1"

#define TEST_FEN_3 "5b2/3Rk3/8/8/4R3/8/8/4K3 w - - 0 1"

#define TEST_FEN_4 "4n3/3p1K2/2kn4/5q2/8/8/8/8 w - - 0 1"

#define TEST_FEN_5 "5R2/8/7K/4n3/7k/8/8/8 w - - 0 1"

#define TEST_FEN_6 "2r5/5b2/1k2N3/8/1PpP4/8/K7/8 b - b3 0 1"

#define TEST_FEN_7 "7K/8/8/2Pp4/8/8/3k4/8 w - d6 0 1"

#define TEST_FEN_8 "8/6Q1/1R3k2/4P3/8/8/1B1K4/8 b - - 0 1"

#define TEST_FEN_9 "4N3/6Q1/1R3k2/4P3/8/8/1B1K4/1B2r3 b - - 0 1"

#define TEST_FEN_10 "6b1/8/8/2k5/2pPp3/8/7K/B7 b - d3 0 1"

#define TEST_FEN_11 "8/8/8/4k1R1/4p3/8/7K/8 b - - 0 1"

#define TEST_FEN_12 "6Q1/4k3/5r2/1q6/8/5B1b/4N1N1/5K2 w - - 0 1"

#define TEST_FEN_13 "8/3p3r/6k1/2K5/8/3N4/8/6q1 w - - 0 1"

#define TEST_FEN_14 "8/4k3/7B/1N6/8/2Q4b/BQ2N1N1/5K2 w - - 0 1"

#define TEST_FEN_15 "5q2/3BP2K/1k6/8/3Pp3/8/7B/7Q b - d3 0 1"

#define TEST_FEN_16                                                            \
  "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

#define TEST_FEN_17 "5n2/5k2/3P1ppp/p2PpN2/2b3P1/6PP/P2B1K2/8 w - - 0 1"

#define TEST_FEN_18                                                            \
  "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1"

// AttackBoards --> KingDanger --> KingInfo --> CaptureBoard --> MoveList
int main(int argc, char *argv[]) {
  AllInit();
  // Board_State board = Board_State(TEST_FEN_15);

  // cout<<"Pieces Board  : "<<endl;
  // board.printBoard();

  // print_bitboard(board.OccupancyMapColor[0]);
  // MoveGen movegen;

  //     movegen.update_attack_boards(board ,0);
  //     movegen.update_attack_boards(board ,1);

  //     movegen.update_KingMovesInfo(board, 0);

  //     movegen.update_enPasssantInfo(board , 0);
  //     movegen.update_capture_board(board, 0);

  //     // print_bitboard(movegen.kingMoves[1] );

  //    cout<<"Attack Board  : "<<endl;
  //     print_bitboard(movegen.attackBoards[0][0] );

  //     cout<<"Capture  Board  : "<<endl;

  //     print_bitboard(movegen.captureBoard[0] );

  //     cout<<"Num checkers : "<<movegen.num_checkers[0]<<endl;

  //     cout<<"Check bitboard : ";
  //     print_bitboard(movegen.kingCheckingPieces[0]);cout<<endl;

  //     cout<<"Push Mask : "; print_bitboard(movegen.pushMask[0]);cout<<endl;

  //     cout<<"DEBUG : "<<endl;
  //     // print_bitboard(get_pawn_moves(54, 1, (1ULL)<<38));

  //     print_bitboard(xrayBishopAttacks(board.OccupancyMap,
  //     board.OccupancyMapColor[0], board.KingSq[0]));
  //     // cout<<"King Moves : ";
  //     print_bitboard(movegen.Moves[1][KING][0]);cout<<endl;

  //     cout<<"BQ BITBOARD : "<<endl;
  //     print_bitboard(board.OccupancyMapBQ[0]);

  //     cout<<"ALL PINNED PIECCE :  "<<endl;

  //     movegen.GenerateMovesForPinned(board , 0);

  //     print_bitboard(movegen.pinnedPiecesMap[0]);

  // movegen.generate_moves(board , board.side);

  // print_Move_list(movegen.moveList);

  // MoveMaker M(TEST_FEN_15);

  // U64 undo = M.MakeMove(movegen.moveList[8]);
  // M.board_state.printBoard();
  // cout<<endl;
  // M.UndoMove(undo);
  // M.board_state.printBoard();
  // cout<<endl;

  // movegen.generate_moves(M.board_state , M.board_state.side);
  // M.MakeMove(movegen.moveList[35]);
  // movegen.generate_moves(M.board_state , M.board_state.side);

  // print_Move_list(movegen.moveList);

  // for(auto move : movegen.moveList){
  //     M.MakeMove(move);
  //     M.board_state.printBoard();
  //     cout<<endl;
  //     // M.UnMakeMove(move);
  //     // M.board_state.printBoard();
  //     // cout<<endl;
  // }
  // Search chessSearch(START_POS);

  // U64 total = chessSearch.perft(2,true);
  // cout<<endl<<total<<endl;
  // return 0;

  // FOR PERFT TESTING ////////////////////
  // string moves = "";
  // string FEN = argv[1];
  // // cout<<argv[2]<<endl;
  // int depth = stoi(argv[2]);
  // if (argc > 3) {
  //   moves = argv[3];
  // }

  // Search chessSearch(FEN);

  // vector<int> movesVEC;
  // chessSearch.moveMaker.parse_moves_string(
  //     movesVEC, "d6d5 e3f4 f3d4 f4e3 d4c6 e3f4 c6d4 f4g5 d5e5 g5h6 d4e6 h6h5 e5f5 h5h6 e4f3 h6h7 f5f6 h7h8 f3c6 h8h7 c6a8 h7h8 a8d5 h8h7 f6f7 h7h8 f7g6 h8g8 d5c6 g8h8");

  // for (int move : movesVEC) {
  //   chessSearch.moveMaker.MakeMove(move);
  //   chessSearch.moveMaker.board_state.ply++;
  //   chessSearch.moveMaker.board_state.registerMove();
  // }
  // chessSearch.moveMaker.board_state.printBoard();
  // U64 total = chessSearch.perft(depth, true);
  // cout << endl << total << endl;
  // return 0;

  //////////////////////////////////////

  // Search chessSearch("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1P/PPPBBP2/1R2K2R
  // b Kkq - 0 2");
  // // chessSearch.moveMaker.parse_moves_string("g2g1r");
  // // chessSearch.moveMaker.board_state.printBoard();
  // cout<<endl;
  // U64 undo = chessSearch.moveMaker.MakeMove(24974);
  // chessSearch.moveMaker.board_state.printBoard();
  // cout<<endl;
  // chessSearch.moveMaker.UndoMove(undo);
  // chessSearch.moveMaker.board_state.printBoard();
  // cout<<endl;
  // U64 undo2 = chessSearch.moveMaker.MakeMove(29070);
  // chessSearch.moveMaker.board_state.printBoard();
  // cout<<endl;

  // chessSearch.moveMaker.parse_moves_string("a2a3");
  // chessSearch.moveMaker.board_state.printBoard();
  // cout<<endl;
  // chessSearch.moveMaker.parse_moves_string("a7a5");
  // chessSearch.moveMaker.board_state.printBoard();
  // cout<<endl;
  // // chessSearch.moveMaker.parse_moves_string("h2h3");
  // // chessSearch.moveMaker.board_state.printBoard();

  // chessSearch.perft(2, true);

  // MoveGen movegen;
  // vector<int> moveList;
  // movegen.generate_moves(moveList, chessSearch.moveMaker.board_state,
  // chessSearch.moveMaker.board_state.side);

  // // print_Move_list(moveList);
  // cout<<"NO OF MOVES FOR SIDE IN THIS POSITION BY MAKING MOVE AND MOVEGEN ARE
  // : "<<moveList.size()<<endl;
  // //
  // cout<<"_____________________________________________________________"<<endl;
  // MoveGen movegen2;
  // vector<int> moveList2;
  // Board_State ss =
  // Board_State(Board_State("rnbqkbnr/1ppppppp/8/8/p7/3P4/PPPKPPPP/RNBQ1BNR w
  // kq - 0 3")); movegen2.generate_moves(moveList2, ss, ss.side);
  // print_Move_list(moveList2);
  // cout<<"NO OF MOVES FOR SIDE IN THIS POSITION BY ONLY MOVEGEN ARE :
  // "<<moveList2.size()<<endl;
  // cout<<"_____________________________________________________________"<<endl;

  // cout<<endl;

  // MoveMaker M(TEST_FEN_15);
  // M.board_state.printBoard();
  // M.parse_moves_string("e4d3 e7f8Q d3d2");
  // M.board_state.printBoard();

  // string input;
  // Search chessSearch(TEST_FEN_18);

  // while (TRUE) {
  //   chessSearch.moveMaker.board_state.printBoard();

  //   cout << "Enter a move :  ";
  //   cin >> input;
  //   cout << endl;
  //   if (input == "q") {
  //     return 0;

  //   } else if (input == "t") {

  //       chessSearch.moveMaker.UndoMove();
  //       chessSearch.moveMaker.board_state.registerUndoMove();

  //   }
  //   else if(input=="pv"){
  //     chessSearch.get_pv_line();
  //   }

  //   else if (input.at(0) == 'p') {
  //     chessSearch.perft(1 + input.at(1) - '1', true);
  //   }

  //   else if(input.at(0)=='s'){
  //     chessSearch.depth = 1+input.at(1) - '1';
  //     chessSearch.starttime = chrono::system_clock::now();
  //     chessSearch.stoptime = chessSearch.starttime +
  //     chrono::milliseconds(200); chessSearch.searchPos();
  //   }

  //   else if(input=="c"){
  //     vector<int> moves ;
  //     chessSearch.movegen.generate_capture_moves(moves,
  //     chessSearch.moveMaker.board_state,
  //     chessSearch.moveMaker.board_state.side); for(auto move : moves){

  //       print_move(move);cout<<endl;
  //     }
  //     cout<<endl;
  //   }

  //   else {
  //      vector<int> moves ;
  //     chessSearch.moveMaker.parse_moves_string(moves , input);
  //     for(auto move : moves){

  //       chessSearch.moveMaker.MakeMove(move);
  //       chessSearch.moveMaker.board_state.registerMove();
  //       cout<<endl;
  //     }

  //   }

  //   cin.ignore(INT_MAX, '\n');
  // }
uci_loop();
}
