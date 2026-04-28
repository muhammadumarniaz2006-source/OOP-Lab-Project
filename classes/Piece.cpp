#include "Piece.hpp"

// Constructor: Piece ki initial state set karta hai.
Piece::Piece(Pos p, PieceColor c, string name, Board *b) : color(c), board(b){
  pos = p;
  this->name = name;
}

// Pos structure ka constructor.
Pos::Pos(int x, int y) : x(x), y(y) {}

// Comparison operator: check karta hai ke do positions barabar hain ya nahi.
bool Pos::operator==(const Pos &pos) const{
  return (this->x == pos.x && this->y == pos.y);
}

// Color enum ko string mein convert karta hai (display ke liye).
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

// Piece ka color return karta hai.
PieceColor Piece::getcolor() const{
  return color;
}

// Check karta hai ke destination valid hai ya nahi.
bool Piece::isValidMove(Pos newMove){
  for (auto pMove : Possiblemoves){
    if (newMove.x == pMove.x && newMove.y == pMove.y){
      return true;
    }
  }
  return false;
}

// Piece ki position update karta hai aur 'first move' flag handle karta hai.
void Piece::updatePos(Pos p, bool suppressFirstMoveChange){
  pos = p;
  if (!suppressFirstMoveChange && ifFirstMove){
    ifFirstMove = false;
  }
}

// Piece ka naam return karta hai.
string Piece::getName(){
  return name;
}

// Board set karta hai.
void Piece::setBoard(Board *b){
  board = b;
}

// Moves ka list return karta hai.
vector<Pos> Piece::getPossibleMoves() const{
  return Possiblemoves;
}

// Console par possible moves print karta hai (debugging).
void Piece::debugPrintPossibleMoves() const{
  cout << "Possible moves for " << name << " (" << pos.x << "," << pos.y << "): ";
  for (auto move : Possiblemoves)
  {
    cout << "(" << move.x << ", " << move.y << ") ";
  }
  cout << endl;
}

// Current position return karta hai.
Pos Piece::getPos() const{
  return pos;
}

// Yeh function isliye hai takay humein pata chal sakay ke piece ne pehli move kar li hai ya nahi
bool Piece::isFirstMove() const {
    return ifFirstMove;
}

// Game load karte waqt piece ki 'first move' wali state set karne ke liye.
void Piece::setFirstMove(bool val) {
    ifFirstMove = val;
}