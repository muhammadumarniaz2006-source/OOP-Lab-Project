#include "Bishop.hpp"
#include "Board.hpp"
#include "Move.hpp"
//override likhna optional hota hai.
/*Bishop logic:
    row difference and col difference nikal ker dono kko compare karay gay
    if dono brabar hai tu valid move hai ager destinated position per apna piece  na ho ya uskay rastay mai koi bhi dosra piece ho
*/

Bishop::Bishop(Pos p, PieceColor c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,1}, {-1,1}, {1,-1}, {-1,-1}}; //Bishop ke possible directions
}

char Bishop::getSymbol() { 
  return (getcolor() == PieceColor::WHITE_PIECE) ? 'B' : 'b'; 
}

void Bishop::calculatePossibleMoves(bool checkSafety){
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::slidingMove(*board, this, checkSafety);
}