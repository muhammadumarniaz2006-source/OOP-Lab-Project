#include "King.hpp" 
#include "Board.hpp"
#include "Move.hpp" 

King::King(Pos p, PieceColor c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1,1}, {1,-1}, {-1,-1}}; 
  //King ke possible directions, par king sirf ek step move kar sakta hai, is liye directions same hain queen ke, lekin iski valid move check karte waqt ensure karna hoga ke king sirf ek step hi move kare.
}

char King::getSymbol() { 
  return (getcolor() == PieceColor::WHITE_PIECE) ? 'K' : 'k'; 
}

void King::calculatePossibleMoves(bool checkSafety){
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::kingMove(*board, *this, checkSafety);
}