#include "Piece.hpp"

Piece::Piece(Pos p, PieceColor c, string name, Board *b) : color(c), board(b){
  pos = p;
  this->name = name;
}

Pos::Pos(int x, int y) : x(x), y(y) {}

bool Pos::operator==(const Pos &pos) const{
  return (this->x == pos.x && this->y == pos.y);
}

string colorToString(PieceColor color){
  switch (color){
    case PieceColor::BLACK_PIECE:
      return "BLACK";
    case PieceColor::WHITE_PIECE:
      return "WHITE";
    default:
      return "None";
  }
}

PieceColor Piece::getcolor() const{
  return color;
}

bool Piece::isValidMove(Pos newMove){
  for (auto pMove : Possiblemoves){
    if (newMove.x == pMove.x && newMove.y == pMove.y){
      return true;
    }
  }
  return false;
}

void Piece::updatePos(Pos p, bool suppressFirstMoveChange){
  pos = p;
  if (!suppressFirstMoveChange && ifFirstMove){
    ifFirstMove = false;
  }
}

string Piece::getName(){
  return name;
}

void Piece::setBoard(Board *b){
  board = b;
}

vector<Pos> Piece::getPossibleMoves() const{
  return Possiblemoves;
}

void Piece::debugPrintPossibleMoves() const{
  cout << "Possible moves for " << name << " (" << pos.x << "," << pos.y << "): ";
  for (auto move : Possiblemoves)
  {
    cout << "(" << move.x << ", " << move.y << ") ";
  }
  cout << endl;
}

Pos Piece::getPos() const{
  return pos;
}

// Yeh function isliye hai takay humein pata chal sakay ke piece ne pehli move kar li hai ya nahi
// Takay game load karte waqt rules (jesay pawn double move) sahi se kaam karein
bool Piece::isFirstMove() const {
    return ifFirstMove;
}

// Yeh function game load karte waqt piece ki 'first move' wali state wapis set karne ke liye hai
void Piece::setFirstMove(bool val) {
    ifFirstMove = val;
}