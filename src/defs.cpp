#include "../include/defs.hpp"

int PAWN_PUSH_DIRECTION[2] = {8, -8};
unordered_map<char, int> notation = {{'Q',3},{'R',2},{'B',1},{'N',0},{'q',3},{'r',2},{'b',1},{'n',0}};

const int CastlePerm[64] = {

    13, 15, 15, 15, 12, 15, 15, 14, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 7,  15, 15, 15, 3,  15, 15, 11};

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
    cout << "Move " << i << " ";
    cout << "FROM SQ : " << (move & 0x3f) << " TO SQ : " << ((move >> 6) & 0x3f)
         << " PROMOTION : " << ((move >> 12) & 0x3)
         << " SPECIAL : " << ((move >> 14) & 0x3) << endl;
    cout << "\n";
  }
  cout << "\n";
}

void print_square(int sqNo) {
  cout << (char)('a' + sqNo % 8) << 1 + (sqNo / 8);
}

void print_move(int move) {
  // write for me copilot

  int from = (move & 0x3f);
  int to = ((move >> 6) & 0x3f);
  print_square(from);
  print_square(to);
  if (((move >> 14) & 0x3) == 1) {
    switch (((move >> 12) & 0x3) + 2) {
    case KNIGHT:
      cout << "N";
      break;
    case BISHOP:
      cout << "B";
      break;
    case ROOK:
      cout << "R";
      break;
    case QUEEN:
      cout << "Q";
      break;
    }
  }
}

