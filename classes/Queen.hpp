#pragma once

#include "Piece.hpp"

class Board; // Forward declaration
class MoveGenerator; // Forward declaration

class Queen : public Piece {
private:
    friend class MoveGenerator; // MoveGenerator ko Queen ke internals tak rasai deta hai
public:
    // Queen ka constructor
    Queen(Pos p, PieceColor c, string name, Board* b);
    // Queen ka symbol ('Q'/'q') return karta hai
    char getSymbol() override;
    // Queen ki value (9) return karta hai
    int getValue() const override { return 9; }
    // Queen ki sliding moves (diagonal aur straight) calculate karta hai
    void calculatePossibleMoves(bool checkSafety = true) override;
};
