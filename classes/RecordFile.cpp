#include "RecordFile.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

/**
 * Timestamp generate karta hai (Format: Save_2024-04-25_14-30-00.txt)
 * @return: Unique file name based on current time
 */
std::string RecordFile::generateTimestampName() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << "Save_" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".txt";
    return oss.str();
}

/**
 * Index file ko update karta hai takay list dikhana asaan ho
 * @param filename: Save ki gayi file ka path
 * @param vsComputer: Game mode (Computer ke khilaf ya nahi)
 */
void RecordFile::updateIndex(std::string filename, bool vsComputer) {
    ofstream file("saves/index.txt", ios::app); // Append mode: purani entries delete nahi hongi
    if (file.is_open()) {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        
        // Data format: filename|timestamp|mode
        file << filename << "|" << oss.str() << "|" << (vsComputer ? "vs Computer" : "vs Player") << endl;
        file.close();
    }
}

/**
 * Index file se saari saved games ki list parhta hai
 * @return: SaveEntry objects ka vector
 */
std::vector<SaveEntry> RecordFile::getSavedGamesList() {
    std::vector<SaveEntry> entries;
    ifstream file("saves/index.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        SaveEntry entry;
        getline(ss, entry.filename, '|');
        getline(ss, entry.date, '|');
        getline(ss, entry.mode, '|');
        if (!entry.filename.empty()) entries.push_back(entry);
    }
    file.close();
    return entries;
}

/**
 * Poori game ki state ko file mein save karta hai
 * @param board: Board object (Current pieces state)
 * @param moveCount: Current turn count
 * @param vsComputer: Game mode flag
 * @param filename: Custom path ya khali string (for auto-timestamp)
 */
bool RecordFile::saveGame(const Board& board, int moveCount, bool vsComputer, string filename) {
    if (filename == "") {
        filename = "saves/" + generateTimestampName();
        updateIndex(filename, vsComputer);
    }

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: File nahi khul saki save karne ke liye: " << filename << endl;
        return false;
    }

    file << moveCount << endl;
    file << (vsComputer ? 1 : 0) << endl;
    file << board.enPassantTarget.x << " " << board.enPassantTarget.y << endl;

    // Har square ke piece ki details save karein
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = board.getSquare(r, c);
            if (p == nullptr) {
                file << ". 0 0" << endl; // Khali square
            } else {
                file << p->getSymbol() << " " << (int)(p->getcolor() == PieceColor::WHITE_PIECE ? 0 : 1) 
                     << " " << (p->isFirstMove() ? 1 : 0) << endl;
            }
        }
    }

    // Side pieces (Captured pieces) save karein
    file << board.sidePieces.size() << endl;
    for (Piece* p : board.sidePieces) {
        file << p->getSymbol() << " " << (int)(p->getcolor() == PieceColor::WHITE_PIECE ? 0 : 1) << endl;
    }
    file.close();
    return true;
}

/**
 * Save ki hui file se data load karke board ko restore karta hai
 * @param board/moveCount/vsComputer: Reference variables to update
 * @param filename: Path of the file to load
 */
bool RecordFile::loadGame(Board& board, int& moveCount, bool& vsComputer, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: File nahi mil saki: " << filename << endl;
        return false;
    }

    if (!(file >> moveCount)) return false;

    int vc;
    if (!(file >> vc)) return false;
    vsComputer = (vc == 1);

    int epx, epy;
    if (!(file >> epx >> epy)) return false;
    board.enPassantTarget = Pos(epx, epy);

    // Purane board ke pieces delete karein takay memory leak na ho
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = board.getSquare(r, c);
            if (p != nullptr) delete p;
            board.setSquare(r, c, nullptr);
        }
    }

    // File se parh kar naye pieces create karein
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            char symbol;
            int colorInt, firstMove;
            if (!(file >> symbol >> colorInt >> firstMove)) return false;
            if (symbol == '.') continue;

            PieceColor color = (colorInt == 0) ? PieceColor::WHITE_PIECE : PieceColor::BLACK_PIECE;
            Piece* newPiece = nullptr;
            char lowerSym = tolower(symbol);
            
            // Piece type ke mutabiq object creation
            if (lowerSym == 'p') newPiece = new Pawn(Pos(r,c), color, "p", &board);
            else if (lowerSym == 'r') newPiece = new Rook(Pos(r,c), color, "r", &board);
            else if (lowerSym == 'n') newPiece = new Knight(Pos(r,c), color, "n", &board);
            else if (lowerSym == 'b') newPiece = new Bishop(Pos(r,c), color, "b", &board);
            else if (lowerSym == 'q') newPiece = new Queen(Pos(r,c), color, "q", &board);
            else if (lowerSym == 'k') newPiece = new King(Pos(r,c), color, "k", &board);

            if (newPiece) {
                newPiece->setFirstMove(firstMove == 1);
                board.setSquare(r, c, newPiece);
            }
        }
    }

    board.recalculateAllMoves(); // Load ke baad moves refresh karein
    file.close();
    return true;
}
