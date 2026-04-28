#include "GUI.hpp"
#include "../classes/Piece.hpp"
#include <iostream>

/**
 * GUI Constructor: Screen dimensions, cellSize aur basic window settings initialize karta hai.
 * Yeh Game class ke constructor mein call hota hai jab game start hoti hai.
 */
GUI::GUI(Board& b) : board(b), screenWidth(1100), screenHeight(800), cellSize(85), pieceSelected(false), showPromotionMenu(false) {
    InitWindow(screenWidth, screenHeight, "Chess Master");
    SetTargetFPS(60);
    SetExitKey(0); 
    loadTextures();
    recalculateDimensions();
}

/**
 * GUI Destructor: Saari loaded textures ko memory se saaf karta hai aur window band karta hai.
 */
GUI::~GUI() {
    for (auto const& [name, tex] : textures) UnloadTexture(tex);
    CloseWindow();
}

/**
 * loadTextures: 'assets' folder se saare chess pieces ki PNG images load karke textures banata hai.
 */
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

/**
 * recalculateDimensions: Screen size ke mutabiq board aur buttons ki position adjust karta hai.
 * Yeh function har frame par call hota hai takay resize handle ho sakay.
 */
void GUI::recalculateDimensions() {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    boardSize = cellSize * 8;
    offsetX = 40; 
    offsetY = (screenHeight - boardSize) / 2;

    float centerX = (float)screenWidth / 2;
    btnNewGame = { centerX - 150, 200, 300, 60 };
    btnLoadGame = { centerX - 150, 280, 300, 60 };
    btnHowToPlay = { centerX - 150, 360, 300, 60 };
    btnAbout = { centerX - 150, 440, 300, 60 };
    btnQuit = { centerX - 150, 520, 300, 60 };
    
    btnPvP = { centerX - 150, 250, 300, 60 };
    btnPvC = { centerX - 150, 330, 300, 60 };
    
    btnEasy = { centerX - 150, 160, 300, 60 };
    btnMedium = { centerX - 150, 240, 300, 60 };
    btnHard = { centerX - 150, 320, 300, 60 };
    btnExpert = { centerX - 150, 400, 300, 60 };

    btnBack = { centerX - 150, (float)screenHeight - 100, 300, 50 };
}

/**
 * shouldClose: Window close button ya ESC press hone par true return karta hai.
 */
bool GUI::shouldClose() { return WindowShouldClose(); }

/**
 * drawButton: Aik custom button screen par draw karta hai aur hover effect handle karta hai.
 */
void GUI::drawButton(Rectangle rect, const char* text, Color baseColor) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), rect);
    Color drawColor = hover ? ColorBrightness(baseColor, 0.2f) : baseColor;
    DrawRectangleRec(rect, drawColor);
    DrawRectangleLinesEx(rect, 2, DARKGRAY);
    DrawText(text, rect.x + (rect.width - MeasureText(text, 20)) / 2, rect.y + (rect.height - 20) / 2, 20, RAYWHITE);
}

/**
 * isButtonClicked: Check karta hai ke kya mouse button kisi rectangle (button) ke andar click hua hai.
 */
