#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Rook : public Piece {
public:
    Rook(Pos p, Color c, string name, Board* b);
    char getSymbol() override;
    void calculatePossibleMoves() override;
};