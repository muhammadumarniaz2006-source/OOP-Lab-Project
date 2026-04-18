#include "Piece.hpp"
 
Piece::Piece(Pos p, Color c, string name, Board* b) : color(c), board(b) {
  pos = p;
  this->name = name;
}

Color Piece::getcolor() const {
    return color;
}

bool Piece::isValidMove(Pos newMove){
  for(auto pMove: Possiblemoves){
    if(newMove.x == pMove.x && newMove.y == pMove.y){
      return true;
    }
  }
  return false;
}

void Piece::updatePos(Pos p){
  pos = p;
  if(ifFirstMove){
    ifFirstMove = false;
  }
}

string Piece::getName(){
  return name;
}

void Piece::setBoard(Board* b) {
    board = b;
}

// void Piece::debugPrintPossibleMoves() const {
//     cout << "Possible moves for " << name << " (" << pos.x << "," << pos.y << "): ";
//     for (int i = 0; i < Possiblemoves.size(); i++) {
//         Pos move = Possiblemoves[i];
//         cout << "(" << move.x << ", " << move.y << ") ";
//     }
//     cout << endl;
// }