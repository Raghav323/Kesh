/**************************************\
 ======================================
        
         Plain magic bitboards
     implementation & demonstration
     
                  by
                  
           Code Monkey King

 ======================================
\**************************************/





#include "../include/defs.hpp"



// rook rellevant occupancy bits
int rook_rellevant_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

// bishop rellevant occupancy bits
int bishop_rellevant_bits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};




// just a random number
unsigned int state = 1804289383;

// 32-bit number pseudo random generator
unsigned int generate_random_number()
{
	// XOR shift algorithm
	unsigned int x = state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	state = x;
	return x;
}

// generate random U64 number
U64 random_U64()
{
    // init numbers to randomize
    U64 u1, u2, u3, u4;
    
    // randomize numbers
    u1 = (U64)(generate_random_number()) & 0xFFFF;
    u2 = (U64)(generate_random_number()) & 0xFFFF;
    u3 = (U64)(generate_random_number()) & 0xFFFF;
    u4 = (U64)(generate_random_number()) & 0xFFFF;
    
    // shuffle bits and return
    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

// get random few bits
U64 random_fewbits() {
    return random_U64() & random_U64() & random_U64();
}



// get index of LS1B in bitboard
int get_ls1b_index(U64 bitboard) {
    // make sure bitboard is not empty
    if (bitboard != 0)
        // convert trailing zeros before LS1B to ones and count them
        return count_bits((bitboard & -bitboard) - 1);
    
    // otherwise
    else
        // return illegal index
        return -1;
}

// set occupancies
U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask)
{
    // occupancy map
    U64 occupancy = 0ULL;
    
    // loop over the range of bits within attack mask
    for (int count = 0; count < bits_in_mask; count++)
    {
        // get LS1B index of attacks mask
        int square = get_ls1b_index(attack_mask);
        
        // pop LS1B in attack map
        pop_bit(attack_mask, square);
        
        // make sure occupancy is on board
        if (index & (1 << count))
            // populate occupancy map
            occupancy |= (1ULL << square);
    }
    
    // return occupancy map
    return occupancy;
}

// mask bishop attacks
U64 mask_bishop_attacks(int square)
{
    // attack bitboard
    U64 attacks = 0ULL;
    
    // init files & ranks
    int f, r;
    
    // init target files & ranks
    int tr = square / 8;
    int tf = square % 8;
    
    // generate attacks
    for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) attacks |= (1ULL << (r * 8 + f));
    for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) attacks |= (1ULL << (r * 8 + f));
    
    // return attack map for bishop on a given square
    return attacks;
}

// mask rook attacks
U64 mask_rook_attacks(int square)
{
    // attacks bitboard
    U64 attacks = 0ULL;
    
    // init files & ranks
    int f, r;
    
    // init target files & ranks
    int tr = square / 8;
    int tf = square % 8;
    
    // generate attacks
    for (r = tr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
    for (r = tr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));
    for (f = tf + 1; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
    for (f = tf - 1; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));
    
    // return attack map for bishop on a given square
    return attacks;
}

// bishop attacks
U64 bishop_attacks_on_the_fly(int square, U64 block)
{
    // attack bitboard
    U64 attacks = 0ULL;
    
    // init files & ranks
    int f, r;
    
    // init target files & ranks
    int tr = square / 8;
    int tf = square % 8;
    
    // generate attacks
    for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++)
    {
        attacks |= (1ULL << (r * 8 + f));
        if (block & (1ULL << (r * 8 + f))) break;
    }
    
    for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--)
    {
        attacks |= (1ULL << (r * 8 + f));
        if (block & (1ULL << (r * 8 + f))) break;
    }
    
    for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++)
    {
        attacks |= (1ULL << (r * 8 + f));
        if (block & (1ULL << (r * 8 + f))) break;
    }
    
    for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--)
    {
        attacks |= (1ULL << (r * 8 + f));
        if (block & (1ULL << (r * 8 + f))) break;
    }
    
    // return attack map for bishop on a given square
    return attacks;
}

