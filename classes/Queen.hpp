#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Queen : public Piece{
public:
    Queen(Pos p, Color c, string name, Board* b);
    char getSymbol() override;
    void calculatePossibleMoves() override;
};