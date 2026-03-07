#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Pawn : public Piece
{
private:
    bool first_move;
    bool move_two_square;

public:
   Pawn::Pawn(Color c):Piece(c)
{
    first_move=true;
    move_two_square=false;
}
    
    bool isvalidmove(int from_row,int from_col,int to_row, int to_col, Board &board);
};
