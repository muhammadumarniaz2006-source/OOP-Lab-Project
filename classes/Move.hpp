#pragma once
#include <vector>
#include "Common.hpp"

// Forward declarations
class Board;
class King;
class Piece;
class Knight;
class Pawn;

class MoveGenerator {
    public:
        // Queen, Rook, aur Bishop ki seedhi ya diagonal moves calculate karta hai.
        static std::vector<Pos> slidingMove(Board& board, Piece* piece, bool checkSafety = true);
        // Knight (Ghoray) ki 'L' shape moves calculate karta hai.
        static std::vector<Pos> knightMove(Board& board, Knight* knight, bool checkSafety = true);
        // Pawn ki unique moves (sidha chalna, diagonal capture, double move, en passant) calculate karta hai.
        static std::vector<Pos> pawnMove(Board& board, Pawn* pawn, bool checkSafety = true);
        // King ki normal moves aur Castling calculate karta hai.
        static std::vector<Pos> kingMove(Board& board, King& king, bool checkSafety = true);
};
