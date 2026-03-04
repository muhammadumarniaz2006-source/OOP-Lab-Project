#include "Piece.hpp"
#include<iosteam>

using namespace std;

class Board{
public:
    Piece *squares[8][8];
    Color color;
    Board(){
        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                squares[r][c] = nullptr;
            }
        }
    }
    ~Board(){
        for (int r = 0; r < 8; r++){
            for (int c = 0; c < 8; c++){
                delete squares[r][c];
                squares[r][c] = nullptr;
            }
        }
    }

    void initBoard(){
        for (int c = 0; c < 8; c++){
            squares[1][c] = new Pawn(Color::BLACK);
            squares[6][c] = new Pawn(Color::WHITE);
        }
        squares[0][0] = new Rook(Color::BLACK);
        squares[0][7] = new Rook(Color::BLACK);
        squares[7][0] = new Rook(Color::WHITE);
        squares[7][7] = new Rook(Color::WHITE);
        squares[0][1] = new Knight(Color::BLACK);
        squares[0][6] = new Knight(Color::BLACK);
        squares[7][1] = new Knight(Color::WHITE);
        squares[7][6] = new Knight(Color::WHITE);
        squares[0][2] = new Bishop(Color::BLACK);
        squares[0][5] = new Bishop(Color::BLACK);
        squares[7][2] = new Bishop(Color::WHITE);
        squares[7][5] = new Bishop(Color::WHITE);
        squares[0][3] = new Queen(Color::BLACK);
        squares[7][3] = new Queen(Color::WHITE);
        squares[0][4] = new King(Color::BLACK);
        squares[7][4] = new King(Color::WHITE);
    }

    bool isEmpty(int row, int col){
        if (row < 0 || row >= 8 || col < 0 || col >= 8) { return false; }
        return squares[row][col] == nullptr;
    }

    bool hasOpponent(int row, int col, Color myColor)
    {

        if (row < 0 || row >= 8 || col < 0 || col >= 8)
            return false;

        Piece *target = squares[row][col];

        if (target == nullptr)
            return false;

        return (target->getcolor() != myColor);
    }
};