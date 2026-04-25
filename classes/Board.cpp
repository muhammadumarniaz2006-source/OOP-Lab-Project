#include "Board.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include <iostream>

Board::Board() : enPassantTarget(-1, -1) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = nullptr;
        }
    }
}

Board::~Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]) delete squares[i][j];
        }
    }
    for (Piece* p : sidePieces) delete p;
}

void Board::initBoard() {
    // Clear existing
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]) delete squares[i][j];
            squares[i][j] = nullptr;
        }
    }
    for (Piece* p : sidePieces) delete p;
    sidePieces.clear();

    // Black Pieces
    squares[0][0] = new Rook(Pos(0, 0), PieceColor::BLACK_PIECE, "r", this);
    squares[0][1] = new Knight(Pos(0, 1), PieceColor::BLACK_PIECE, "n", this);
    squares[0][2] = new Bishop(Pos(0, 2), PieceColor::BLACK_PIECE, "b", this);
    squares[0][3] = new Queen(Pos(0, 3), PieceColor::BLACK_PIECE, "q", this);
    squares[0][4] = new King(Pos(0, 4), PieceColor::BLACK_PIECE, "k", this);
    squares[0][5] = new Bishop(Pos(0, 5), PieceColor::BLACK_PIECE, "b", this);
    squares[0][6] = new Knight(Pos(0, 6), PieceColor::BLACK_PIECE, "n", this);
    squares[0][7] = new Rook(Pos(0, 7), PieceColor::BLACK_PIECE, "r", this);
    for (int i = 0; i < 8; i++) squares[1][i] = new Pawn(Pos(1, i), PieceColor::BLACK_PIECE, "p", this);

    // White Pieces
    for (int i = 0; i < 8; i++) squares[6][i] = new Pawn(Pos(6, i), PieceColor::WHITE_PIECE, "P", this);
    squares[7][0] = new Rook(Pos(7, 0), PieceColor::WHITE_PIECE, "R", this);
    squares[7][1] = new Knight(Pos(7, 1), PieceColor::WHITE_PIECE, "N", this);
    squares[7][2] = new Bishop(Pos(7, 2), PieceColor::WHITE_PIECE, "B", this);
    squares[7][3] = new Queen(Pos(7, 3), PieceColor::WHITE_PIECE, "Q", this);
    squares[7][4] = new King(Pos(7, 4), PieceColor::WHITE_PIECE, "K", this);
    squares[7][5] = new Bishop(Pos(7, 5), PieceColor::WHITE_PIECE, "B", this);
    squares[7][6] = new Knight(Pos(7, 6), PieceColor::WHITE_PIECE, "N", this);
    squares[7][7] = new Rook(Pos(7, 7), PieceColor::WHITE_PIECE, "R", this);

    recalculateAllMoves();
}

bool Board::checkBoundary(Pos pos) const {
    return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;
}

bool Board::isEmpty(Pos pos) const {
    if (!checkBoundary(pos)) return false;
    return squares[pos.x][pos.y] == nullptr;
}

bool Board::hasOpponent(Pos pos, PieceColor myColor) const {
    if (!checkBoundary(pos) || squares[pos.x][pos.y] == nullptr) return false;
    return squares[pos.x][pos.y]->getcolor() != myColor;
}

bool Board::hasMate(Pos pos, PieceColor myColor) const {
    if (!checkBoundary(pos) || squares[pos.x][pos.y] == nullptr) return false;
    return squares[pos.x][pos.y]->getcolor() == myColor;
}

void Board::recalculateAllMoves() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]) {
                squares[i][j]->calculatePossibleMoves();
            }
        }
    }
}

void Board::promotePawn(Pos pos, char targetSymbol) {
    if (!checkBoundary(pos)) return;
    PieceColor color = squares[pos.x][pos.y]->getcolor();
    delete squares[pos.x][pos.y];
    
    char lowerSym = tolower(targetSymbol);
    if (lowerSym == 'q') squares[pos.x][pos.y] = new Queen(pos, color, color == PieceColor::WHITE_PIECE ? "Q" : "q", this);
    else if (lowerSym == 'r') squares[pos.x][pos.y] = new Rook(pos, color, color == PieceColor::WHITE_PIECE ? "R" : "r", this);
    else if (lowerSym == 'b') squares[pos.x][pos.y] = new Bishop(pos, color, color == PieceColor::WHITE_PIECE ? "B" : "b", this);
    else if (lowerSym == 'n') squares[pos.x][pos.y] = new Knight(pos, color, color == PieceColor::WHITE_PIECE ? "N" : "n", this);
}

bool Board::makeMove(Pos from, Pos to, PieceColor turn) {
    Piece* p = squares[from.x][from.y];
    if (p == nullptr || p->getcolor() != turn) return false;

    bool valid = false;
    for (auto m : p->getPossibleMoves()) {
        if (m == to) { valid = true; break; }
    }
    if (!valid) return false;

    // Capture
    if (squares[to.x][to.y]) {
        sidePieces.push_back(squares[to.x][to.y]);
        squares[to.x][to.y] = nullptr;
    }

    squares[to.x][to.y] = p;
    squares[from.x][from.y] = nullptr;
    p->updatePos(to);
    
    recalculateAllMoves();
    return true;
}

bool Board::checkPin(Piece* piece, Pos move) { return false; }
bool Board::isSquareAttacked(Pos targetPos, PieceColor attackerColor) { return false; }
bool Board::isCheck(PieceColor color) { return false; }
bool Board::kingCheckValidation(King& king, Pos move) { return false; }

int Board::getWhiteScore() const {
    int score = 0;
    for (Piece* p : sidePieces) {
        if (p->getcolor() == PieceColor::BLACK_PIECE) {
            score += p->getValue();
        }
    }
    return score;
}

int Board::getBlackScore() const {
    int score = 0;
    for (Piece* p : sidePieces) {
        if (p->getcolor() == PieceColor::WHITE_PIECE) {
            score += p->getValue();
        }
    }
    return score;
}
void Board::popCapturedPiece() {}
void Board::recalculateAllMovesExceptKing() {}
void Board::print_board() {}
Pos Board::getKingPos(PieceColor color) const { return Pos(0,0); }
bool Board::isCheckMate(PieceColor color) { return false; }
bool Board::isStaleMate(PieceColor color) { return false; }
bool Board::isInsufficientMaterial() const { return false; }
bool Board::hasLegalMoves(PieceColor color) { return true; }
std::string Board::getBoardState() const { return ""; }

std::string Board::toFEN(PieceColor turn) const {
    std::string fen = "";
    for (int r = 0; r < 8; r++) {
        int emptyCount = 0;
        for (int c = 0; c < 8; c++) {
            Piece* p = squares[r][c];
            if (p == nullptr) emptyCount++;
            else {
                if (emptyCount > 0) { fen += std::to_string(emptyCount); emptyCount = 0; }
                fen += p->getSymbol();
            }
        }
        if (emptyCount > 0) fen += std::to_string(emptyCount);
        if (r < 7) fen += "/";
    }
    fen += (turn == PieceColor::WHITE_PIECE ? " w " : " b ");
    fen += "- - 0 1";
    return fen;
}