bool GUI::isButtonClicked(Rectangle rect) {
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

/**
 * drawMenu: Game ka main menu (New Game, Load Game, etc.) draw karta hai.
 */
void GUI::drawMenu() {
    recalculateDimensions();
    DrawText("CHESS MASTER", screenWidth / 2 - MeasureText("CHESS MASTER", 50) / 2, 100, 50, GOLD);
    drawButton(btnNewGame, "New Game", { 60, 120, 60, 255 });
    drawButton(btnLoadGame, "Load Game", { 60, 60, 120, 255 });
    drawButton(btnHowToPlay, "How to Play", { 120, 60, 120, 255 });
    drawButton(btnAbout, "About Game", { 120, 120, 60, 255 });
    drawButton(btnQuit, "Quit Game", { 150, 50, 50, 255 });
}

/**
 * drawModeSelection: Player vs Player ya Player vs Computer select karne wali screen draw karta hai.
 */
void GUI::drawModeSelection() {
    recalculateDimensions();
    DrawText("SELECT MODE", screenWidth / 2 - MeasureText("SELECT MODE", 30) / 2, 100, 30, GOLD);
    drawButton(btnPvP, "Player vs Player", { 60, 60, 120, 255 });
    drawButton(btnPvC, "Player vs Computer", { 60, 120, 60, 255 });
    drawButton(btnBack, "Back (ESC)", DARKGRAY);
}

/**
 * drawDifficultySelection: Computer AI ki difficulty (Easy to Expert) select karne ki screen.
 */
void GUI::drawDifficultySelection() {
    recalculateDimensions();
    DrawText("SELECT DIFFICULTY", screenWidth / 2 - MeasureText("SELECT DIFFICULTY", 30) / 2, 80, 30, GOLD);
    drawButton(btnEasy, "Easy", { 60, 120, 60, 255 });
    drawButton(btnMedium, "Medium", { 120, 120, 60, 255 });
    drawButton(btnHard, "Hard", { 120, 60, 60, 255 });
    drawButton(btnExpert, "Expert", { 180, 60, 60, 255 });
    drawButton(btnBack, "Back (ESC)", DARKGRAY);
}

/**
 * drawLoadList: Saved games ki list dikhata hai takay user kisi purani game ko load kar sakay.
 */
void GUI::drawLoadList(const std::vector<SaveEntry>& entries, int& selectedIndex) {
    recalculateDimensions();
    DrawText("SAVED GAMES", screenWidth / 2 - MeasureText("SAVED GAMES", 30) / 2, 40, 30, GOLD);
    for (int i = 0; i < (int)entries.size(); i++) {
        Rectangle rect = { (float)(screenWidth / 2 - 250), (float)(100 + i * 70), 500.0f, 60.0f };
        bool hover = CheckCollisionPointRec(GetMousePosition(), rect);
        DrawRectangleRec(rect, hover ? DARKGRAY : (Color){ 50, 50, 50, 255 });
        DrawText(entries[i].date.c_str(), rect.x + 15, rect.y + 10, 18, RAYWHITE);
        DrawText(entries[i].mode.c_str(), rect.x + 15, rect.y + 35, 16, GOLD);
        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedIndex = i;
    }
    drawButton(btnBack, "Back (ESC)", DARKGRAY);
}

/**
 * render: Game play screen ki saari cheezein (Board, Pieces, Score, Check/Mate) draw karta hai.
 */
void GUI::render(PieceColor currentTurn) {
    recalculateDimensions();
    drawBoard();
    drawPieces();
    drawHighlights();
    drawScores(currentTurn);
    
    if (board.isCheckMate(PieceColor::WHITE_PIECE)) {
        DrawRectangle(0, 0, screenWidth, screenHeight, {0,0,0,150});
        DrawText("CHECKMATE! BLACK WINS", screenWidth/2 - MeasureText("CHECKMATE! BLACK WINS", 40)/2, screenHeight/2 - 20, 40, RED);
    } else if (board.isCheckMate(PieceColor::BLACK_PIECE)) {
        DrawRectangle(0, 0, screenWidth, screenHeight, {0,0,0,150});
        DrawText("CHECKMATE! WHITE WINS", screenWidth/2 - MeasureText("CHECKMATE! WHITE WINS", 40)/2, screenHeight/2 - 20, 40, GREEN);
    } else if (board.isCheck(PieceColor::WHITE_PIECE) || board.isCheck(PieceColor::BLACK_PIECE)) {
        DrawText("CHECK!", offsetX + boardSize/2 - MeasureText("CHECK!", 30)/2, offsetY - 40, 30, ORANGE);
    }
}

/**
 * drawBoard: 8x8 Chess board ke squares draw karta hai alternating colors mein.
 */
void GUI::drawBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Color color = ((i + j) % 2 == 0) ? (Color){ 235, 235, 210, 255 } : (Color){ 115, 149, 82, 255 };
            DrawRectangle(offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize, color);
        }
    }
}

/**
 * getPieceResourceName: Piece ke type aur color ke mutabiq texture ka naam return karta hai (e.g. "king-white").
 */
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

/**
 * drawPieces: Board par maujood har piece ki image relevant square par draw karta hai.
 */
void GUI::drawPieces() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = board.getSquare(i, j);
            if (p) {
                std::string texName = getPieceResourceName(p);
                if (textures.count(texName))
                    DrawTexture(textures[texName], offsetX + j * cellSize, offsetY + i * cellSize, WHITE);
            }
        }
    }
}

