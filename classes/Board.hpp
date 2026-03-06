#pragma once

#include "Piece.hpp"

class Board {
public:
    Piece *squares[8][8];
    Color color;

    Board();
    ~Board();

    void initBoard();
    bool isEmpty(int row, int col) const;
    bool hasOpponent(int row, int col, Color myColor) const;
};
