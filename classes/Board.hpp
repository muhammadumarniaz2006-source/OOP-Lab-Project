#pragma once

#include "Piece.hpp"

class Board {
public:
    Piece *squares[8][8];
    Color color;

    Board();
    ~Board();


    void initBoard();
    /*yai makemove piece ko move kernay kay liay hai aur undomove isliay banaya hai ager koi piecce check hoa tu undo move kerna hoga aur yai dono function game class handel karay gi */
    Piece* makeMove(int fr,int fc,int tr,int tc);
    void undoMove(int fr,int fc,int tr,int tc,Piece* capturedPiece);
    bool isEmpty(int row, int col) const;
    bool hasOpponent(int row, int col, Color myColor) const;
    void print_board();
};
