#include "Game.hpp"
#include "../GUI/GUI.hpp"

// Constructor: AI player set karta hai, board initialize karta hai aur GUI loop start karta hai.
Game::Game() : moveCount(1), fiftyMoveCounter(0), isGameDraw(false), currentState(GameState::MENU), vsComputer(false) {
    ai = new AIPlayer("stockfish/stockfish-windows-x86-64-avx2.exe");
    board.initBoard();
    guiLoop();
}

Game::~Game() {
    delete ai;
}

void Game::checkDrawConditions() {
    if (fiftyMoveCounter >= 100) {
        isGameDraw = true;
        drawReason = "50-move rule";
    }
}

// guiLoop: Yeh function game ka main engine hai. Har frame par input leta hai aur screen update karta hai.
void Game::guiLoop() {
    GUI gui(board);
    currentState = GameState::MENU;
    std::vector<SaveEntry> savedEntries;
    int selectedFileIndex = -1;

    if (!DirectoryExists("saves")) {
        MakeDirectory("saves");
    }
    
    while(!gui.shouldClose() && currentState != GameState::QUIT) {
        // Fullscreen Toggle
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        BeginDrawing();
        ClearBackground({ 30, 30, 30, 255 });

        if (currentState == GameState::MENU) {
            gui.drawMenu();
            if (gui.isButtonClicked(gui.btnNewGame)) currentState = GameState::MODE_SELECTION;
            if (gui.isButtonClicked(gui.btnLoadGame)) {
                currentState = GameState::LOADING;
                savedEntries = RecordFile::getSavedGamesList();
                selectedFileIndex = -1;
            }
            if (gui.isButtonClicked(gui.btnHowToPlay)) {
                OpenURL("https://www.chess.com/learn-how-to-play-chess");
            }
            if (gui.isButtonClicked(gui.btnAbout)) currentState = GameState::ABOUT;
            if (gui.isButtonClicked(gui.btnQuit)) currentState = GameState::QUIT;
        } 
        else if (currentState == GameState::MODE_SELECTION) {
            gui.drawModeSelection();
            if (gui.isButtonClicked(gui.btnPvP)) {
                vsComputer = false;
                board.initBoard();
                moveCount = 1;
                history.clear();
                currentState = GameState::PLAYING;
            }
            if (gui.isButtonClicked(gui.btnPvC)) {
                currentState = GameState::DIFFICULTY_SELECTION;
            }
            if (IsKeyPressed(KEY_ESCAPE) || gui.isButtonClicked(gui.btnBack)) currentState = GameState::MENU;
        }
        else if (currentState == GameState::DIFFICULTY_SELECTION) {
            gui.drawDifficultySelection();
            int level = 0;
            if (gui.isButtonClicked(gui.btnEasy)) level = 1;
            else if (gui.isButtonClicked(gui.btnMedium)) level = 2;
            else if (gui.isButtonClicked(gui.btnHard)) level = 3;
            else if (gui.isButtonClicked(gui.btnExpert)) level = 4;
            
            if (level > 0) {
                ai->setDifficulty(level);
                vsComputer = true;
                board.initBoard();
                moveCount = 1;
                history.clear();
                currentState = GameState::PLAYING;
            }
            if (IsKeyPressed(KEY_ESCAPE) || gui.isButtonClicked(gui.btnBack)) currentState = GameState::MODE_SELECTION;
        }
        else if (currentState == GameState::PLAYING) {
            currentTurn = (moveCount % 2 == 1) ? PieceColor::WHITE_PIECE : PieceColor::BLACK_PIECE;
            
            if (IsKeyPressed(KEY_S)) {
                RecordFile::saveGame(board, moveCount, vsComputer, "");
            }

            Pos from, to;
            char aiPromo = ' ';
            bool moveReady = false;

            if (vsComputer && currentTurn == PieceColor::BLACK_PIECE && !isGameDraw) {
                std::string fen = board.toFEN(currentTurn);
                if (ai->getBestMove(fen, from, to, aiPromo)) {
                    moveReady = true;
                }
            } else {
                if(!isGameDraw && gui.update(currentTurn, from, to)) {
                    moveReady = true;
                }
            }

            if(moveReady) {
                if (board.makeMove(from, to, currentTurn)) {
                    moveCount++;
                    checkDrawConditions();
                    Piece* p = board.getSquare(to.x, to.y);
                    if (p != nullptr && (tolower(p->getSymbol()) == 'p')) {
                        if (to.x == 0 || to.x == 7) {
                            char choice = (vsComputer && currentTurn == PieceColor::BLACK_PIECE) ? aiPromo : gui.getPromotionChoice(currentTurn);
                            board.promotePawn(to, choice == ' ' ? 'Q' : choice);
                        }
                    }
                }
            }
            gui.render(currentTurn);
            if (IsKeyPressed(KEY_ESCAPE)) currentState = GameState::MENU;
        }
        else if (currentState == GameState::LOADING) {
            gui.drawLoadList(savedEntries, selectedFileIndex);
            if (selectedFileIndex != -1) {
                if (RecordFile::loadGame(board, moveCount, vsComputer, savedEntries[selectedFileIndex].filename)) {
                    currentState = GameState::PLAYING;
                }
            }
            if (IsKeyPressed(KEY_ESCAPE) || gui.isButtonClicked(gui.btnBack)) currentState = GameState::MENU;
        }
        else if (currentState == GameState::ABOUT) {
            gui.drawAbout();
            if (IsKeyPressed(KEY_ESCAPE) || gui.isButtonClicked(gui.btnBack)) currentState = GameState::MENU;
        }

        EndDrawing();
    }
}