// rook attacks
U64 rook_attacks_on_the_fly(int square, U64 block)
{
    // attacks bitboard
    U64 attacks = 0ULL;
    
    // init files & ranks
    int f, r;
    
    // init target files & ranks
    int tr = square / 8;
    int tf = square % 8;
    
    // generate attacks
    for (r = tr + 1; r <= 7; r++)
    {
        attacks |= (1ULL << (r * 8 + tf));
        if (block & (1ULL << (r * 8 + tf))) break;
    }
    
    for (r = tr - 1; r >= 0; r--)
    {
        attacks |= (1ULL << (r * 8 + tf));
        if (block & (1ULL << (r * 8 + tf))) break;
    }
    
    for (f = tf + 1; f <= 7; f++)
    {
        attacks |= (1ULL << (tr * 8 + f));
        if (block & (1ULL << (tr * 8 + f))) break;
    }
    
    for (f = tf - 1; f >= 0; f--)
    {
        attacks |= (1ULL << (tr * 8 + f));
        if (block & (1ULL << (tr * 8 + f))) break;
    }
    
    // return attack map for bishop on a given square
    return attacks;
}


/**************************************\

        Generating magic numbers
        
\**************************************/

// find magic number
U64 find_magic(int square, int relevant_bits, int bishop) {
    // define occupancies array
    U64 occupancies[4096];

    // define attacks array
    U64 attacks[4096];

    // define used indicies array
    U64 used_attacks[4096];
    
    // mask piece attack
    U64 mask_attack = bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);

    // occupancy variations
    int occupancy_variations = 1 << relevant_bits;

    // loop over the number of occupancy variations
    for(int count = 0; count < occupancy_variations; count++) {
        // init occupancies
        occupancies[count] = set_occupancy(count, relevant_bits, mask_attack);
        
        // init attacks
        attacks[count] = bishop ? bishop_attacks_on_the_fly(square, occupancies[count]) :
                                  rook_attacks_on_the_fly(square, occupancies[count]);
    }

    // test magic numbers
    for(int random_count = 0; random_count < 100000000; random_count++)
    {
        // init magic number candidate
        U64 magic = random_fewbits();

        // skip testing magic number if inappropriate
        if(count_bits((mask_attack * magic) & 0xFF00000000000000ULL) < 6) continue;

        // reset used attacks array
        memset(used_attacks, 0ULL, sizeof(used_attacks));
        
        // init count & fail flag
        int count, fail;
        
        // test magic index
        for (count = 0, fail = 0; !fail && count < occupancy_variations; count++) {
            // generate magic index
            int magic_index = (int)((occupancies[count] * magic) >> (64 - relevant_bits));
          
            // if got free index
            if(used_attacks[magic_index] == 0ULL)
                // assign corresponding attack map
                used_attacks[magic_index] = attacks[count];

            // otherwise fail on  collision
            else if(used_attacks[magic_index] != attacks[count]) fail = 1;
        }
        
        // return magic if it works
        if(!fail) return magic;
    }
    
    // on fail
    printf("***Failed***\n");
    return 0ULL;
}

// init magics
void init_magics()
{
  printf("const U64 rook_magics[64] = {\n");
  
  // loop over 64 board squares
  for(int square = 0; square < 64; square++)
      printf("    0x%llxULL,\n", find_magic(square, rook_rellevant_bits[square], 0));
  
  printf("};\n\nconst U64 bishop_magics[64] = {\n");
  
  // loop over 64 board squares
  for(int square = 0; square < 64; square++)
      printf("    0x%llxULL,\n", find_magic(square, bishop_rellevant_bits[square], 1));
  
  printf("};\n\n");
}


/**************************************\

        Initializing attack table
        
\**************************************/

// masks
U64 bishop_masks[64];
U64 rook_masks[64];

// attacks
U64 bishop_attacks[64][512];
U64 rook_attacks[64][4096];

