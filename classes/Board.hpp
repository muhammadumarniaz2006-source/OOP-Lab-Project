#pragma once
#include "Piece.hpp"

class King; // Forward declaration

class Board {
private:
    Piece* squares[8][8];
    vector<Piece*> sidePieces; // captured pieces ko store karnay kay liay vector banaya hai.
public:
    // Board ka constructor jo squares ko initialize karta hai.
    Board();
    // Destructor: pieces aur vectors ko memory se clear karta hai.
    ~Board();
    // Pieces ko unki starting positions par set karta hai.
    void initBoard();
    // Di gayi position se destination tak move perform karta hai (Special moves samait).
    bool makeMove(Pos from, Pos to, PieceColor currentTurn);
    // Check karta hai ke square khali hai ya nahi.
    bool isEmpty(Pos pos) const;
    // Check karta hai ke square par dushman piece hai ya nahi.
    bool hasOpponent(Pos pos, PieceColor myColor) const;
    // Check karta hai ke square par apna hi piece hai ya nahi.
    bool hasMate(Pos pos, PieceColor myColor) const;
    // Check karta hai ke coordinates board ke andar hain ya nahi.
    bool checkBoundary(Pos pos) const;
    // Board ke tamam pieces ki moves calculate karta hai.
    void recalculateAllMoves();
    void recalculateAllMovesExceptKing();
    void print_board();
    // Diye gaye color ke King ki position dhoondta hai.
    Pos getKingPos(PieceColor color) const;
    
    // Captured pieces ke points calculate karta hai.
    int getWhiteScore() const;
    int getBlackScore() const;
    void popCapturedPiece();
    
    // En Passant target square ki location.
    Pos enPassantTarget;

    // Pawn ko promotion piece mein tabdeel karta hai.
    void promotePawn(Pos pos, char targetSymbol);

    // Check karta hai ke piece move hone par King check mein toh nahi aayega.
    bool checkPin(Piece* piece, Pos move);
    // Check karta hai ke koi dushman piece is square par attack kar raha hai ya nahi.
    bool isSquareAttacked(Pos targetPos, PieceColor attackerColor);
    
    // Game ki halat check karne wale functions.
    bool isCheck(PieceColor color);
    bool isCheckMate(PieceColor color);
    bool isStaleMate(PieceColor color);
    bool isInsufficientMaterial() const;
    bool hasLegalMoves(PieceColor color);
    
    // King ki move ko validate karta hai.
    bool kingCheckValidation(King& king, Pos move);
    
    // Square se piece hasil karne aur set karne ke functions.
    Piece* getSquare(int r, int c) const { return squares[r][c]; }
    void setSquare(int r, int c, Piece* p) { squares[r][c] = p; }

    // Board ki maujooda state string mein hasil karta hai.
    std::string getBoardState() const;
    
    // Board ki state ko FEN notation mein convert karta hai (AI ke liye).
    std::string toFEN(PieceColor turn) const;

    // RecordFile ko friend isliye banaya hai takay woh private members ko save/load ke liye use kar sakay
    friend class RecordFile;
};