#include "King.hpp" 
#include "Move.hpp" 

King::King(Pos p, Color c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {-1,1}, {1,-1}, {-1,-1}}; 
  //King ke possible directions, par king sirf ek step move kar sakta hai, is liye directions same hain queen ke, lekin iski valid move check karte waqt ensure karna hoga ke king sirf ek step hi move kare.
  calculatePossibleMoves();
}

char King::getSymbol() { 
  return (getcolor() == Color::WHITE) ? 'K' : 'k'; 
}

void King::calculatePossibleMoves(){
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::kingMove(*board, pos, color, Directions);
}