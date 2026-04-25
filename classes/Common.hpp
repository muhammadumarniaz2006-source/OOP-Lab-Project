#pragma once
#include <string>

enum class PieceColor { WHITE_PIECE, BLACK_PIECE };
enum class GameState { MENU, MODE_SELECTION, DIFFICULTY_SELECTION, LOADING, PLAYING, ABOUT, HOW_TO_PLAY, QUIT };
enum class GameMode { PVP, PVC };
std::string colorToString(PieceColor color);

struct Pos {
    int x;
    int y;
    Pos(int x = 0, int y = 0);
    bool operator==(const Pos& pos) const;
};

struct Dir {
    int x;  
    int y;
};
