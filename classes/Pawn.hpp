#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c) {}
    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) override {
        // Basic Pawn logic placeholder
        return true;
    }
};
