#pragma once

#include "Piece.hpp"
#include "Board.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"

class Queen : public Piece ,public Bishop,public Rook{
public:
    Queen(Color c) : Piece(c),Bishop(c),Rook(c){}
    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) override {
        // Basic Queen logic placeholder
        return true;
    }
    char getsymbol();
};
