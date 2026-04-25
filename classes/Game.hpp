#include "Board.hpp"
#include "Piece.hpp"
#include "RecordFile.hpp"
#include "AIPlayer.hpp"
#include <map>
#include <string>

struct MoveRecord {
    Pos from;
    Pos to;
    Piece* capturedPiece;
    bool movedPieceWasFirstMove;
    // Yeh move se pehle wala En Passant target save karta hai takay undo par wapis aa sakay
    Pos enPassantTargetBeforeMove;
    // Castling ke liye Rook ki state save kar rahay hain
    bool rookWasFirstMoveBeforeCastling;
    int fiftyMoveCounterBeforeMove;

    MoveRecord(Pos f, Pos t, Piece* cap = nullptr, bool first = false, Pos ep = Pos(-1,-1), bool rFirst = false, int fifty = 0) 
        : from(f), to(t), capturedPiece(cap), movedPieceWasFirstMove(first), 
          enPassantTargetBeforeMove(ep), rookWasFirstMoveBeforeCastling(rFirst), fiftyMoveCounterBeforeMove(fifty) {}
};

class Game{
    private:
        Board board;
        AIPlayer* ai;
        int moveCount; //odd moves for white and even moves for black
        PieceColor currentTurn; // To keep track of whose turn it is
        int choice;
        vector<MoveRecord> history; // Game ki history store karne ke liye stack (vector)
        
        // Draw rule members
        int fiftyMoveCounter; // Counter for 50-move rule
        std::map<std::string, int> positionHistory; // For threefold repetition
        bool isGameDraw;
        std::string drawReason;
        
        GameState currentState;
        GameMode mode;
        bool vsComputer;

        void checkDrawConditions();
    public:
        void gameLoop();
        void guiLoop();
        Game();
        ~Game();
        void menu();
        void saveGame();
        void loadGame();
        void undoMove(); // Undo karne ka function
};