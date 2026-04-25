#pragma once

#include "Piece.hpp"

class Board; // Forward declaration

class King : public Piece {
private:
    friend class MoveGenerator;
public:
    King(Pos p, PieceColor c, string name, Board* b);
    char getSymbol() override;
    int getValue() const override { return 0; }
    void calculatePossibleMoves(bool checkSafety = true) override;
};
