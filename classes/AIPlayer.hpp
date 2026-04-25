#pragma once
#include <string>
#include <vector>
#include "Common.hpp"

// Windows handles ko void* ke taur par use karenge takay conflict na ho
typedef void* win_handle;

class AIPlayer {
private:
    win_handle hPipeWrite;
    win_handle hPipeRead;
    win_handle hProcess;
    int skillLevel;
    int searchDepth;

    void sendCommand(std::string command);
    std::string readResponse();

public:
    AIPlayer(std::string path);
    ~AIPlayer();

    void setDifficulty(int level);
    bool getBestMove(std::string fen, Pos& from, Pos& to, char& promotion);
    static void algebraicToPos(std::string move, Pos& from, Pos& to, char& promotion);
};
