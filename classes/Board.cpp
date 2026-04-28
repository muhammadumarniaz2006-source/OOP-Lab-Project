#include "Board.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Move.hpp"
#include <iostream>

// Board ka constructor: squares array ko null se initialize karta hai.
Board::Board() : enPassantTarget(-1, -1) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = nullptr;
        }
    }
}

// Destructor: pieces aur captured pieces ki memory delete karta hai takay memory leak na ho.
Board::~Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]) delete squares[i][j];
        }
    }
    for (Piece* p : sidePieces) delete p;
}

// initBoard: Purane pieces clear karke Chess ke standard arrangement ke mutabiq naye pieces lagata hai.
void Board::initBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]) delete squares[i][j];
            squares[i][j] = nullptr;
        }
    }
    for (Piece* p : sidePieces) delete p;
    sidePieces.clear();
    enPassantTarget = Pos(-1, -1);

    // Black Pieces (Rank 0 aur 1)
    squares[0][0] = new Rook(Pos(0, 0), PieceColor::BLACK_PIECE, "r", this);
    squares[0][1] = new Knight(Pos(0, 1), PieceColor::BLACK_PIECE, "n", this);
    squares[0][2] = new Bishop(Pos(0, 2), PieceColor::BLACK_PIECE, "b", this);
    squares[0][3] = new Queen(Pos(0, 3), PieceColor::BLACK_PIECE, "q", this);
    squares[0][4] = new King(Pos(0, 4), PieceColor::BLACK_PIECE, "k", this);
    squares[0][5] = new Bishop(Pos(0, 5), PieceColor::BLACK_PIECE, "b", this);
    squares[0][6] = new Knight(Pos(0, 6), PieceColor::BLACK_PIECE, "n", this);
    squares[0][7] = new Rook(Pos(0, 7), PieceColor::BLACK_PIECE, "r", this);
    for (int i = 0; i < 8; i++) squares[1][i] = new Pawn(Pos(1, i), PieceColor::BLACK_PIECE, "p", this);

    // White Pieces (Rank 6 aur 7)
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

// checkBoundary: Ensure karta hai ke position board (0-7) ke andar hi hai.
bool Board::checkBoundary(Pos pos) const {
    return pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8;
}

// isEmpty: Batata hai ke square par koi piece hai ya nahi.
bool Board::isEmpty(Pos pos) const {
    if (!checkBoundary(pos)) return false;
    return squares[pos.x][pos.y] == nullptr;
}

// hasOpponent: Check karta hai ke square par dushman ka piece hai ya nahi.
bool Board::hasOpponent(Pos pos, PieceColor myColor) const {
    if (!checkBoundary(pos) || squares[pos.x][pos.y] == nullptr) return false;
    return squares[pos.x][pos.y]->getcolor() != myColor;
}

// hasMate: Check karta hai ke square par apna (friendly) piece hai ya nahi.
bool Board::hasMate(Pos pos, PieceColor myColor) const {
    if (!checkBoundary(pos) || squares[pos.x][pos.y] == nullptr) return false;
    return squares[pos.x][pos.y]->getcolor() == myColor;
}

// recalculateAllMoves: Board par maujood har piece ki legal moves dobara calculate karta hai.
void Board::recalculateAllMoves() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]) squares[i][j]->calculatePossibleMoves(true);
        }
    }
}

// promotePawn: Pawn ko hata kar user ki pasand ka naya piece (Queen, Rook, etc.) lagata hai.
void Board::promotePawn(Pos pos, char targetSymbol) {
    if (!checkBoundary(pos) || !squares[pos.x][pos.y]) return;
    PieceColor color = squares[pos.x][pos.y]->getcolor();
    delete squares[pos.x][pos.y];
    
    char lowerSym = tolower(targetSymbol);
    if (lowerSym == 'q') squares[pos.x][pos.y] = new Queen(pos, color, color == PieceColor::WHITE_PIECE ? "Q" : "q", this);
    else if (lowerSym == 'r') squares[pos.x][pos.y] = new Rook(pos, color, color == PieceColor::WHITE_PIECE ? "R" : "r", this);
    else if (lowerSym == 'b') squares[pos.x][pos.y] = new Bishop(pos, color, color == PieceColor::WHITE_PIECE ? "B" : "b", this);
    else if (lowerSym == 'n') squares[pos.x][pos.y] = new Knight(pos, color, color == PieceColor::WHITE_PIECE ? "N" : "n", this);
    recalculateAllMoves();
}

