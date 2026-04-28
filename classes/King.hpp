#pragma once

#include "Piece.hpp"

class Board; // Forward declaration

class King : public Piece {
private:
    friend class MoveGenerator; // MoveGenerator ko King ke internals tak rasai deta hai
public:
    // King ka constructor
    King(Pos p, PieceColor c, string name, Board* b);
    // King ka symbol ('K'/'k') return karta hai
    char getSymbol() override;
    // King ki value return karta hai
    int getValue() const override { return 0; }
    // King ki 1-step aur castling moves calculate karta hai
    void calculatePossibleMoves(bool checkSafety = true) override;
};
