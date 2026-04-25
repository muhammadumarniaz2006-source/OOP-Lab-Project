#include "GUI.hpp"
#include "../classes/Piece.hpp"
#include <iostream>

GUI::GUI(Board& b) : board(b), screenWidth(1100), screenHeight(800), cellSize(85), pieceSelected(false), showPromotionMenu(false) {
    boardSize = cellSize * 8;
    offsetX = 50;
    offsetY = (screenHeight - boardSize) / 2;
    
    InitWindow(screenWidth, screenHeight, "Chess Master");
    SetTargetFPS(60);
    loadTextures();
    recalculateDimensions();
}

GUI::~GUI() {
    for (auto const& [name, tex] : textures) UnloadTexture(tex);
    CloseWindow();
}

void GUI::loadTextures() {
    std::string types[] = {"pawn", "rook", "knight", "bishop", "queen", "king"};
    std::string colors[] = {"white", "black"};
    for (const auto& type : types) {
        for (const auto& color : colors) {
            std::string path = "assets/" + type + "-" + color + ".png";
            Image img = LoadImage(path.c_str());
            if (img.data != nullptr) {
                ImageResize(&img, cellSize, cellSize);
                textures[type + "-" + color] = LoadTextureFromImage(img);
                UnloadImage(img);
            }
        }
    }
}

void GUI::recalculateDimensions() {
    btnNewGame = { (float)(screenWidth / 2 - 150), 200, 300, 60 };
    btnLoadGame = { (float)(screenWidth / 2 - 150), 280, 300, 60 };
    btnHowToPlay = { (float)(screenWidth / 2 - 150), 360, 300, 60 };
    btnAbout = { (float)(screenWidth / 2 - 150), 440, 300, 60 };
    btnQuit = { (float)(screenWidth / 2 - 150), 520, 300, 60 };
    btnPvP = { (float)(screenWidth / 2 - 150), 250, 300, 60 };
    btnPvC = { (float)(screenWidth / 2 - 150), 330, 300, 60 };
    btnEasy = { (float)(screenWidth / 2 - 150), 160, 300, 60 };
    btnMedium = { (float)(screenWidth / 2 - 150), 240, 300, 60 };
    btnHard = { (float)(screenWidth / 2 - 150), 320, 300, 60 };
    btnExpert = { (float)(screenWidth / 2 - 150), 400, 300, 60 };
}

bool GUI::shouldClose() { return WindowShouldClose(); }

void GUI::drawButton(Rectangle rect, const char* text, Color baseColor) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), rect);
    Color drawColor = hover ? ColorBrightness(baseColor, 0.2f) : baseColor;
    DrawRectangleRec(rect, drawColor);
    DrawRectangleLinesEx(rect, 2, DARKGRAY);
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height - 20) / 2, 20, RAYWHITE);
}

bool GUI::isButtonClicked(Rectangle rect) {
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void GUI::drawMenu() {
    DrawText("CHESS MASTER", screenWidth / 2 - MeasureText("CHESS MASTER", 50) / 2, 100, 50, GOLD);
    drawButton(btnNewGame, "New Game", { 60, 120, 60, 255 });
    drawButton(btnLoadGame, "Load Game", { 60, 60, 120, 255 });
    drawButton(btnHowToPlay, "How to Play", { 120, 60, 120, 255 });
    drawButton(btnAbout, "About Game", { 120, 120, 60, 255 });
    drawButton(btnQuit, "Quit Game", { 150, 50, 50, 255 });
}

void GUI::drawModeSelection() {
    DrawText("SELECT MODE", screenWidth / 2 - MeasureText("SELECT MODE", 30) / 2, 100, 30, GOLD);
    drawButton(btnPvP, "Player vs Player", { 60, 60, 120, 255 });
    drawButton(btnPvC, "Player vs Computer", { 60, 120, 60, 255 });
    DrawText("Press ESC to go back", screenWidth / 2 - MeasureText("Press ESC to go back", 18) / 2, screenHeight - 40, 18, GRAY);
}

void GUI::drawDifficultySelection() {
    DrawText("SELECT DIFFICULTY", screenWidth / 2 - MeasureText("SELECT DIFFICULTY", 30) / 2, 80, 30, GOLD);
    drawButton(btnEasy, "Easy", { 60, 120, 60, 255 });
    drawButton(btnMedium, "Medium", { 120, 120, 60, 255 });
    drawButton(btnHard, "Hard", { 120, 60, 60, 255 });
    drawButton(btnExpert, "Expert", { 180, 60, 60, 255 });
    DrawText("Press ESC to go back", screenWidth / 2 - MeasureText("Press ESC to go back", 18) / 2, screenHeight - 40, 18, GRAY);
}

void GUI::drawLoadList(const std::vector<SaveEntry>& entries, int& selectedIndex) {
    DrawText("SAVED GAMES", screenWidth / 2 - MeasureText("SAVED GAMES", 30) / 2, 40, 30, GOLD);
    for (int i = 0; i < (int)entries.size(); i++) {
        Rectangle rect = { (float)(screenWidth / 2 - 250), (float)(100 + i * 70), 500.0f, 60.0f };
        bool hover = CheckCollisionPointRec(GetMousePosition(), rect);
        DrawRectangleRec(rect, hover ? DARKGRAY : (Color){ 50, 50, 50, 255 });
        DrawText(entries[i].date.c_str(), rect.x + 15, rect.y + 10, 18, RAYWHITE);
        DrawText(entries[i].mode.c_str(), rect.x + 15, rect.y + 35, 16, GOLD);
        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedIndex = i;
    }
    DrawText("Press ESC to go back", screenWidth / 2 - MeasureText("Press ESC to go back", 18) / 2, screenHeight - 40, 18, GRAY);
}

void GUI::render() {
    drawBoard();
    drawPieces();
    drawHighlights();
    drawScores();
}

void GUI::drawBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Color color = ((i + j) % 2 == 0) ? (Color){ 235, 235, 210, 255 } : (Color){ 115, 149, 82, 255 };
            DrawRectangle(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, color);
        }
    }
}

