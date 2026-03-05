#include "Board.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

Board::Board() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            squares[r][c] = nullptr;
        }
    }
}

Board::~Board() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            delete squares[r][c];
            squares[r][c] = nullptr;
        }
    }
}

void Board::initBoard() {
    for (int c = 0; c < 8; c++) {
        squares[1][c] = new Pawn(Color::BLACK);
        squares[1][c]->setBoard(this);
        squares[6][c] = new Pawn(Color::WHITE);
        squares[6][c]->setBoard(this);
    }
    squares[0][0] = new Rook(Color::BLACK); squares[0][0]->setBoard(this);
    squares[0][7] = new Rook(Color::BLACK); squares[0][7]->setBoard(this);
    squares[7][0] = new Rook(Color::WHITE); squares[7][0]->setBoard(this);
    squares[7][7] = new Rook(Color::WHITE); squares[7][7]->setBoard(this);
    
    squares[0][1] = new Knight(Color::BLACK); squares[0][1]->setBoard(this);
    squares[0][6] = new Knight(Color::BLACK); squares[0][6]->setBoard(this);
    squares[7][1] = new Knight(Color::WHITE); squares[7][1]->setBoard(this);
    squares[7][6] = new Knight(Color::WHITE); squares[7][6]->setBoard(this);
    
    squares[0][2] = new Bishop(Color::BLACK); squares[0][2]->setBoard(this);
    squares[0][5] = new Bishop(Color::BLACK); squares[0][5]->setBoard(this);
    squares[7][2] = new Bishop(Color::WHITE); squares[7][2]->setBoard(this);
    squares[7][5] = new Bishop(Color::WHITE); squares[7][5]->setBoard(this);
    
    squares[0][3] = new Queen(Color::BLACK); squares[0][3]->setBoard(this);
    squares[7][3] = new Queen(Color::WHITE); squares[7][3]->setBoard(this);
    
    squares[0][4] = new King(Color::BLACK); squares[0][4]->setBoard(this);
    squares[7][4] = new King(Color::WHITE); squares[7][4]->setBoard(this);
}

bool Board::isEmpty(int row, int col) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) { return false; }
    return squares[row][col] == nullptr;
}

bool Board::hasOpponent(int row, int col, Color myColor) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;

    Piece *target = squares[row][col];
    if (target == nullptr)
        return false;

    return (target->getcolor() != myColor);
}
