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
    // Saves current board state and move count to a file
    static bool saveGame(const Board& board, int moveCount, bool vsComputer, string filename);
    
    // Loads board state and move count from a file
    static bool loadGame(Board& board, int& moveCount, bool& vsComputer, string filename);

    // Helpers for timestamped saves
    static std::string generateTimestampName();
    static void updateIndex(std::string filename, bool vsComputer);
    static std::vector<SaveEntry> getSavedGamesList();
};
