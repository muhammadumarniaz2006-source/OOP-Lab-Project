#include<string>
#include<iostream>
#include "Board.hpp"

using namespace std;

enum class Color { WHITE, BLACK };

typedef struct {
    int x;
    int y;
} Pos;

class Piece{
private:
    Pos pos;

public:
    Color color;
    Board *board;
    string name;
    Piece(){}
    int *possibleMoves()
    {
        int arr[5]; // example func
        return arr;
    }
    Color getcolor(){
        return color;
    }
}; 