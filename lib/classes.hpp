#include <iostream>
#include <string>
#include <cmath>

using namespace std;
class Piece;
class Pawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;


enum class Color { WHITE, BLACK };

typedef struct {
    int x;
    int y;
} Pos;
class Piece;

class Board{
public:
    Piece *squares[8][8];
    Color color;
    Board(){
        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                squares[r][c] = nullptr;
            }
        }
    }
    ~Board(){
        for (int r = 0; r < 8; r++){
            for (int c = 0; c < 8; c++){
                delete squares[r][c];
                squares[r][c] = nullptr;
            }
        }
    }
void initBoard();
   
    bool isEmpty(int row, int col){
        if (row < 0 || row >= 8 || col < 0 || col >= 8) { return false; }
        return squares[row][col] == nullptr;
    }

    bool hasOpponent(int row, int col, Color myColor)
    {

        if (row < 0 || row >= 8 || col < 0 || col >= 8)
            return false;

        Piece *target = squares[row][col];

        if (target == nullptr)
            return false;

        return (target->getcolor() != myColor);
    }
};

class Piece{
private:
    Pos pos;

public:
    Color color;
    Board *board;
    string name;
   Piece(){}
    Piece(Color c){ color = c; }
    int *possibleMoves()
    {
        int arr[5]; // example func
        return arr;
    }
    Color getcolor(){
        return color;
    }
};

class Bishop :virtual public Piece
{
    public:
     Bishop(){}
    Bishop(Color c):Piece(c){}

    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board){
        int rowdiff = fromRow - toRow;
        int coldiff = fromCol - toCol;
        if (abs(rowdiff) != abs(coldiff)) { return false; }
        if (fromRow == toRow || fromCol == toCol) { return false; }
        if (!board.isEmpty(toRow, toCol) && !board.hasOpponent(toRow, toCol, color)) { return false; }
        int rowstep = (toRow > fromRow) ? 1 : -1;
        int colstep = (toCol > fromCol) ? 1 : -1;
        int currRow = fromRow + rowstep;
        int currCol = fromCol + colstep;
        while (currRow != toRow || currCol != toCol)
        {
            if (!board.isEmpty(currRow, currCol) && !board.hasOpponent(currRow, currCol, color))
                { return false; }
            currRow += rowstep;
            currCol += colstep;
        }
        return true;
    }
};

class Rook :virtual public Piece{
    public:
     Rook(){}
    Rook(Color c):Piece(c){}

    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board){
        int rowstep, colstep;
        int rowdiff = fromRow - toRow;
        int coldiff = fromCol - toCol;
        if (rowdiff == 0 && coldiff == 0) { return false; }
        if (rowdiff != 0 && coldiff != 0) { return false; }
        if (rowdiff != 0) { rowstep = (toRow > fromRow) ? 1 : -1; }
        else { rowstep = 0; }
        if (coldiff != 0) { colstep = (toCol > fromCol) ? 1 : -1; }
        else { colstep = 0; }
        int currRow = fromRow + rowstep;
        int currCol = fromCol + colstep;
        while (currRow != toRow || currCol != toCol){
            if (!board.isEmpty(currRow, currCol) && !board.hasOpponent(currRow, currCol, color)) { return false; }
            currRow += rowstep;
            currCol += colstep;
        }
        return true;
    }
};
class Queen: virtual public Piece,public Bishop,public Rook{
    public:
     Queen(){}
    Queen(Color c):Piece(c),Bishop(c),Rook(c){}
    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board){
 return Bishop::isvalidmove(fromRow,fromCol,toRow,toCol,board)|| Rook::isvalidmove(fromRow,fromCol,toRow,toCol,board);
    }
};
 void Board::initBoard(){
        for (int c = 0; c < 8; c++){
            squares[1][c] = new Pawn(Color::BLACK);
            squares[6][c] = new Pawn(Color::WHITE);
        }
        squares[0][0] = new Rook(Color::BLACK);
        squares[0][7] = new Rook(Color::BLACK);
        squares[7][0] = new Rook(Color::WHITE);
        squares[7][7] = new Rook(Color::WHITE);
        squares[0][1] = new Knight(Color::BLACK);
        squares[0][6] = new Knight(Color::BLACK);
        squares[7][1] = new Knight(Color::WHITE);
        squares[7][6] = new Knight(Color::WHITE);
        squares[0][2] = new Bishop(Color::BLACK);
        squares[0][5] = new Bishop(Color::BLACK);
        squares[7][2] = new Bishop(Color::WHITE);
        squares[7][5] = new Bishop(Color::WHITE);
        squares[0][3] = new Queen(Color::BLACK);
        squares[7][3] = new Queen(Color::WHITE);
        squares[0][4] = new King(Color::BLACK);
        squares[7][4] = new King(Color::WHITE);
    }
