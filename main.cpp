#include "classes/Board.hpp"
#include "classes/Piece.hpp"
#include <iostream>

using namespace std;

int main() {
    Board board;
    board.initBoard();
    
    cout << "Board initialized successfully!" << endl;
    
    // Test a piece
    if (board.squares[0][0] != nullptr) {
        cout << "Square (0,0) contains a piece." << endl;
    }

    return 0;
}
