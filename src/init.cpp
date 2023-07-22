#include "../include/defs.hpp"

// int Sq120ToSq64[BOARD_SQ];
// int Sq64ToSq120[64];

// void InitSq120To64(){
//     int index = 0;
//     int file = FILE_A;
//     int rank = RANK_1;
//     int sq = A1;
//     int sq64 = 0;

//     for(index = 0; index < BOARD_SQ; ++index){
//         Sq120ToSq64[index] = 65;
//     }

//     for(index = 0; index < 64; ++index){
//         Sq64ToSq120[index] = 120;
//     }

//     for(rank = RANK_1; rank <= RANK_8; ++rank){
//         for(file = FILE_A; file <= FILE_H; ++file){
//             sq = FR2SQ(file, rank);
//             Sq64ToSq120[sq64] = sq;
//             Sq120ToSq64[sq] = sq64;
//             sq64++;
//         }
//     }
// }



void AllInit(){
    // InitSq120To64();
    
    init_sliders_attacks(1);
    init_sliders_attacks(0);
    init_leaper_attacks();
    init_pawn_pushes();
    init_king_attacks();
    init_rect_lookup();

}