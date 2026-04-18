#include "Game.hpp"

void Game::gameLoop(){
    while(true){
        board.print_board();
        Pos from, to;
        cout << "\nEnter move: (from x, y (e4) --- to x, y (e5)): ";
        char fromFile, toFile;
        int fromRank, toRank;
        cin >> fromFile >> fromRank >> toFile >> toRank;
        
        from.x = 8 - fromRank;      // Row index (0-7)
        from.y = fromFile - 'a';    // Column index (0-7)
        
        to.x = 8 - toRank;          // Row index (0-7)
        to.y = toFile - 'a';        // Column index (0-7)
        
        cout << "From: Row " << from.x << " Col " << from.y << " To: Row " << to.x << " Col " << to.y << endl; // Debugging output 
        if(moveCount % 2 == 1){
            currentTurn = Color::WHITE;
        } else {
            currentTurn = Color::BLACK;
        }
        if(board.makeMove(from, to, currentTurn)){
            moveCount++;
        }
    }
}

void Game::menu(){
    cout << "Enter Choice";
    cin >> choice;
    switch(choice){
        case 1:
            gameLoop();
            break;
        default:
            break;
    }
}

Game::Game(){
    moveCount = 1; // Initialize move count to 1, indicating it's White's turn at the start of the game.
    board.initBoard();
    menu();
}