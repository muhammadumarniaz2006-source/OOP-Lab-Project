#pragma once

#include "Piece.hpp"
#include "Board.hpp"

class Pawn : public Piece
{
public:
    Pawn(Pos p, Color c, string name, Board* b);
    char getSymbol() override;
    void calculatePossibleMoves() override;
};
