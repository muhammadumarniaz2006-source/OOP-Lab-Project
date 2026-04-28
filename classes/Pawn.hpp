#pragma once

#include "Piece.hpp"

class Board; // Forward declaration
class MoveGenerator; // Forward declaration

class Pawn : public Piece {
private:
    friend class MoveGenerator; // MoveGenerator ko Pawn ke internals tak rasai deta hai
public:
    // Pawn ka constructor
    Pawn(Pos p, PieceColor c, string name, Board* b);
    // Pawn ka symbol ('P'/'p') return karta hai
    char getSymbol() override;
    // Pawn ki value (1) return karta hai
    int getValue() const override { return 1; }
    // Pawn ki sidhi moves aur diagonal captures calculate karta hai
    void calculatePossibleMoves(bool checkSafety = true) override;
};
