#include "Bishop.hpp"
#include "Board.hpp"
#include "Move.hpp"
//override likhna optional hota hai.
/*Bishop logic:
    row difference and col difference nikal ker dono kko compare karay gay
    if dono brabar hai tu valid move hai ager destinated position per apna piece  na ho ya uskay rastay mai koi bhi dosra piece ho
*/

/**
 * Bishop: Bishop object create karta hai aur iski initial directions (diagonal) set karta hai.
 * Yeh constructor tab call hota hai jab game start hoti hai ya pawn promote ho kar bishop banta hai.
 */
Bishop::Bishop(Pos p, PieceColor c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,1}, {-1,1}, {1,-1}, {-1,-1}}; //Bishop ke possible directions
}

/**
 * getSymbol: Piece ka symbol return karta hai ('B' white ke liye, 'b' black ke liye).
 * Yeh function Board save karte waqt aur piece recognize karte waqt use hota hai.
 */
char Bishop::getSymbol() { 
  return (getcolor() == PieceColor::WHITE_PIECE) ? 'B' : 'b'; 
}

/**
 * calculatePossibleMoves: Bishop ki saari valid diagonal moves calculate karta hai.
 * Yeh function har turn ke baad board refresh karte waqt call hota hai.
 */
void Bishop::calculatePossibleMoves(bool checkSafety){
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::slidingMove(*board, this, checkSafety);
}