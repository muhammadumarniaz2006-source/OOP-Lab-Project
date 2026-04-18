#pragma once

#include "Piece.hpp"

class Board {
private:
    Piece *squares[8][8];
    vector<Piece*> sidePieces; // captured pieces ko store karnay kay liay vector banaya hai.
public:
    Board();
    ~Board();
    void initBoard();
    /*yai makemove piece ko move kernay kay liay hai aur undomove isliay banaya hai ager koi piecce check hoa tu undo move kerna hoga aur yai dono function game class handel karay gi */
    bool makeMove(Pos from, Pos to, Color currentTurn);
    bool isEmpty(Pos pos) const;
    bool hasOpponent(Pos pos, Color myColor) const;
    bool hasMate(Pos pos, Color myColor) const;
    bool checkBoundary(Pos pos) const;
    void recalculateAllMoves();
    void print_board();
};
