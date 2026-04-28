#pragma once
#include <string>

// PieceColor: Pieces ke rang (Sufaid ya Siyah)
enum class PieceColor { WHITE_PIECE, BLACK_PIECE };
// GameState: Game ki mukhtalif halatein (Menu, Playing, etc.)
enum class GameState { MENU, MODE_SELECTION, DIFFICULTY_SELECTION, LOADING, PLAYING, ABOUT, HOW_TO_PLAY, QUIT };
// GameMode: Player vs Player ya Player vs Computer
enum class GameMode { PVP, PVC };
// colorToString: PieceColor enum ko string mein badalta hai
std::string colorToString(PieceColor color);

// Pos: Board par kisi bhi square ki (x, y) coordinates
struct Pos {
    int x;
    int y;
    Pos(int x = 0, int y = 0);
    bool operator==(const Pos& pos) const;
};

// Dir: Piece ki movement ki direction (x aur y mein tabdeeli)
struct Dir {
    int x;  
    int y;
};
