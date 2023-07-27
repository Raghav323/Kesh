#ifndef DEFS_H
#define DEFS_H

#include <bits/stdc++.h>
#include<iostream> 
# include <assert.h>
#include <unordered_map>

using namespace std;





typedef unsigned long long U64;

#define NAME "Kesh 1.0"
#define MAX_DEPTH 64
#define MAX_BCUTS_STORED 4

#define MAXGAMEMOVES 2048
#define BOARD_SQ 64
#define START_POS "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define clear_bit(bitboard, square) (bitboard &= ~(1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? (bitboard ^= (1ULL << square)) : 0)

extern unordered_map<char, int> notation;


enum PieceTypeWithoutColor { NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING }; // Piece types without color

enum PieceType { NO_PIECE , wP, wN, wB, wR, wQ, wK , bP, bN, bB, bR, bQ, bK }; // Piece types

enum color { WHITE, BLACK, BOTH };


enum File { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE }; // Files

enum Rank { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE }; // Ranks

enum SquareType {NO_SQ= 0 , OFFBOARD = -1 , EMPTY , OCCUPIED }; // Square types




enum SquarEnotation { A1 = 0, B1, C1, D1, E1, F1, G1, H1, // Squares
       A2 = 8, B2, C2, D2, E2, F2, G2, H2,
       A3 = 16, B3, C3, D3, E3, F3, G3, H3,
       A4 = 32, B4, C4, D4, E4, F4, G4, H4,
        B5, C5, D5, E5, F5, G5, H5,
        B6, C6, D6, E6, F6, G6, H6,
        B7, C7, D7, E7, F7, G7, H7,
        B8, C8, D8, E8, F8, G8, H8};

enum { FALSE, TRUE }; // Booleans

enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 }; // Castling permissions




/* MACROS */

#define FR2SQ(f,r)   ( (f)  +  (r) * 8 )  // Converts file and rank to square
// #define SQ64(sq120) (Sq120ToSq64[(sq120)]) // Converts 120 based square to 64 based square
// #define SQ120(sq64) (Sq64ToSq120[(sq64)]) // Converts 64 based square to 120 based square


/* GLOBALS */

extern  U64 pawn_attacks[2][64];
extern  U64 knight_attacks[64];
extern  U64 king_attacks[64];
extern  U64 queen_attacks[64];
extern  U64 pawn_pushes[2][64];
extern  int PAWN_PUSH_DIRECTION[2];
extern  U64 rectlookup[64][64];

extern const int CastlePerm[64];




/* FUNCTIONS */

extern void AllInit();
extern void print_bitboard(U64 bitboard);
extern int count_bits(U64 bitboard); 
extern  PieceType get_piece_type(PieceTypeWithoutColor pieceTypeWithoutColor, int pieceColor);
extern void print_Move_list(vector<int> moveList);
extern void init_castle_map();
extern void print_move(int move);

/* MAGIC */
extern void init_sliders_attacks(int);
extern void init_leaper_attacks();
extern U64 get_rook_attacks(int square, U64 occupancy);
extern U64 get_bishop_attacks(int square, U64 occupancy);
extern void init_king_attacks();
extern int pop_1st_bit(U64 *bb);
extern void init_pawn_pushes();
extern U64 get_pawn_moves(int sq , int side , U64 occupancy);
extern void init_rect_lookup();




// temp 

extern U64 xrayBishopAttacks(U64 occ, U64 blockers, int bishopSq);
U64 xrayRookAttacks(U64 occ, U64 blockers, int rookSq) ;

//random 

//eval 



#endif