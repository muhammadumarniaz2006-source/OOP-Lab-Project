#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Rook : public Piece {
public:
    Rook(){}
    Rook(Color c) : Piece(c) {}

    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) override;

    char getsymbol();
};
