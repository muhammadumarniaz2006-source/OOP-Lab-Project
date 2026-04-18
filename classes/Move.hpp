#pragma once
#include <vector>
#include "Piece.hpp"

class MoveGenerator {
    public:
        static std::vector<Pos> slidingMove(Board& board, Pos pos, Color color, std::vector<Dir> dirs);
        static std::vector<Pos> knightMove(Board& board, Pos pos, Color color, std::vector<Dir> dirs);
        static std::vector<Pos> pawnMove(Board& board, Pos pos, Color color, Dir dir, bool ifFirst);
        static std::vector<Pos> kingMove(Board& board, Pos pos, Color color, std::vector<Dir> dirs);
};
