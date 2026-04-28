#pragma once

#include "Piece.hpp"

class Board; // Forward declaration
class MoveGenerator; // Forward declaration

class Knight : public Piece {
private:
    friend class MoveGenerator; // MoveGenerator ko Knight ke internals tak rasai deta hai
public:
    // Knight ka constructor
    Knight(Pos p, PieceColor c, string name, Board* b);
    // Knight ka symbol ('N'/'n') return karta hai
    char getSymbol() override;
    // Knight ki value (3) return karta hai
    int getValue() const override { return 3; }
    // Knight ki 'L' shaped moves calculate karta hai
    void calculatePossibleMoves(bool checkSafety = true) override;
};
