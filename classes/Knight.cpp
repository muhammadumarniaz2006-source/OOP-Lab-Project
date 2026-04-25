#include "Knight.hpp"
#include "Board.hpp"
#include "Move.hpp"

Knight::Knight(Pos p, PieceColor c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}}; 
  //Knight ke possible directions, knight ke moves L shape mai hotay hai is liye 2 aur 1 ka combination use kia hai
}

char Knight::getSymbol(){
  return (getcolor() == PieceColor::WHITE_PIECE) ? 'N' : 'n'; 
}

void Knight::calculatePossibleMoves(bool checkSafety) {
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::knightMove(*board, this, checkSafety);
}