// rook magic numbers
const U64 rook_magics[64] = {
    0xa8002c000108020ULL,
    0x6c00049b0002001ULL,
    0x100200010090040ULL,
    0x2480041000800801ULL,
    0x280028004000800ULL,
    0x900410008040022ULL,
    0x280020001001080ULL,
    0x2880002041000080ULL,
    0xa000800080400034ULL,
    0x4808020004000ULL,
    0x2290802004801000ULL,
    0x411000d00100020ULL,
    0x402800800040080ULL,
    0xb000401004208ULL,
    0x2409000100040200ULL,
    0x1002100004082ULL,
    0x22878001e24000ULL,
    0x1090810021004010ULL,
    0x801030040200012ULL,
    0x500808008001000ULL,
    0xa08018014000880ULL,
    0x8000808004000200ULL,
    0x201008080010200ULL,
    0x801020000441091ULL,
    0x800080204005ULL,
    0x1040200040100048ULL,
    0x120200402082ULL,
    0xd14880480100080ULL,
    0x12040280080080ULL,
    0x100040080020080ULL,
    0x9020010080800200ULL,
    0x813241200148449ULL,
    0x491604001800080ULL,
    0x100401000402001ULL,
    0x4820010021001040ULL,
    0x400402202000812ULL,
    0x209009005000802ULL,
    0x810800601800400ULL,
    0x4301083214000150ULL,
    0x204026458e001401ULL,
    0x40204000808000ULL,
    0x8001008040010020ULL,
    0x8410820820420010ULL,
    0x1003001000090020ULL,
    0x804040008008080ULL,
    0x12000810020004ULL,
    0x1000100200040208ULL,
    0x430000a044020001ULL,
    0x280009023410300ULL,
    0xe0100040002240ULL,
    0x200100401700ULL,
    0x2244100408008080ULL,
    0x8000400801980ULL,
    0x2000810040200ULL,
    0x8010100228810400ULL,
    0x2000009044210200ULL,
    0x4080008040102101ULL,
    0x40002080411d01ULL,
    0x2005524060000901ULL,
    0x502001008400422ULL,
    0x489a000810200402ULL,
    0x1004400080a13ULL,
    0x4000011008020084ULL,
    0x26002114058042ULL,
};

// bishop magic number
const U64 bishop_magics[64] = {
    0x89a1121896040240ULL,
    0x2004844802002010ULL,
    0x2068080051921000ULL,
    0x62880a0220200808ULL,
    0x4042004000000ULL,
    0x100822020200011ULL,
    0xc00444222012000aULL,
    0x28808801216001ULL,
    0x400492088408100ULL,
    0x201c401040c0084ULL,
    0x840800910a0010ULL,
    0x82080240060ULL,
    0x2000840504006000ULL,
    0x30010c4108405004ULL,
    0x1008005410080802ULL,
    0x8144042209100900ULL,
    0x208081020014400ULL,
    0x4800201208ca00ULL,
    0xf18140408012008ULL,
    0x1004002802102001ULL,
    0x841000820080811ULL,
    0x40200200a42008ULL,
    0x800054042000ULL,
    0x88010400410c9000ULL,
    0x520040470104290ULL,
    0x1004040051500081ULL,
    0x2002081833080021ULL,
    0x400c00c010142ULL,
    0x941408200c002000ULL,
    0x658810000806011ULL,
    0x188071040440a00ULL,
    0x4800404002011c00ULL,
    0x104442040404200ULL,
    0x511080202091021ULL,
    0x4022401120400ULL,
    0x80c0040400080120ULL,
    0x8040010040820802ULL,
    0x480810700020090ULL,
    0x102008e00040242ULL,
    0x809005202050100ULL,
    0x8002024220104080ULL,
    0x431008804142000ULL,
    0x19001802081400ULL,
    0x200014208040080ULL,
    0x3308082008200100ULL,
    0x41010500040c020ULL,
    0x4012020c04210308ULL,
    0x208220a202004080ULL,
    0x111040120082000ULL,
    0x6803040141280a00ULL,
    0x2101004202410000ULL,
    0x8200000041108022ULL,
    0x21082088000ULL,
    0x2410204010040ULL,
    0x40100400809000ULL,
    0x822088220820214ULL,
    0x40808090012004ULL,
    0x910224040218c9ULL,
    0x402814422015008ULL,
    0x90014004842410ULL,
    0x1000042304105ULL,
    0x10008830412a00ULL,
    0x2520081090008908ULL,
    0x40102000a0a60140ULL,
};

// init slider pieces attacks
void init_sliders_attacks(int is_bishop)
{
    // loop over 64 board squares
    for (int square = 0; square < 64; square++)
    {
        // init bishop & rook masks
        bishop_masks[square] = mask_bishop_attacks(square);
        rook_masks[square] = mask_rook_attacks(square);
        
        // init current mask
        U64 mask = is_bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);
        
        // count attack mask bits
        int bit_count = count_bits(mask);
        
        // occupancy variations count
        int occupancy_variations = 1 << bit_count;
        
        // loop over occupancy variations
        for (int count = 0; count < occupancy_variations; count++)
        {
            // bishop
            if (is_bishop)
            {
                // init occupancies, magic index & attacks
                U64 occupancy = set_occupancy(count, bit_count, mask);
                U64 magic_index = occupancy * bishop_magics[square] >> 64 - bishop_rellevant_bits[square];
                bishop_attacks[square][magic_index] = bishop_attacks_on_the_fly(square, occupancy);                
            }
            
            // rook
            else
            {
                // init occupancies, magic index & attacks
                U64 occupancy = set_occupancy(count, bit_count, mask);
                U64 magic_index = occupancy * rook_magics[square] >> 64 - rook_rellevant_bits[square];
                rook_attacks[square][magic_index] = rook_attacks_on_the_fly(square, occupancy);                
            }
        }
    }
}

