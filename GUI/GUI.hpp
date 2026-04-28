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
    
    std::map<std::string, Texture2D> textures; // Pieces ki images store karne ke liye
    
    Pos selectedPos;           // Konsa piece select kiya gaya hai
    bool pieceSelected;        // Kya koi piece selected hai?
    std::vector<Pos> validMoves; // Selected piece ki valid moves
    PieceColor currentTurn;
    bool showPromotionMenu;

    // Internal Drawing Functions
    void loadTextures();       // Images load karta hai
    void drawBoard();          // Board draw karta hai
    void drawPieces();         // Pieces draw karta hai
    void drawHighlights();      // Selected piece aur moves highlight karta hai
    void drawScores(PieceColor currentTurn); // Score aur Turn dikhata hai
    void drawPromotionMenu();
    void recalculateDimensions(); // Screen size adjust karta hai
    void drawButton(Rectangle rect, const char* text, Color baseColor); // Button banata hai

    Pos getBoardPos(Vector2 mousePos); // Mouse coord ko board pos mein badalta hai
    std::string getPieceResourceName(Piece* piece); // Piece ki texture ka naam

public:
    GUI(Board& b);
    ~GUI();
    
    // Menu buttons (Game.cpp inhein check karta hai)
    Rectangle btnNewGame, btnLoadGame, btnHowToPlay, btnAbout, btnQuit;
    Rectangle btnPvP, btnPvC;
    Rectangle btnEasy, btnMedium, btnHard, btnExpert;
    Rectangle btnBack;
    
    // Check karta hai ke button click hua ya nahi
    bool isButtonClicked(Rectangle rect);

    // Mukhtalif screens draw karne ke functions
    void drawMenu();
    void drawModeSelection();
    void drawDifficultySelection();
    void drawAbout();
    void drawLoadList(const std::vector<SaveEntry>& entries, int& selectedIndex);

    // Input update aur rendering
    bool update(PieceColor currentTurn, Pos& outFrom, Pos& outTo);
    void render(PieceColor currentTurn);
    bool shouldClose();

    // Pawn promotion ka intikhab
    char getPromotionChoice(PieceColor color);
};

#endif