std::string GUI::getPieceResourceName(Piece* piece) {
    if (!piece) return "";
    std::string name = "";
    char sym = tolower(piece->getSymbol());
    if (sym == 'p') name = "pawn";
    else if (sym == 'r') name = "rook";
    else if (sym == 'n') name = "knight";
    else if (sym == 'b') name = "bishop";
    else if (sym == 'q') name = "queen";
    else if (sym == 'k') name = "king";
    name += (piece->getcolor() == PieceColor::WHITE_PIECE ? "-white" : "-black");
    return name;
}

void GUI::drawPieces() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = board.getSquare(i, j);
            if (p) {
                std::string texName = getPieceResourceName(p);
                if (textures.count(texName)) DrawTexture(textures[texName], offsetX + j * cellSize, offsetY + i * cellSize, WHITE);
            }
        }
    }
}

void GUI::drawHighlights() {
    if (pieceSelected) {
        DrawRectangleLinesEx({(float)offsetX + selectedPos.y * cellSize, (float)offsetY + selectedPos.x * cellSize, (float)cellSize, (float)cellSize}, 3, GOLD);
        for (auto move : validMoves) DrawCircle(offsetX + move.y * cellSize + cellSize / 2, offsetY + move.x * cellSize + cellSize / 2, 10, { 0, 0, 0, 50 });
    }
}

void GUI::drawScores() {
    int scoreX = offsetX + boardSize + 40;
    DrawText("CAPTURED", scoreX, offsetY, 25, GOLD);
    DrawText(TextFormat("White: +%d", board.getWhiteScore()), scoreX, offsetY + 40, 20, GREEN);
    DrawText(TextFormat("Black: +%d", board.getBlackScore()), scoreX, offsetY + 70, 20, RED);
    
    DrawText("TURN", scoreX, offsetY + 130, 25, GOLD);
    // Move count is used to determine turn
    // (Actual logic is in Game::guiLoop, but we can mirror it here)
}

Pos GUI::getBoardPos(Vector2 mousePos) {
    return Pos((mousePos.y - offsetY) / cellSize, (mousePos.x - offsetX) / cellSize);
}

bool GUI::update(PieceColor currentTurn, Pos& outFrom, Pos& outTo) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Pos boardPos = getBoardPos(GetMousePosition());
        if (!board.checkBoundary(boardPos)) return false;
        if (!pieceSelected) {
            Piece* p = board.getSquare(boardPos.x, boardPos.y);
            if (p && p->getcolor() == currentTurn) {
                selectedPos = boardPos; pieceSelected = true; validMoves = p->getPossibleMoves();
            }
        } else {
            outFrom = selectedPos; outTo = boardPos; pieceSelected = false; return true;
        }
    }
    return false;
}

void GUI::drawAbout() {
    DrawText("DEVELOPERS", screenWidth / 2 - MeasureText("DEVELOPERS", 40) / 2, 100, 40, GOLD);
    DrawText("1. Fahad", screenWidth / 2 - 100, 200, 25, RAYWHITE);
    DrawText("2. Majid", screenWidth / 2 - 100, 250, 25, RAYWHITE);
    DrawText("3. Umar", screenWidth / 2 - 100, 300, 25, RAYWHITE);
    DrawText("OOP Lab Project - 2nd Semester", screenWidth / 2 - MeasureText("OOP Lab Project - 2nd Semester", 20) / 2, 400, 20, GRAY);
    DrawText("Press ESC to go back", screenWidth / 2 - MeasureText("Press ESC to go back", 18) / 2, screenHeight - 60, 18, GOLD);
}

void GUI::drawPromotionMenu() {}
char GUI::getPromotionChoice(PieceColor color) { return 'Q'; }