/**
 * drawHighlights: Selected piece aur uski valid moves ko highlight (circles/lines) karta hai.
 */
void GUI::drawHighlights() {
    if (pieceSelected) {
        DrawRectangleLinesEx({(float)offsetX + selectedPos.y * cellSize, (float)offsetY + selectedPos.x * cellSize, (float)cellSize, (float)cellSize}, 3, GOLD);
        Piece* selectedPiece = board.getSquare(selectedPos.x, selectedPos.y);
        
        for (auto move : validMoves) {
            float cx = offsetX + move.y * cellSize + cellSize / 2;
            float cy = offsetY + move.x * cellSize + cellSize / 2;
            
            if (board.getSquare(move.x, move.y) != nullptr) {
                // Normal Capture
                DrawCircleLines(cx, cy, (float)cellSize/2 - 5, { 255, 0, 0, 150 });
            } else if (move == board.enPassantTarget && selectedPiece && tolower(selectedPiece->getSymbol()) == 'p') {
                // En Passant GUI
                DrawCircle(cx, cy, (float)cellSize/2 - 10, { 0, 121, 241, 100 });
                DrawText("EP", cx - 10, cy - 10, 20, RAYWHITE);
            } else if (selectedPiece && tolower(selectedPiece->getSymbol()) == 'k' && abs(move.y - selectedPos.y) == 2) {
                // Castling GUI
                DrawCircle(cx, cy, (float)cellSize/2 - 10, { 0, 121, 241, 100 });
                DrawText("0-0", cx - 15, cy - 10, 20, RAYWHITE);
            } else {
                // Normal Move
                DrawCircle(cx, cy, 10, { 0, 0, 0, 50 });
            }
        }
    }
}

/**
 * drawScores: Screen ki side par score, current turn aur controls ki detail dikhata hai.
 */
void GUI::drawScores(PieceColor currentTurn) {
    int scoreX = offsetX + boardSize + 40;
    DrawText("SCORE", scoreX, offsetY, 25, GOLD);
    DrawText(TextFormat("White: %d", board.getWhiteScore()), scoreX, offsetY + 40, 20, RAYWHITE);
    DrawText(TextFormat("Black: %d", board.getBlackScore()), scoreX, offsetY + 70, 20, RAYWHITE);
    
    DrawText("TURN", scoreX, offsetY + 130, 25, GOLD);
    const char* turnText = (currentTurn == PieceColor::WHITE_PIECE) ? "WHITE" : "BLACK";
    Color turnColor = (currentTurn == PieceColor::WHITE_PIECE) ? RAYWHITE : DARKGRAY;
    DrawRectangle(scoreX, offsetY + 160, 100, 30, turnColor);
    DrawText(turnText, scoreX + 10, offsetY + 165, 20, (currentTurn == PieceColor::WHITE_PIECE ? BLACK : WHITE));

    DrawText("CONTROLS", scoreX, offsetY + 230, 25, GOLD);
    DrawText("S: Save Game", scoreX, offsetY + 265, 18, GRAY);
    DrawText("ESC: Menu", scoreX, offsetY + 290, 18, GRAY);
    DrawText("F11: Fullscreen", scoreX, offsetY + 315, 18, GRAY);
}

/**
 * getBoardPos: Screen par mouse ke coordinates ko board ke (row, col) mein convert karta hai.
 */
Pos GUI::getBoardPos(Vector2 mousePos) {
    return Pos((mousePos.y - offsetY) / cellSize, (mousePos.x - offsetX) / cellSize);
}

/**
 * update: Mouse input handle karta hai, piece select karna aur move karna isi function mein hota hai.
 */
bool GUI::update(PieceColor currentTurn, Pos& outFrom, Pos& outTo) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Pos boardPos = getBoardPos(GetMousePosition());
        if (!board.checkBoundary(boardPos)) return false;
        
        if (!pieceSelected) {
            Piece* p = board.getSquare(boardPos.x, boardPos.y);
            if (p && p->getcolor() == currentTurn) {
                selectedPos = boardPos;
                pieceSelected = true;
                validMoves = p->getPossibleMoves();
            }
        } else {
            if (boardPos == selectedPos) {
                pieceSelected = false;
            } else {
                bool isValid = false;
                for (auto m : validMoves) {
                    if (m == boardPos) { isValid = true; break; }
                }
                if (isValid) {
                    outFrom = selectedPos;
                    outTo = boardPos;
                    pieceSelected = false;
                    return true;
                } else {
                    Piece* p = board.getSquare(boardPos.x, boardPos.y);
                    if (p && p->getcolor() == currentTurn) {
                        selectedPos = boardPos;
                        validMoves = p->getPossibleMoves();
                    } else {
                        pieceSelected = false;
                    }
                }
            }
        }
    }
    return false;
}

