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
        static std::vector<Pos> slidingMove(Board& board, Piece* piece, bool checkSafety = true);
        static std::vector<Pos> knightMove(Board& board, Knight* knight, bool checkSafety = true);
        static std::vector<Pos> pawnMove(Board& board, Pawn* pawn, bool checkSafety = true);
        static std::vector<Pos> kingMove(Board& board, King& king, bool checkSafety = true);
};
