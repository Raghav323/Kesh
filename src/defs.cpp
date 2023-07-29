#include "../include/defs.hpp"

int PAWN_PUSH_DIRECTION[2] = {8, -8};
unordered_map<char, int> notation = {{'Q',3},{'R',2},{'B',1},{'N',0},{'q',3},{'r',2},{'b',1},{'n',0}};

const int CastlePerm[64] = {

    13, 15, 15, 15, 12, 15, 15, 14, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 7,  15, 15, 15, 3,  15, 15, 11};


const int MvvLva[13][13] = {-1, -1, -1, -1, -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1,
                            -1, 107 , 207 , 227 , 407 , 507 , 607 ,107 , 207 , 227 , 407 , 507 , 607 ,
                            -1 , 106 , 206 , 226 , 406 , 506 , 606 ,106 , 206 , 226 , 406 , 506 , 606,
                            -1 , 105 , 205 , 225 , 405 , 505 , 605 ,105 , 205 , 225 , 405 , 505 , 605,
                            -1 , 104 , 204 , 224 , 404 , 504 , 604 ,104 , 204 , 224 , 404 , 504 , 604,
                            -1 , 103 , 203 , 223 , 403 , 503 , 603 ,103 , 203 , 223 , 403 , 503 , 603,
                            -1 , 102 , 202 , 222 , 402 , 502 , 602 ,102 , 202 , 222 , 402 , 502 , 602,
                            -1, 107 , 207 , 227 , 407 , 507 , 607 ,107 , 207 , 227 , 407 , 507 , 607 ,
                            -1 , 106 , 206 , 226 , 406 , 506 , 606 ,106 , 206 , 226 , 406 , 506 , 606,
                            -1 , 105 , 205 , 225 , 405 , 505 , 605 ,105 , 205 , 225 , 405 , 505 , 605,
                            -1 , 104 , 204 , 224 , 404 , 504 , 604 ,104 , 204 , 224 , 404 , 504 , 604,
                            -1 , 103 , 203 , 223 , 403 , 503 , 603 ,103 , 203 , 223 , 403 , 503 , 603,
                            -1 , 102 , 202 , 222 , 402 , 502 , 602 ,102 , 202 , 222 , 402 , 502 , 602

                            };


const char pieceChars[13] = {
    /* 0 */ '-', // No piece
    /* 1 */ 'P', // White Pawn
    /* 2 */ 'N', // White Knight
    /* 3 */ 'B', // White Bishop
    /* 4 */ 'R', // White Rook
    /* 5 */ 'Q', // White Queen
    /* 6 */ 'K', // White King
    /* 7 */ 'p', // Black Pawn
    /* 8 */ 'n', // Black Knight
    /* 9 */ 'b', // Black Bishop
    /* 10 */ 'r', // Black Rook
    /* 11 */ 'q', // Black Queen
    /* 12 */ 'k'  // Black King
};


std::string castlePermissionsToKQkq(int permissions) {
    std::string result;

    if (permissions & 1) // If '1' bit is set, white can kingside castle
        result += "K";
    else
        result += "-";

    if (permissions & 2) // If '2' bit is set, white can queenside castle
        result += "Q";
    else
        result += "-";

    if (permissions & 4) // If '4' bit is set, black can kingside castle
        result += "k";
    else
        result += "-";

    if (permissions & 8) // If '8' bit is set, black can queenside castle
        result += "q";
    else
        result += "-";

    return result;
}


int count_bits(U64 bitboard) {
  // bit count
  int count = 0;

  // pop bits untill bitboard is empty
  while (bitboard) {
    // increment count
    count++;

    // consecutively reset least significant 1st bit
    bitboard &= bitboard - 1;
  }

  // return bit count
  return count;
}

PieceType get_piece_type(PieceTypeWithoutColor pieceTypeWithoutColor,
                         int pieceColor) {
  return (PieceType)(pieceTypeWithoutColor + (pieceColor * 6));
}

void print_bitboard(U64 bitboard) {
  printf("\n");

  // loop over board ranks
  for (int rank = 7; rank >= 0; rank--) {
    // loop over board files
    for (int file = 0; file < 8; file++) {
      // init board square
      int square = rank * 8 + file;

      // print ranks
      if (!file)
        printf("  %d ", rank);

      // print bit indexed by board square
      printf(" %d", get_bit(bitboard, square) ? 1 : 0);
    }

    printf("\n");
  }

  // print files
  printf("\n     a b c d e f g h\n\n");

  // print bitboard as decimal
  printf("     bitboard: %llud\n\n", bitboard);
}

void print_Move_list(vector<int> moveList) {
  cout << "\n";
  for (int i = 0; i < moveList.size(); i++) {
    int move = moveList[i];
    print_move(move);
    cout << "\n";
  }
  cout << "\n";
}

void print_square(int sqNo) {
  cout << (char)('a' + sqNo % 8) << 1 + (sqNo / 8);
}

void print_move(int move) {
  // write for me copilot
  if(move==0){
    cout<<"No move found"<<endl;
  }
  int from = (move & 0x3f);
  int to = ((move >> 6) & 0x3f);
  print_square(from);
  print_square(to);
  if (((move >> 14) & 0x3) == 1) {
    switch (((move >> 12) & 0x3) + 2) {
    case KNIGHT:
      cout << "n";
      break;
    case BISHOP:
      cout << "b";
      break;
    case ROOK:
      cout << "r";
      break;
    case QUEEN:
      cout << "q";
      break;
    }
  }
}

