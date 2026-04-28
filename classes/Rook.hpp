#pragma once

#include "Piece.hpp"

class Board; // Forward declaration
class MoveGenerator; // Forward declaration

class Rook : public Piece {
private:
    friend class MoveGenerator; // MoveGenerator ko Rook ke internals tak rasai deta hai
public:
    // Rook ka constructor
    Rook(Pos p, PieceColor c, string name, Board* b);
    // Rook ka symbol ('R'/'r') return karta hai
    char getSymbol() override;
    // Rook ki value (5) return karta hai
    int getValue() const override { return 5; }
    // Rook ki horizontal aur vertical moves calculate karta hai
    void calculatePossibleMoves(bool checkSafety = true) override;
};
