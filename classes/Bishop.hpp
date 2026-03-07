#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Bishop : public Piece {
public:
    Bishop(){}
    Bishop(Color c) : Piece(c) {}

    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) override;
};
