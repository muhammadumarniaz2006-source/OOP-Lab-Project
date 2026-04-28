#include "Knight.hpp"
#include "Board.hpp"
#include "Move.hpp"

/**
 * Knight: Ghoray (Knight) ka object banata hai aur iski unique 'L' shaped directions define karta hai.
 * Game initialization ya pawn promotion ke waqt call hota hai.
 */
Knight::Knight(Pos p, PieceColor c, string name, Board* b): Piece(p, c, name, b) {
  Directions = {{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}}; 
  //Knight ke possible directions, knight ke moves L shape mai hotay hai is liye 2 aur 1 ka combination use kia hai
}

/**
 * getSymbol: Knight ka unique symbol return karta hai ('N' for white, 'n' for black).
 * Stockfish AI aur saving logic mein piece ki pehchan ke liye istemal hota hai.
 */
char Knight::getSymbol(){
  return (getcolor() == PieceColor::WHITE_PIECE) ? 'N' : 'n'; 
}

/**
 * calculatePossibleMoves: Ghoray ki saari mumkin 'L' moves check karta hai.
 * Board par har move ke baad pieces ki moves refresh karne ke liye call hota hai.
 */
void Knight::calculatePossibleMoves(bool checkSafety) {
  Possiblemoves.clear();
  Possiblemoves = MoveGenerator::knightMove(*board, this, checkSafety);
}