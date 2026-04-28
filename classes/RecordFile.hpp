#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Board.hpp"

using namespace std;

struct SaveEntry {
    std::string filename;
    std::string date;
    std::string mode;
};

class RecordFile {
public:
    // Poori game ki state (board, moves, pieces) ko file mein mehfooz karta hai.
    static bool saveGame(const Board& board, int moveCount, bool vsComputer, string filename);
    
    // Save ki hui file se game wapis restore karta hai.
    static bool loadGame(Board& board, int& moveCount, bool& vsComputer, string filename);

    // Har save file ke liye waqt ke mutabiq anokha naam banata hai.
    static std::string generateTimestampName();
    // Index file ko update karta hai takay list dikhai ja sakay.
    static void updateIndex(std::string filename, bool vsComputer);
    // Saved games ki mukammal list return karta hai.
    static std::vector<SaveEntry> getSavedGamesList();
};
