#ifndef GUI_HPP
#define GUI_HPP

#include "raylib.h"
#include "../classes/Board.hpp"
#include "../classes/Common.hpp"
#include "../classes/RecordFile.hpp"
#include <map>
#include <string>
#include <vector>

class GUI {
private:
    Board& board;
    int screenWidth;
    int screenHeight;
    int cellSize;
    int boardSize;
    int offsetX;
    int offsetY;
    
    std::map<std::string, Texture2D> textures;
    
    Pos selectedPos;
    bool pieceSelected;
    std::vector<Pos> validMoves;
    PieceColor currentTurn;

    // Layout members
    int panelWidth;
    int panelGap;

    // Promotion state
    bool showPromotionMenu;
    PieceColor promotionColor;
    char promotionChoice;

    // Internal Drawing Functions
    void loadTextures();
    void drawBoard();
    void drawPieces();
    void drawHighlights();
    void drawScores(PieceColor currentTurn);
    void drawPromotionMenu();
    void recalculateDimensions();
    void drawButton(Rectangle rect, const char* text, Color baseColor);

    Pos getBoardPos(Vector2 mousePos);
    std::string getPieceResourceName(Piece* piece);

public:
    GUI(Board& b);
    ~GUI();
    
    // Menu button regions (Public for Game.cpp)
    Rectangle btnNewGame, btnLoadGame, btnHowToPlay, btnAbout, btnQuit;
    Rectangle btnPvP, btnPvC;
    Rectangle btnEasy, btnMedium, btnHard, btnExpert;
    bool isButtonClicked(Rectangle rect);

    // Menu rendering functions
    void drawMenu();
    void drawModeSelection();
    void drawDifficultySelection();
    void drawAbout();
    void drawLoadList(const std::vector<SaveEntry>& entries, int& selectedIndex);

    // Returns true if a move was made
    bool update(PieceColor currentTurn, Pos& outFrom, Pos& outTo);
    void render(PieceColor currentTurn);
    bool shouldClose();

    char getPromotionChoice(PieceColor color);
};

#endif
