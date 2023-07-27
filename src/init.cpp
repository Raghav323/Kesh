#include "../include/defs.hpp"



void AllInit(){
    // InitSq120To64();
    
    init_sliders_attacks(1);
    init_sliders_attacks(0);
    init_leaper_attacks();
    init_pawn_pushes();
    init_king_attacks();
    init_rect_lookup();

}