// lookup bishop attacks 
U64 get_bishop_attacks(int square, U64 occupancy) {
	
	// calculate magic index
	occupancy &= bishop_masks[square];
	occupancy *=  bishop_magics[square];
	occupancy >>= 64 - bishop_rellevant_bits[square];
	
	// return rellevant attacks
	return bishop_attacks[square][occupancy];
	
}

// lookup rook attacks 
U64 get_rook_attacks(int square, U64 occupancy) {
	
	// calculate magic index
	occupancy &= rook_masks[square];
	occupancy *=  rook_magics[square];
	occupancy >>= 64 - rook_rellevant_bits[square];
	
	// return rellevant attacks
	return rook_attacks[square][occupancy];

}


// define squares
enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

// define sides
enum { white, black };



// not A file bitboard

/*
  8  0 1 1 1 1 1 1 1
  7  0 1 1 1 1 1 1 1
  6  0 1 1 1 1 1 1 1
  5  0 1 1 1 1 1 1 1
  4  0 1 1 1 1 1 1 1
  3  0 1 1 1 1 1 1 1
  2  0 1 1 1 1 1 1 1
  1  0 1 1 1 1 1 1 1
     
     a b c d e f g h
*/

U64 not_a_file = 18374403900871474942ULL;

// not H file bitboard

/*
  8  1 1 1 1 1 1 1 0
  7  1 1 1 1 1 1 1 0
  6  1 1 1 1 1 1 1 0
  5  1 1 1 1 1 1 1 0
  4  1 1 1 1 1 1 1 0
  3  1 1 1 1 1 1 1 0
  2  1 1 1 1 1 1 1 0
  1  1 1 1 1 1 1 1 0

     a b c d e f g h
*/

U64 not_h_file = 9187201950435737471ULL;

// not HG file

/*
  8  1 1 1 1 1 1 0 0
  7  1 1 1 1 1 1 0 0
  6  1 1 1 1 1 1 0 0
  5  1 1 1 1 1 1 0 0
  4  1 1 1 1 1 1 0 0
  3  1 1 1 1 1 1 0 0
  2  1 1 1 1 1 1 0 0
  1  1 1 1 1 1 1 0 0

     a b c d e f g h
*/

U64 not_hg_file = 4557430888798830399ULL;

// not AB file

/*
  8  0 0 1 1 1 1 1 1
  7  0 0 1 1 1 1 1 1
  6  0 0 1 1 1 1 1 1
  5  0 0 1 1 1 1 1 1
  4  0 0 1 1 1 1 1 1
  3  0 0 1 1 1 1 1 1
  2  0 0 1 1 1 1 1 1
  1  0 0 1 1 1 1 1 1

     a b c d e f g h
*/

U64 not_ab_file = 18229723555195321596ULL;


// pawn attacks array [side][square]
U64 pawn_attacks[2][64];

// knight attacks array [square]
U64 knight_attacks[64];

// mask pawn attacks
U64 mask_pawn_attacks(int side, int square)
{
    // attack bitboard
    U64 attacks = 0;
    
    // piece bitboard
    U64 bitboard = 0;
    
    // set piece on bitboard
    set_bit(bitboard, square);
    
    // white pawn attacks
    if (!side)
    {
        // make sure attack is on board
        if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
        if((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    }
    
    // black pawn atacks
    else
    {
        // make sure attack is on board
        if ((bitboard << 7) & not_h_file) attacks |= (bitboard << 7);
        if((bitboard << 9) & not_a_file) attacks |= (bitboard << 9);
    }
    
    // return attack map for pawn on a given square
    return attacks;  
}

// mask knight attacks
U64 mask_knight_attacks(int square)
{
    // attack bitboard
    U64 attacks = 0;
    
    // piece bitboard
    U64 bitboard = 0;
    
    // set piece on bitboard
    set_bit(bitboard, square);
    
    // generate knight
    if ((bitboard >> 17) & not_h_file) attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & not_a_file) attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & not_hg_file) attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & not_ab_file) attacks |= (bitboard >> 6);
    if ((bitboard << 17) & not_a_file) attacks |= (bitboard << 17);
    if ((bitboard << 15) & not_h_file) attacks |= (bitboard << 15);
    if ((bitboard << 10) & not_ab_file) attacks |= (bitboard << 10);
    if ((bitboard << 6) & not_hg_file) attacks |= (bitboard << 6);
    
    // return attack map for knight on a given square
    return attacks;
}

