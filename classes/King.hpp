#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class King : public Piece {
public:
    King(Pos p, Color c, string name, Board* b);
    char getSymbol() override;
    void calculatePossibleMoves() override;
};
