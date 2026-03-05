#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class King : public Piece {
public:
    King(Color c) : Piece(c) {}
    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) override {
        // Basic King logic placeholder
        return true;
    }
};
