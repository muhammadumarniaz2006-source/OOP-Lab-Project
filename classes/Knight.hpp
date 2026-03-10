#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class ValidMove {
    protected:
        bool isPinned;
        vector<Pos> possibleMoves;
    public:
        ValidMove() : isPinned(false) {}
        void calculatePossibleMoves();
};

class Knight : public Piece {
public:
    ValidMove validMove;
    Knight(Color c) : Piece(c) {}
    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) override {
        // Basic Knight logic placeholder
        return true;
    }
};
