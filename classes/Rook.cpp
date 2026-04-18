#include "Rook.hpp"
#include "Move.hpp"
/*Rook logic:
      row difference and col difference nikal ker dono ko check  karay gay
    if dono mai say koi aik bhi 0 hai  hai tu valid move hai aur ager destinated position per apna piece  na ho ya uskay rastay mai koi bhi dosra piece ho 
*/

Rook::Rook(Pos p, Color c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,0}, {0,1}, {-1,0}, {0,-1}}; //Rook ke possible directions
  calculatePossibleMoves();
}

char Rook::getSymbol(){ 
    return (getcolor() == Color::WHITE) ? 'R' : 'r'; 
}

void Rook::calculatePossibleMoves() {
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::slidingMove(*board, pos, color, Directions);
}