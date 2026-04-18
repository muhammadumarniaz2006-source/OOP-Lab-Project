#include "Bishop.hpp"
#include "Move.hpp"
#include <cmath>
//override likhna optional hota hai.
/*Bishop logic:
    row difference and col difference nikal ker dono kko compare karay gay
    if dono brabar hai tu valid move hai ager destinated position per apna piece  na ho ya uskay rastay mai koi bhi dosra piece ho
*/

Bishop::Bishop(Pos p, Color c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,1}, {-1,1}, {1,-1}, {-1,-1}}; //Bishop ke possible directions
  calculatePossibleMoves();
}

char Bishop::getSymbol() { 
  return (getcolor() == Color::WHITE) ? 'B' : 'b'; 
}

void Bishop::calculatePossibleMoves(){
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::slidingMove(*board, pos, color, Directions);
}