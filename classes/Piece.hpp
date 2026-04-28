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
    // Piece ka constructor jo position, color, naam aur board set karta hai.
    Piece(Pos p, PieceColor c, string name, Board* b);
    virtual ~Piece() {}
    // Check karta hai ke di gayi move valid moves ki list mein hai ya nahi.
    virtual bool isValidMove(Pos newMove);
    // Piece ka symbol return karta hai (maslan 'P' for Pawn).
    virtual char getSymbol() = 0;
    // Piece ki value return karta hai (maslan Pawn=10, Queen=90).
    virtual int getValue() const = 0;
    // Har piece ki apni moves calculate karne ka function.
    virtual void calculatePossibleMoves(bool checkSafety = true) = 0;
    // Piece ki position update karta hai.
    void updatePos(Pos p, bool suppressFirstMoveChange = false);
    // Piece ka color (White/Black) return karta hai.
    PieceColor getcolor() const;
    // Board ka pointer set karta hai.
    void setBoard(Board* b);
    // Piece ka naam return karta hai.
    string getName();
    // Maujooda position return karta hai.
    Pos getPos() const;
    // Kya piece ne pehli move kar li hai?
    bool isFirstMove() const;
    // First move ki state manually set karne ke liye (loading ke liye).
    void setFirstMove(bool val);
    // Calculate ki hui possible moves ka vector return karta hai.
    vector<Pos> getPossibleMoves() const;
    // Debugging ke liye moves console par print karta hai.
    void debugPrintPossibleMoves() const; 
};
