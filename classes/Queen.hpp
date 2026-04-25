#pragma once

#include "Piece.hpp"

class Board; // Forward declaration
class MoveGenerator; // Forward declaration

class Queen : public Piece {
private:
    friend class MoveGenerator; // Allow MoveGenerator to access private members of Queen
public:
    Queen(Pos p, PieceColor c, string name, Board* b);
    char getSymbol() override;
    int getValue() const override { return 9; }
    void calculatePossibleMoves(bool checkSafety = true) override;
};
