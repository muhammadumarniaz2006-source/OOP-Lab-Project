#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Bishop : public Piece {
public:
    Bishop(Pos p, Color c, string name, Board* b);
    char getSymbol() override;
    void calculatePossibleMoves() override;
};
