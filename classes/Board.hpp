#pragma once
#include "Piece.hpp"

class King; // Forward declaration

class Board {
private:
    Piece* squares[8][8];
    vector<Piece*> sidePieces; // captured pieces ko store karnay kay liay vector banaya hai.
public:
    Board();
    ~Board();
    void initBoard();
    /*yai makemove piece ko move kernay kay liay hai aur undomove isliay banaya hai ager koi piecce check hoa tu undo move kerna hoga aur yai dono function game class handel karay gi */
    bool makeMove(Pos from, Pos to, PieceColor currentTurn);
    bool isEmpty(Pos pos) const;
    bool hasOpponent(Pos pos, PieceColor myColor) const;
    bool hasMate(Pos pos, PieceColor myColor) const;
    bool checkBoundary(Pos pos) const;
    void recalculateAllMoves();
    void recalculateAllMovesExceptKing();
    void print_board();
    Pos getKingPos(PieceColor color) const;
    
    int getWhiteScore() const;
    int getBlackScore() const;
    void popCapturedPiece();
    
    // Yeh variable us square ki position save rakhta hai jahan se pawn 'En Passant' ke liye guzra ho
    // Takay aglay turn mein opponent isay capture kar sakay
    Pos enPassantTarget;

    // Yeh function pawn ko doosray piece (Queen, Rook, etc.) mein tabdeel karne ke liye hai
    void promotePawn(Pos pos, char targetSymbol);

    bool checkPin(Piece* piece, Pos move);
    bool isSquareAttacked(Pos targetPos, PieceColor attackerColor);
    
    // Check, Checkmate and Stalemate logic
    bool isCheck(PieceColor color);
    bool isCheckMate(PieceColor color);
    bool isStaleMate(PieceColor color);
    bool isInsufficientMaterial() const;
    bool hasLegalMoves(PieceColor color);
    
    bool kingCheckValidation(King& king, Pos move);
    
    // Yeh functions RecordFile class ko board ke squares tak rasai (access) dete hain takay game save aur load ho sakay
    Piece* getSquare(int r, int c) const { return squares[r][c]; }
    void setSquare(int r, int c, Piece* p) { squares[r][c] = p; }

    // Board state as string for repetition check
    std::string getBoardState() const;
    
    // Stockfish ke liye standard FEN string generate karne wala function
    std::string toFEN(PieceColor turn) const;

    // RecordFile ko friend isliye banaya hai takay woh private members ko save/load ke liye use kar sakay
    friend class RecordFile;
};