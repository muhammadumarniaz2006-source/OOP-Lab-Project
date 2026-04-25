#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Common.hpp"

using namespace std;

class Board; // Forward declaration

class Piece {
protected:
    Pos pos;
    PieceColor color;
    Board* board;
    string name;
    vector<Dir> Directions;
    vector<Pos> Possiblemoves; 
    bool ifFirstMove = true;    
    bool isPinned = false;
    friend class MoveGenerator; // Allow MoveGenerator to access private members of Piece
public:
    Piece(Pos p, PieceColor c, string name, Board* b);
    virtual ~Piece() {}
    virtual bool isValidMove(Pos newMove);
    virtual char getSymbol() = 0;
    virtual int getValue() const = 0;
    virtual void calculatePossibleMoves(bool checkSafety = true) = 0;
    void updatePos(Pos p, bool suppressFirstMoveChange = false);
    PieceColor getcolor() const;
    void setBoard(Board* b);
    string getName();
    Pos getPos() const;
    bool isFirstMove() const;
    void setFirstMove(bool val);
    vector<Pos> getPossibleMoves() const;
    void debugPrintPossibleMoves() const; 
};
