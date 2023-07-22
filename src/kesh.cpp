#include "../include/defs.hpp"
#include "../include/Board.hpp"
#include "../include/Square.hpp"
#include "../include/Piece.hpp"
#include "../include/movegen.hpp"

#include <iostream>

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

#define TEST_FEN_15 "5NK1/1k1BP3/8/8/3Pp3/8/7B/7Q b - d3 0 1"

#define TEST_FEN_16 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

// AttackBoards --> KingDanger --> KingInfo --> CaptureBoard --> MoveList
int main(){
    AllInit();
    Board_State board = Board_State(TEST_FEN_16);

    cout<<"Pieces Board  : "<<endl;
    board.printBoard();


    // print_bitboard(board.OccupancyMapColor[0]);
    MoveGen movegen;

    
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

//     cout<<"Check bitboard : "; print_bitboard(movegen.kingCheckingPieces[0]);cout<<endl;

//     cout<<"Push Mask : "; print_bitboard(movegen.pushMask[0]);cout<<endl;

//     cout<<"DEBUG : "<<endl;
//     // print_bitboard(get_pawn_moves(54, 1, (1ULL)<<38));

//     print_bitboard(xrayBishopAttacks(board.OccupancyMap, board.OccupancyMapColor[0], board.KingSq[0]));
//     // cout<<"King Moves : "; print_bitboard(movegen.Moves[1][KING][0]);cout<<endl;

//     cout<<"BQ BITBOARD : "<<endl;
//     print_bitboard(board.OccupancyMapBQ[0]);

//     cout<<"ALL PINNED PIECCE :  "<<endl;

//     movegen.GenerateMovesForPinned(board , 0);

//     print_bitboard(movegen.pinnedPiecesMap[0]);

movegen.generate_moves(board , 0);

print_Move_list(movegen.moveList);




    return 0;
}