/**
 * drawAbout: Developers ke naam aur project ki info dikhata hai.
 */
void GUI::drawAbout() {
    recalculateDimensions();
    DrawText("DEVELOPERS", screenWidth / 2 - MeasureText("DEVELOPERS", 40) / 2, 100, 40, GOLD);
    DrawText("1. Fahad", screenWidth / 2 - 100, 200, 25, RAYWHITE);
    DrawText("2. Majid", screenWidth / 2 - 100, 250, 25, RAYWHITE);
    DrawText("3. Umar", screenWidth / 2 - 100, 300, 25, RAYWHITE);
    DrawText("OOP Lab Project - 2nd Semester", screenWidth / 2 - MeasureText("OOP Lab Project - 2nd Semester", 20) / 2, 400, 20, GRAY);
    drawButton(btnBack, "Back (ESC)", DARKGRAY);
}

/**
 * drawPromotionMenu: (Not used directly, getPromotionChoice handles this).
 */
void GUI::drawPromotionMenu() {}

/**
 * getPromotionChoice: Jab pawn end par pohanch jaye toh user se naye piece (Queen, Rook, etc.) ka intikhab karwata hai.
 */
char GUI::getPromotionChoice(PieceColor color) {
    char choice = ' ';
    std::string colorStr = (color == PieceColor::WHITE_PIECE) ? "white" : "black";
    
    while (choice == ' ') {
        recalculateDimensions();
        Rectangle qRect = { (float)screenWidth/2 - 200, (float)screenHeight/2 - 50, 80, 80 };
        Rectangle rRect = { (float)screenWidth/2 - 100, (float)screenHeight/2 - 50, 80, 80 };
        Rectangle bRect = { (float)screenWidth/2,       (float)screenHeight/2 - 50, 80, 80 };
        Rectangle nRect = { (float)screenWidth/2 + 100, (float)screenHeight/2 - 50, 80, 80 };

        if (WindowShouldClose()) return 'Q';
        
        BeginDrawing();
        DrawRectangle(0, 0, screenWidth, screenHeight, { 0, 0, 0, 150 });
        DrawText("CHOOSE PROMOTION", screenWidth/2 - MeasureText("CHOOSE PROMOTION", 30)/2, screenHeight/2 - 120, 30, GOLD);
        
        bool qHover = CheckCollisionPointRec(GetMousePosition(), qRect);
        bool rHover = CheckCollisionPointRec(GetMousePosition(), rRect);
        bool bHover = CheckCollisionPointRec(GetMousePosition(), bRect);
        bool nHover = CheckCollisionPointRec(GetMousePosition(), nRect);
        
        DrawRectangleRec(qRect, qHover ? LIGHTGRAY : GRAY);
        DrawRectangleRec(rRect, rHover ? LIGHTGRAY : GRAY);
        DrawRectangleRec(bRect, bHover ? LIGHTGRAY : GRAY);
        DrawRectangleRec(nRect, nHover ? LIGHTGRAY : GRAY);
        
        if (textures.count("queen-" + colorStr))  DrawTexture(textures["queen-" + colorStr], qRect.x, qRect.y, WHITE);
        if (textures.count("rook-" + colorStr))   DrawTexture(textures["rook-" + colorStr], rRect.x, rRect.y, WHITE);
        if (textures.count("bishop-" + colorStr)) DrawTexture(textures["bishop-" + colorStr], bRect.x, bRect.y, WHITE);
        if (textures.count("knight-" + colorStr)) DrawTexture(textures["knight-" + colorStr], nRect.x, nRect.y, WHITE);
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (qHover) choice = 'Q';
            if (rHover) choice = 'R';
            if (bHover) choice = 'B';
            if (nHover) choice = 'N';
        }
        EndDrawing();
    }
    return choice;
}