// makeMove: Asli Chess rules ke mutabiq piece ko move karta hai (Castling aur En Passant handle karta hai).
bool Board::makeMove(Pos from, Pos to, PieceColor turn) {
    Piece* p = squares[from.x][from.y];
    if (p == nullptr || p->getcolor() != turn) return false;

    // Verify if move is legal
    bool valid = false;
    for (auto m : p->getPossibleMoves()) {
        if (m == to) { valid = true; break; }
    }
    if (!valid) return false;

    // Special Case: Castling Execution (King aur Rook dono move hote hain).
    if (tolower(p->getSymbol()) == 'k' && abs(to.y - from.y) == 2) {
        int r = from.x;
        if (to.y == 6) { // King-side Short
            Piece* rook = squares[r][7];
            squares[r][5] = rook; squares[r][7] = nullptr;
            rook->updatePos(Pos(r, 5));
        } else if (to.y == 2) { // Queen-side Long
            Piece* rook = squares[r][0];
            squares[r][3] = rook; squares[r][0] = nullptr;
            rook->updatePos(Pos(r, 3));
        }
    }

    // Special Case: En Passant Capture Execution (Pawn diagonal move hota hai par capture samne wala hota hai).
    if (tolower(p->getSymbol()) == 'p' && to == enPassantTarget) {
        int capturedX = from.x;
        int capturedY = to.y;
        if (squares[capturedX][capturedY]) {
            sidePieces.push_back(squares[capturedX][capturedY]);
            squares[capturedX][capturedY] = nullptr;
        }
    }

    // Normal Capture: Agar target par koi piece hai toh usay sidePieces mein daal do.
    if (squares[to.x][to.y]) {
        sidePieces.push_back(squares[to.x][to.y]);
        squares[to.x][to.y] = nullptr;
    }

    // Set new En Passant target if pawn moves 2 steps (agle turn ke liye).
    enPassantTarget = Pos(-1, -1);
    if (tolower(p->getSymbol()) == 'p' && abs(to.x - from.x) == 2) {
        enPassantTarget = Pos((from.x + to.x) / 2, from.y);
    }

    // Move Piece: Asli move yahan hoti hai.
    squares[to.x][to.y] = p;
    squares[from.x][from.y] = nullptr;
    p->updatePos(to);
    
    recalculateAllMoves();
    return true;
}

// isSquareAttacked: Check karta hai ke kya koi dushman piece is square par hamla kar sakta hai.
bool Board::isSquareAttacked(Pos targetPos, PieceColor attackerColor) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = squares[i][j];
            if (p && p->getcolor() == attackerColor) {
                // Raw attack range calculate karte hain (without pin check).
                vector<Pos> attacks;
                char sym = tolower(p->getSymbol());
                if (sym == 'p') attacks = MoveGenerator::pawnMove(*this, (Pawn*)p, false);
                else if (sym == 'n') attacks = MoveGenerator::knightMove(*this, (Knight*)p, false);
                else if (sym == 'k') attacks = MoveGenerator::kingMove(*this, *(King*)p, false);
                else attacks = MoveGenerator::slidingMove(*this, p, false);
                
                for (auto m : attacks) {
                    if (m == targetPos) return true;
                }
            }
        }
    }
    return false;
}

// isCheck: Batata hai ke kya diye gaye color ka King khatre mein (check) hai.
bool Board::isCheck(PieceColor color) {
    Pos kingPos = getKingPos(color);
    if (kingPos.x == -1) return false;
    PieceColor opponent = (color == PieceColor::WHITE_PIECE ? PieceColor::BLACK_PIECE : PieceColor::WHITE_PIECE);
    return isSquareAttacked(kingPos, opponent);
}

// checkPin: Ek move simulate karke check karta hai ke kya yeh move karne se King check mein aa jayega.
bool Board::checkPin(Piece* piece, Pos move) {
    Pos originalPos = piece->getPos();
    Piece* captured = squares[move.x][move.y];
    
    // Simulate move (temporarily move piece on board).
    squares[move.x][move.y] = piece;
    squares[originalPos.x][originalPos.y] = nullptr;
    piece->updatePos(move, true); 
    
    bool result = isCheck(piece->getcolor());
    
    // Revert move (piece ko wapis purani jagah rakh do).
    squares[originalPos.x][originalPos.y] = piece;
    squares[move.x][move.y] = captured;
    piece->updatePos(originalPos, true);
    
    return result;
}

// kingCheckValidation: King ki move validate karne ke liye checkPin ka istemal karta hai.
bool Board::kingCheckValidation(King& king, Pos move) {
    return checkPin(&king, move);
}

// getKingPos: Poore board par dhoondta hai ke King kahan khada hai.
Pos Board::getKingPos(PieceColor color) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = squares[i][j];
            if (p && tolower(p->getSymbol()) == 'k' && p->getcolor() == color) {
                return Pos(i, j);
            }
        }
    }
    return Pos(-1, -1);
}

// hasLegalMoves: Check karta hai ke kya player ke paas koi bhi valid move bachi hai.
bool Board::hasLegalMoves(PieceColor color) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = squares[i][j];
            if (p && p->getcolor() == color) {
                p->calculatePossibleMoves(true);
                if (!p->getPossibleMoves().empty()) return true;
            }
        }
    }
    return false;
}

// isCheckMate: Agar King check mein hai aur koi legal move nahi bachi, toh yeh Checkmate hai.
bool Board::isCheckMate(PieceColor color) {
    return isCheck(color) && !hasLegalMoves(color);
}

// isStaleMate: Agar King check mein nahi hai par koi move bhi nahi bachi, toh game draw (Stalemate) hai.
bool Board::isStaleMate(PieceColor color) {
    return !isCheck(color) && !hasLegalMoves(color);
}

// getWhiteScore: White player ke captured pieces ke total points return karta hai.
int Board::getWhiteScore() const {
    int score = 0;
    for (Piece* p : sidePieces) if (p->getcolor() == PieceColor::BLACK_PIECE) score += p->getValue();
    return score;
}

// getBlackScore: Black player ke captured pieces ke total points return karta hai.
int Board::getBlackScore() const {
    int score = 0;
    for (Piece* p : sidePieces) if (p->getcolor() == PieceColor::WHITE_PIECE) score += p->getValue();
    return score;
}

// toFEN: Board ki state ko FEN string mein convert karta hai (Stockfish AI ke liye zaroori hai).
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
