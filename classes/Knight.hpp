#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Knight : public Piece {
public:
    Knight(Color c) : Piece(c) {}
    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) override {
        // Basic Knight logic placeholder
        return true;
    }
};
