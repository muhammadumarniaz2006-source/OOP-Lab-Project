#include "Queen.hpp"
#include "Move.hpp"

Queen::Queen(Pos p, Color c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1,1}, {1,-1}, {-1,-1}}; //Queen ke possible directions
  calculatePossibleMoves();
}

char Queen::getSymbol(){ 
  return (getcolor() == Color::WHITE) ? 'Q' : 'q'; 
}

void Queen::calculatePossibleMoves() {
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::slidingMove(*board, pos, color, Directions);
}