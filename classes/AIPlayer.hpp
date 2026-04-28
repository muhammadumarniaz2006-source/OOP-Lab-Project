#pragma once
#include <string>
#include <vector>
#include "Common.hpp"

// Windows handles ko void* ke taur par use karenge takay conflict na ho
typedef void* win_handle;

class AIPlayer {
private:
    win_handle hPipeWrite; // Engine ko commands bhejne ke liye pipe handle
    win_handle hPipeRead;  // Engine se jawab parhne ke liye pipe handle
    win_handle hProcess;   // Stockfish engine ka process handle
    int skillLevel;        // AI ki skill level (0-20)
    int searchDepth;       // AI kitni gehrai (depth) tak sochega

    // Engine ko UCI command bhejne wala function
    void sendCommand(std::string command);
    // Engine ka response parhne wala function
    std::string readResponse();

public:
    // Constructor: Engine process start karta hai
    AIPlayer(std::string path);
    // Destructor: Engine process band karta hai
    ~AIPlayer();

    // Difficulty level (1-4) set karta hai
    void setDifficulty(int level);
    // Board state ke mutabiq best move dhoondta hai
    bool getBestMove(std::string fen, Pos& from, Pos& to, char& promotion);
    // "e2e4" jaise algebraic notation ko Pos coordinates mein badalta hai
    static void algebraicToPos(std::string move, Pos& from, Pos& to, char& promotion);
};