// init pre-calculated attack tables for leaper pieces (pawns, knights, kings)
void init_leaper_attacks()
{
    // loop over 64 board squares
    for (int square = 0; square < 64; square++)
    {
        // init leaper attacks
        pawn_attacks[black][square] = mask_pawn_attacks(white, square);
        pawn_attacks[white][square] = mask_pawn_attacks(black, square);
        knight_attacks[square] = mask_knight_attacks(square);
    }
}


const U64 notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
const U64 notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080

U64 king_attacks[64];
U64 queen_attacks[64];


U64 soutOne (U64 b) {return  b >> 8;}
U64 nortOne (U64 b) {return  b << 8;}
U64 westOne (U64 b) {return (b >> 1) & notHFile;}
U64 eastOne (U64 b) {return (b << 1) & notAFile;}

U64 kingAttacks(U64 kingSet) {
   U64 attacks = eastOne(kingSet) | westOne(kingSet);
   kingSet    |= attacks;
   attacks    |= nortOne(kingSet) | soutOne(kingSet);
   return attacks;
}


void init_king_attacks(){
U64 sqBB = 1;
for (int sq = 0; sq < 64; sq++, sqBB <<= 1)
   king_attacks[sq] = kingAttacks(sqBB);
}





const int BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

int pop_1st_bit(U64 *bb) {
  U64 b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *bb &= (*bb - 1);
  return BitTable[(fold * 0x783a9b23) >> 26];
}


U64 pawn_pushes[2][64];

void init_pawn_pushes(){
    
    for(int i=0;i<56;i++){
        pawn_pushes[0][i] = (1ULL) << (i+8);
       
    }
    for(int i=56;i<64;i++){
        pawn_pushes[0][i]=0ULL;

    }

    for(int i=8;i<16;i++){
        pawn_pushes[0][i]|=(1ULL)<<(i+16);
        
    }

    for(int i=8;i<56;i++){
        pawn_pushes[1][i] = (1ULL) << (i-8);
       
    }
    for(int i=0;i<8;i++){
        pawn_pushes[1][i]=0ULL;

    }

    for(int i=48;i<56;i++){
        pawn_pushes[1][i]|=(1ULL)<<(i-16);
        
    }

  
}

U64 get_pawn_moves(int sq , int side , U64 occupancy){
    U64 blocker = pawn_pushes[side][sq] & occupancy;
    return (1ULL - (1ULL & (blocker >> (sq + PAWN_PUSH_DIRECTION[side])))) * (pawn_pushes[side][sq] & ~blocker);
}


U64 xrayRookAttacks(U64 occ, U64 blockers, int rookSq) {
   U64 attacks = get_rook_attacks(rookSq,occ);
   blockers &= attacks;
   return attacks ^ get_rook_attacks(rookSq, occ ^ blockers);
}

U64 xrayBishopAttacks(U64 occ, U64 blockers, int bishopSq) {
   U64 attacks = get_bishop_attacks(bishopSq, occ );
   blockers &= attacks;
   return attacks ^ get_bishop_attacks(bishopSq ,occ ^ blockers);
}


U64 rectlookup[64][64];

void init_rect_lookup(){
for(int i=0;i<64;i++){
    for(int j=0;j<64;j++){
        U64 TempMask1 = (get_bishop_attacks(i , 0ULL | (1ULL << j )) | (1ULL)<<i ) & get_bishop_attacks(j,0ULL | (1ULL << i ));
    if (!(get_bit(TempMask1, i))){
      TempMask1 = (get_rook_attacks(i , 0ULL | (1ULL <<  j ))| (1ULL<<i)) & get_rook_attacks(j,0ULL | (1ULL << i ));
    }
    if (!(get_bit(TempMask1,i))){
        TempMask1 = 0ULL;
    }

    rectlookup[i][j] = TempMask1; 
    }
}
}
U64 castleMap[4];
void init_castle_map(){
    castleMap[0] = 0x0000000000000060ULL; // white short 
    castleMap[1] = 0x000000000000000eULL; // white long 
    castleMap[2] = 0x6000000000000000ULL; // black short 
    castleMap[3] = 0x0e00000000000000ULL; // black long 
}
































