#include "AIPlayer.hpp"
#include <iostream>
#include <sstream>

// Windows specific headers sirf yahan include honge takay Raylib se conflict na ho
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/**
 * Constructor: Stockfish process ko background mein start karta hai
 * @param path: Stockfish.exe file ka mukammal rasta (path)
 */
AIPlayer::AIPlayer(std::string path) : hPipeWrite(NULL), hPipeRead(NULL), hProcess(NULL), skillLevel(20), searchDepth(10) {
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE; // Handles ko child process mein allow karna
    saAttr.lpSecurityDescriptor = NULL;

    HANDLE hChildStd_OUT_Rd = NULL;
    HANDLE hChildStd_OUT_Wr = NULL;
    HANDLE hChildStd_IN_Rd = NULL;
    HANDLE hChildStd_IN_Wr = NULL;

    // Pipes banaye ja rahe hain takay Engine ko data bhej sakein aur wahan se parh sakein
    CreatePipe(&hChildStd_OUT_Rd, &hChildStd_OUT_Wr, &saAttr, 0);
    SetHandleInformation(hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0);
    CreatePipe(&hChildStd_IN_Rd, &hChildStd_IN_Wr, &saAttr, 0);
    SetHandleInformation(hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0);

    PROCESS_INFORMATION piProcInfo;
    STARTUPINFOA siStartInfo;
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFOA));

    siStartInfo.cb = sizeof(STARTUPINFOA);
    siStartInfo.hStdError = hChildStd_OUT_Wr;
    siStartInfo.hStdOutput = hChildStd_OUT_Wr;
    siStartInfo.hStdInput = hChildStd_IN_Rd;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES; // Pipes ko standard I/O ke taur par use karein

    // Engine ka process background mein baghair kisi window ke start ho raha hai
    if (CreateProcessA(NULL, (LPSTR)path.c_str(), NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &siStartInfo, &piProcInfo)) {
        hPipeWrite = (win_handle)hChildStd_IN_Wr;
        hPipeRead = (win_handle)hChildStd_OUT_Rd;
        hProcess = (win_handle)piProcInfo.hProcess;
        CloseHandle(piProcInfo.hThread);
        
        // Engine ko initialize karne ke liye standard commands
        sendCommand("uci");
        sendCommand("isready");
        setDifficulty(3); // Default to Hard
    } else {
        std::cerr << "Error: Stockfish engine nahi chal saka! Path check karein." << std::endl;
    }

    // Unused handles band kar rahe hain
    CloseHandle(hChildStd_OUT_Wr);
    CloseHandle(hChildStd_IN_Rd);
}

/**
 * Destructor: Engine process aur pipes ko band karta hai
 */
AIPlayer::~AIPlayer() {
    if (hProcess) {
        sendCommand("quit"); // Engine ko band hone ka signal
        CloseHandle((HANDLE)hPipeWrite);
        CloseHandle((HANDLE)hPipeRead);
        TerminateProcess((HANDLE)hProcess, 0);
        CloseHandle((HANDLE)hProcess);
    }
}

/**
 * Difficulty set karne ka function
 * @param level: 1 (Easy), 2 (Medium), 3 (Hard), 4 (Expert)
 */
void AIPlayer::setDifficulty(int level) {
    switch(level) {
        case 1: // Easy (~600-800 Elo)
            skillLevel = 0;
            searchDepth = 1;
            break;
        case 2: // Medium (~1200-1400 Elo)
            skillLevel = 5;
            searchDepth = 5;
            break;
        case 3: // Hard (~2000 Elo)
            skillLevel = 15;
            searchDepth = 10;
            break;
        case 4: // Expert (~3000 Elo)
            skillLevel = 20;
            searchDepth = 15;
            break;
        default:
            skillLevel = 20;
            searchDepth = 10;
            break;
    }
    sendCommand("setoption name Skill Level value " + std::to_string(skillLevel));
}

/**
 * Engine ko command bhejne ka function
 * @param command: UCI standard command (e.g., "go depth 10")
 */
void AIPlayer::sendCommand(std::string command) {
    if (!hPipeWrite) return;
    command += "\n";
    DWORD dwWritten;
    WriteFile((HANDLE)hPipeWrite, command.c_str(), command.length(), &dwWritten, NULL);
}

/**
 * Engine ka jawab line-by-line parhne ka function
 * @return: Engine se mili hui aik mukammal line
 */
std::string AIPlayer::readResponse() {
    if (!hPipeRead) return "";
    char buffer[4096];
    DWORD dwRead;
    std::string response = "";
    
    // Aik aik character parh kar line banayi ja rahi hai
    while (true) {
        if (!ReadFile((HANDLE)hPipeRead, buffer, 1, &dwRead, NULL) || dwRead == 0) break;
        response += buffer[0];
        if (buffer[0] == '\n') break;
    }
    return response;
}

/**
 * Best move dhoondne ka main function
 * @param fen: Board ki current state (FEN format mein)
 * @param from: (Output) AI ka selected start point
 * @param to: (Output) AI ka selected destination point
 * @param promotion: (Output) Agar pawn promote ho raha ho ('Q', 'R', etc.)
 */
bool AIPlayer::getBestMove(std::string fen, Pos& from, Pos& to, char& promotion) {
    if (!hProcess) return false;

    sendCommand("position fen " + fen);
    sendCommand("go depth " + std::to_string(searchDepth));

    std::string line;
    while (true) {
        line = readResponse();
        if (line.find("bestmove") != std::string::npos) {
            // Line format: "bestmove e2e4 ponder e7e5" ya "bestmove e7e8q"
            std::stringstream ss(line);
            std::string word, moveStr;
            ss >> word >> moveStr;
            
            algebraicToPos(moveStr, from, to, promotion);
            return true;
        }
    }
    return false;
}

/**
 * Algebraic moves ko board indices mein badalne wala static function
 * @param move: "e2e4" ya "e7e8q" string
 * @param from/to: Output positions (0-7 indices)
 */
void AIPlayer::algebraicToPos(std::string move, Pos& from, Pos& to, char& promotion) {
    if (move.length() < 4) return;
    // Columns: 'a' is index 0
    from.y = move[0] - 'a';
    to.y = move[2] - 'a';
    // Ranks: '8' is row 0, '1' is row 7
    from.x = 8 - (move[1] - '0');
    to.x = 8 - (move[3] - '0');
    
    // Agar promotion character maujood hai
    if (move.length() > 4) {
        promotion = toupper(move[4]);
    } else {
        promotion = ' ';
    }
}
