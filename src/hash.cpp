
#include "../include/hash.hpp"
#include "../include/defs.hpp"



Zobrist::Zobrist(){
    // std::random_device rd;
    gen = mt19937_64();

    
    // srand(time(NULL));
    for(int i = 0 ; i < 64 ; i++){
        for(int j = 0 ; j < 13 ; j++){
            pieceKeys[i][j] =dis(gen);
        }
    }
    sideKey = dis(gen);
    for(int i = 0 ; i < 16 ; i++){
        castleKeys[i] = dis(gen);
    }


};

U64  Zobrist::hashPiece(U64 sKey , PieceType piece, int sq) {
    if (sq == NO_SQ)
      return sKey;
    if (piece == NO_PIECE)
      return sKey;
    // cout<<"PIECE KEYS :"<<pieceKeys[sq][piece]<<endl;
    (sKey) ^= pieceKeys[sq][piece];
    return sKey ; 

   
  };

  U64  Zobrist::hashCastle(U64 sKey ,  int castlePerm) { (sKey) ^= castleKeys[castlePerm];  return sKey;};// cout<<"TRANSFORMED POS KEY IS "<<*sKey<<endl; };






U64  Zobrist::hashSide(U64 sKey) {
    
    (sKey) ^= sideKey;
    return sKey;
    // cout<<"TRANSFORMED POS KEY IS "<<*sKey<<endl;
    
  };