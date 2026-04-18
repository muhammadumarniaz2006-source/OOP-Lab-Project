#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Knight : public Piece {
public:
    Knight(Pos p, Color c, string name, Board* b);
    char getSymbol() override;
    void calculatePossibleMoves() override;
};
