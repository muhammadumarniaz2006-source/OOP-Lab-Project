#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Queen : public Piece {
public:
    Queen(Color c) : Piece(c) {}
    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) override {
        // Basic Queen logic placeholder
        return true;
    }
    string getsymbol();
};
