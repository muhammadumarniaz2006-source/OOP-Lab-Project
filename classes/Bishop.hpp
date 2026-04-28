#pragma once

#include "Piece.hpp"

class Board; // Forward declaration
class MoveGenerator; // Forward declaration

class Bishop : public Piece {
private:
    friend class MoveGenerator; // MoveGenerator ko Bishop ke internals tak rasai deta hai
public:
    // Bishop ka constructor jo initial position aur color set karta hai
    Bishop(Pos p, PieceColor c, string name, Board* b);
    // Bishop ka symbol ('B'/'b') return karta hai
    char getSymbol() override;
    // Bishop ki point value (3) return karta hai
    int getValue() const override { return 3; }
    // Bishop ki diagonal moves calculate karta hai
    void calculatePossibleMoves(bool checkSafety) override;
};
