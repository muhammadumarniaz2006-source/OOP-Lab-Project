#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color { WHITE, BLACK };

struct Pos {
    int x;
    int y;
};

class Board; // Forward declaration

class Piece {
protected:
    Pos pos;
    Color color;
    Board* board;
    string name;

public:
    Piece(Color c) : color(c), board(nullptr) {}
    virtual ~Piece() {}

    virtual bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) = 0;

    Color getcolor() const {
        return color;
    }

    void setBoard(Board* b) {
        board = b;
    }
};
