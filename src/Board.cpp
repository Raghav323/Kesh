#include "../include/Board.hpp"
#include "../include/Square.hpp"
#include "../include/defs.hpp"

void Board_State::printBoard() {
  std::cout << std::endl << std::endl;
  for (int rank = RANK_8; rank >= RANK_1; rank--) {
    for (int file = FILE_A; file <= FILE_H; file++) {
      int sq = FR2SQ(file, rank);
      std::cout << pieceChars[piecePlacement[sq].pieceOccupying.pieceType]
                << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Side: " << (side == WHITE ? "WHITE" : "BLACK") << std::endl;
  std::cout << "EnPassant Square: ";

  if (enPas == NO_SQ) {
    cout << "-";
  } else {
    print_square(enPas);
  }

  cout << std::endl;
  std::cout << "Fifty Move: " << fiftyMove << std::endl;
  std::cout << "Castle: " << castlePermissionsToKQkq(castlePerm) << std::endl;
  // std::cout << "Ply: " << ply << std::endl;
  // std::cout << "His Ply: " << hisPly << std::endl;
  std::cout << "State Key: " << hex << stateKey << dec << std::endl;
  // std::cout << "White EVAL: " << eval[0] << std::endl;
  // std::cout << "BLACK EVAL: " << eval[1] << std::endl;

  // cout<<"Full Moves Made : " << fullMoves <<endl;
  cout << endl;
}

void Board_State::updatePieceBoard(Square sq, Piece piece, bool add) {

  if (add) {

    switch (piece.pieceType) {
    case wK:
    case bK:
      KingSq[piece.get_piece_color()] = sq.squareNo;
      break;

    case wQ:
    case bQ:
      set_bit(OccupancyMapBQ[piece.get_piece_color()], sq.squareNo);
      set_bit(OccupancyMapRQ[piece.get_piece_color()], sq.squareNo);
      break;

    case bR:
    case wR:
      set_bit(OccupancyMapRQ[piece.get_piece_color()], sq.squareNo);
      break;

    case bB:
    case wB:
      set_bit(OccupancyMapBQ[piece.get_piece_color()], sq.squareNo);
      break;
    case wP:
    case bP:
      set_bit(OccupancyMapP[piece.get_piece_color()], sq.squareNo);
      break;
    case wN:
    case bN:
      set_bit(OccupancyMapN[piece.get_piece_color()], sq.squareNo);
      break;
    default:
      break;
    };

        increment_evalPos(sq, piece, 1,numPieces[NO_PIECE]<8);

    // BUG -> numPieces[piece.pieceType] += 1;

    stateKey = hasher.hashPiece(stateKey, piece.pieceType, sq.squareNo);
    pieceBoard[piece.pieceType].insert(sq);
    piecePlacement[sq.squareNo].pieceOccupying = piece;
    piece.pieceSquare = sq.squareNo;
    set_bit(OccupancyMap, sq.squareNo);
    set_bit(OccupancyMapColor[piece.get_piece_color()], sq.squareNo);
    // set_bit(piecesMap[piece.pieceType], sq.squareNo);

  } else {

    if (piece.pieceType == NO_PIECE) {
      return;
    }

    switch (piece.pieceType) {
    // case wK :
    //     KingSq[WHITE] = NO_SQ;
    //     break;
    // case bK:
    //     KingSq[BLACK] = NO_SQ;
    //     break;
    case wQ:
    case bQ:
      clear_bit(OccupancyMapBQ[piece.get_piece_color()], sq.squareNo);
      clear_bit(OccupancyMapRQ[piece.get_piece_color()], sq.squareNo);
      break;

    case bR:
    case wR:
      clear_bit(OccupancyMapRQ[piece.get_piece_color()], sq.squareNo);
      break;

    case bB:
    case wB:
      clear_bit(OccupancyMapBQ[piece.get_piece_color()], sq.squareNo);
      break;
    case wP:
    case bP:
      clear_bit(OccupancyMapP[piece.get_piece_color()], sq.squareNo);
      break;
    case wN:
    case bN:
      clear_bit(OccupancyMapN[piece.get_piece_color()], sq.squareNo);
      break;
    default:
      break;
    };
        increment_evalPos(sq, piece, 0,numPieces[NO_PIECE]<8);

    // numPieces[piece.pieceType] -= 1;
    numPieces[NO_PIECE]-=1;

    stateKey = hasher.hashPiece(stateKey, piece.pieceType, sq.squareNo);
    pieceBoard[piece.pieceType].erase(sq);
    piecePlacement[sq.squareNo].pieceOccupying = Piece(NO_PIECE, sq.squareNo);
    clear_bit(OccupancyMap, sq.squareNo);
    // clear_bit(piecesMap[piece.pieceType], sq.squareNo);
    clear_bit(OccupancyMapColor[piece.get_piece_color()], sq.squareNo);

  }
}

void Board_State::MovePiece(int from, int to) {
  updatePieceBoard(piecePlacement[to], piecePlacement[to].pieceOccupying, 0);
  updatePieceBoard(piecePlacement[to], piecePlacement[from].pieceOccupying, 1);
  updatePieceBoard(piecePlacement[from], piecePlacement[from].pieceOccupying,
                   0);
}

Board_State::Board_State(std::string FEN) : hasher() {

  // hasher=Zobrist(&stateKey);
  resetBoard();
  int f = FILE_A;
  int r = RANK_8;

  for (int i = 0; i < BOARD_SQ; i++) {
    piecePlacement[i] = Square(i, Piece(NO_PIECE, BOTH), EMPTY);
  }

  int i = 0;
  char c = FEN[0];

  while (r >= RANK_1 && c != ' ') {
    c = FEN[i];
    int count = 1;
    int sq = FR2SQ(f, r);
    PieceType x = NO_PIECE;
    switch (c) {
    case 'p':
      x = bP;
      break;
    case 'P':
      x = wP;
      break;
    case 'n':
      x = bN;
      break;
    case 'N':
      x = wN;
      break;
    case 'b':
      x = bB;
      break;
    case 'B':
      x = wB;
      break;
    case 'r':
      x = bR;
      break;
    case 'R':
      x = wR;
      break;
    case 'q':
      x = bQ;
      break;
    case 'Q':
      x = wQ;
      break;
    case 'k':
      x = bK;
      break;
    case 'K':
      x = wK;
      break;

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
      count = c - '0';
      i += 1;
      f += count;
      continue;

    case '/':
    case ' ':
      f = FILE_A;
      r--;
      i += 1;
      continue;
    default:
      std::cout << "FEN Error" << std::endl;
      break;
    }
    updatePieceBoard(piecePlacement[sq], Piece(x, sq), true);
    i += count;
    f += count;
  }

  if (FEN[i] == 'w') {
    side = WHITE;
    stateKey = hasher.hashSide(stateKey);

  } else {
    side = BLACK;
  }

  i += 2;

  while (FEN[i] != ' ') {

    switch (FEN[i]) {
    case 'K':
      castlePerm |= WKCA;

      break;
    case 'Q':
      castlePerm |= WQCA;

      break;
    case 'k':
      castlePerm |= BKCA;

      break;
    case 'q':
      castlePerm |= BQCA;

      break;
    case '-':
    case ' ':
      break;
    default:
      std::cout << "FEN Error" << std::endl;
      break;
    }
    i += 1;
  }
  stateKey = hasher.hashCastle(stateKey, castlePerm);

  i += 1;

  // cout<<"hi3"<<endl;

  if (FEN[i] != '-') {
    f = FEN[i] - 'a';
    r = FEN[i + 1] - '1';
    enPas = FR2SQ(f, r);
    i += 3;
    stateKey = hasher.hashPiece(stateKey, NO_PIECE, enPas);
  } else {
    enPas = NO_SQ;
    i += 2;
  }

  int j = 0;

  // cout<<"Pointer after enPassant parse : "<<FEN[i]<<endl;

  if (i < FEN.length()) {
    while (FEN[i + j] != ' ') {

      j++;
    }

    fiftyMove = stoi(FEN.substr(i, j));

    fullMoves = stoi(FEN.substr(i + j + 1, FEN.length() - i - j - 1));
    // cout<<"FULL MOVES DEBUG : "<<FEN[i+j+1]<<endl;
  }

  history[stateKey]=1;
};

void Board_State::resetBoard() {

  side = WHITE; // Default
  stateKey = 0ULL;
  enPas = NO_SQ;
  fiftyMove = 0;
  castlePerm = 0;
  history.clear();
  undoStack = stack<U64>();

  ply = 0;
  hisPly = 0;

  fullMoves = 0;

  OccupancyMap = 0ULL;
  fill(numPieces, numPieces + 13, 0);
  fill(eval, eval + 2, 0);
  fill(KingSq, KingSq + 2, NO_SQ);
  fill(OccupancyMapColor, OccupancyMapColor + 2, 0ULL);
  fill(OccupancyMapBQ, OccupancyMapBQ + 2, 0ULL);
  fill(OccupancyMapRQ, OccupancyMapRQ + 2, 0ULL);
  fill(OccupancyMapP, OccupancyMapP + 2, 0ULL);
  fill(OccupancyMapN, OccupancyMapN + 2, 0ULL);
}

bool Board_State::isRepetition() {
  if (history.find(stateKey) != history.end()) {
    return true;
  }
  return false;
}
