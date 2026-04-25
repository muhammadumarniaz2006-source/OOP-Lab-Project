#include "Queen.hpp"
#include "Board.hpp"
#include "Move.hpp"

Queen::Queen(Pos p, PieceColor c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1,1}, {1,-1}, {-1,-1}}; //Queen ke possible directions
}

char Queen::getSymbol(){ 
  return (getcolor() == PieceColor::WHITE_PIECE) ? 'Q' : 'q'; 
}

void Queen::calculatePossibleMoves(bool checkSafety) {
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::slidingMove(*board, this, checkSafety);
}