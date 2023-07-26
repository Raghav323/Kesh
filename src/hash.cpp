
#include "../include/hash.hpp"
#include "../include/defs.hpp"



Zobrist::Zobrist(U64 * posKey){
    // std::random_device rd;
    gen = mt19937_64();

    sKey = posKey;
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

void  Zobrist::hashPiece(PieceType piece, int sq) {
    if (sq == NO_SQ)
      return;
    if (piece == NO_PIECE)
      return;
    // cout<<"PIECE KEYS :"<<pieceKeys[sq][piece]<<endl;
    (*sKey) ^= pieceKeys[sq][piece];

   
  };

  void  Zobrist::hashCastle(int castlePerm) { (*sKey) ^= castleKeys[castlePerm]; };// cout<<"TRANSFORMED POS KEY IS "<<*sKey<<endl; };






  void  Zobrist::hashSide() {
    
    (*sKey) ^= sideKey;
    // cout<<"TRANSFORMED POS KEY IS "<<*sKey<<endl;
    
  };