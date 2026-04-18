#include "Board.hpp"
#include "Piece.hpp"

class Game{
    private:
        Board board;
        int moveCount; //odd moves for white and even moves for black
        Color currentTurn; // To keep track of whose turn it is
        int choice;
    public:
        void gameLoop();
        Game();
        void menu();
};