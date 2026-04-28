#include "King.hpp" 
#include "Board.hpp"
#include "Move.hpp" 

/**
 * King: Badshah (King) ka object initialize karta hai.
 * Yeh constructor game start hone par dono sides ke King setup karta hai.
 */
King::King(Pos p, PieceColor c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1,1}, {1,-1}, {-1,-1}}; 
  //King ke possible directions, par king sirf ek step move kar sakta hai.
}

/**
 * getSymbol: King ka symbol 'K' (white) ya 'k' (black) return karta hai.
 * Check/Checkmate detection aur board recording ke liye use hota hai.
 */
char King::getSymbol() { 
  return (getcolor() == PieceColor::WHITE_PIECE) ? 'K' : 'k'; 
}

/**
 * calculatePossibleMoves: King ki 1-step moves aur Castling moves calculate karta hai.
 * Is mein yeh bhi check hota hai ke King kisi khatre (check) wali jagah par na jaye.
 */
void King::calculatePossibleMoves(bool checkSafety){
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::kingMove(*board, *this, checkSafety);
}