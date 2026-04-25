#include "Rook.hpp"
#include "Board.hpp"
#include "Move.hpp"
/*Rook logic:
      row difference and col difference nikal ker dono ko check  karay gay
    if dono mai say koi aik bhi 0 hai  hai tu valid move hai aur ager destinated position per apna piece  na ho ya uskay rastay mai koi bhi dosra piece ho 
*/

Rook::Rook(Pos p, PieceColor c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{1,0}, {0,1}, {-1,0}, {0,-1}}; //Rook ke possible directions
}

char Rook::getSymbol(){ 
    return (getcolor() == PieceColor::WHITE_PIECE) ? 'R' : 'r'; 
}

void Rook::calculatePossibleMoves(bool checkSafety) {
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::slidingMove(*board, this, checkSafety);
}