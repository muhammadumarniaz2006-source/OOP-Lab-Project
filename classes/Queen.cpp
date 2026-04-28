#include "Queen.hpp"
#include "Board.hpp"
#include "Move.hpp"

/**
 * Queen: Wazir (Queen) ka object create karta hai aur iski 8 directions (horizontal, vertical, diagonal) set karta hai.
 */
Queen::Queen(Pos p, PieceColor c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1,1}, {1,-1}, {-1,-1}}; //Queen ke possible directions
}

/**
 * getSymbol: Queen ka symbol return karta hai ('Q' for white, 'q' for black).
 */
char Queen::getSymbol(){ 
  return (getcolor() == PieceColor::WHITE_PIECE) ? 'Q' : 'q'; 
}

/**
 * calculatePossibleMoves: Queen ki saari sliding moves calculate karta hai jab tak rasta clear ho.
 */
void Queen::calculatePossibleMoves(bool checkSafety) {
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::slidingMove(*board, this, checkSafety);
}