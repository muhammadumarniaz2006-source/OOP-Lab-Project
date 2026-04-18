#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color { WHITE, BLACK };

struct Pos {
    int x;
    int y;
    Pos(int x = 0, int y = 0) : x(x), y(y) {}
};

//Direction ke liye struct for example (1, 1) se x-forward and y-forward. And -ve ka matlab backward;
typedef struct {
    int x;  
    int y;
} Dir;

class Board; // Forward declaration

class Piece {
protected:
    Pos pos;
    Color color;
    Board* board;
    string name;
    vector<Dir> Directions;
    vector<Pos> Possiblemoves; //ismay hum dow integer value safe kersaktay hai aik index per aur size 28 isliay lia kio kay max possible move jo queen ki hoti hai wo 28 hoti hai
    bool ifFirstMove = true;    //yai isliay use kia hai kio kay agay pssible kay array mai iski zarooorat paray gi like for increasing array index or etc

public:
    Piece(Pos p, Color c, string name, Board* b);
    virtual ~Piece() {}
    virtual bool isValidMove(Pos newMove);
    virtual char getSymbol() = 0;
    virtual void calculatePossibleMoves() = 0;
    void updatePos(Pos p);
    Color getcolor() const;
    void setBoard(Board* b);
    string getName();

    // void debugPrintPossibleMoves() const; // Debug function to print possible moves
};
