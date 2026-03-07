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
    pair<int,int>Possiblemove[28];//ismay hum dow integer value safe kersaktay hai aik index per aur size 28 isliay lia kio kay max possible move jo queen ki hoti hai wo 28 hoti hai
    int movecount=0;    //yai isliay use kia hai kio kay agay pssible kay array mai iski zarooorat paray gi like for increasing array index or etc

public:
Piece(){}
    Piece(Color c) : color(c), board(nullptr) {}
    virtual ~Piece() {}
   
    virtual bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) = 0;

    Color getcolor() const {
        return color;
    }

    void setBoard(Board* b) {
        board = b;
    }
     void generateMoves(int row,int col,Board& board);//yai move store karay ga aur next turn mai clear kerday ga
};
