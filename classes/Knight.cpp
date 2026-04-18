#include "Knight.hpp"
#include "Move.hpp"

Knight::Knight(Pos p, Color c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}}; 
  //Knight ke possible directions, knight ke moves L shape mai hotay hai is liye 2 aur 1 ka combination use kia hai
  calculatePossibleMoves();
}

char Knight::getSymbol(){
  return (getcolor() == Color::WHITE) ? 'N' : 'n'; 
}

void Knight::calculatePossibleMoves() {
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::knightMove(*board, pos, color, Directions);
}