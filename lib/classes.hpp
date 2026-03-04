#include <iostream>
#include <string>
#include <cmath>

using namespace std;
class Piece;
enum class Color
{
    WHITE,
    BLACK,
};
typedef struct
{
    int x;
    int y;
} Pos;
class Board
{
public:
    Piece *squares[8][8];
    Color color;
    Board()
{
  
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            squares[r][c] = nullptr;
        }
    }

}
~Board()
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            delete squares[r][c];
            squares[r][c] = nullptr;
        }
    }
}
void Board::initializeBoard()
{
   
    for (int c = 0; c < 8; c++)
    {
        squares[1][c] = new Pawn(BLACK);
        squares[6][c] = new Pawn(WHITE);
    }

    squares[0][0] = new Rook(Black);
    squares[0][7] = new Rook(BLACK);
    squares[7][0] = new Rook(WHITE);
    squares[7][7] = new Rook(WHITE);

    squares[0][1] = new Knight(BLACK);
    squares[0][6] = new Knight(BLACK);
    squares[7][1] = new Knight(WHITE);
    squares[7][6] = new Knight(WHITE);

    squares[0][2] = new Bishop(BLACK);
    squares[0][5] = new Bishop(BLACK);
    squares[7][2] = new Bishop(WHITE);
    squares[7][5] = new Bishop(WHITE);

    
    squares[0][3] = new Queen(BLACK);
    squares[7][3] = new Queen(WHITE);

    squares[0][4] = new King(BLACK);
    squares[7][4] = new King(WHITE);
}
    bool isempty(int row, int col)
    {

        if (row < 0 || row >= 8 || col < 0 || col >= 8)
            return false;

        return squares[row][col] == nullptr;
    }
    bool hasopponent(int row, int col, Color myColor)
    {

        if (row < 0 || row >= 8 || col < 0 || col >= 8)
            return false;

        Piece *target = squares[row][col];

        if (target == nullptr)
            return false;

        return (target->getcolor() != myColor);
    }
};
class Piece
{
private:
    Pos pos;

public:
    Color color;
    Board *board;
    string name;
    int *possibleMoves()
    {
        int arr[5]; // example func
        return arr;
    }
    Color getcolor(){
        return color;
    }
};
class Bishop : public Piece
{
    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board)
    {
        int rowdiff = fromRow - toRow;
        int coldiff = fromCol - toCol;
        if (abs(rowdiff) != abs(coldiff))
            return false;
        if (fromRow == toRow || fromCol == toCol)
            return false;
        if (!board.isempty(toRow, toCol) && !board.hasopponent(toRow, toCol, color))
            return false;
        int rowstep = (toRow > fromRow) ? 1 : -1;
        int colstep = (toCol > fromCol) ? 1 : -1;
        int currRow = fromRow + rowstep;
        int currCol = fromCol + colstep;
        while (currRow != toRow || currCol != toCol)
        {
            if (!board.isempty(currRow, currCol) && !board.hasopponent(currRow, currCol, color))
                return false;
            currRow += rowstep;
            currCol += colstep;
        }
        return true;
    }
};
class Rook : public Piece
{
    bool isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board)
    {
        int rowstep, colstep;
        int rowdiff = fromRow - toRow;
        int coldiff = fromCol - toCol;
        if (rowdiff == 0 && coldiff == 0)
            return false;
        if (rowdiff != 0 && coldiff != 0)
            return false;
        if (rowdiff != 0)
            rowstep = (toRow > fromRow) ? 1 : -1;
        else
            rowstep = 0;

        if (coldiff != 0)
            colstep = (toCol > fromCol) ? 1 : -1;
        else
            colstep = 0;
        int currRow = fromRow + rowstep;
        int currCol = fromCol + colstep;
        while (currRow != toRow || currCol != toCol)
        {
            if (!board.isempty(currRow, currCol) && !board.hasopponent(currRow, currCol, color))
                return false;
            currRow += rowstep;
            currCol += colstep;
        }
        return true;
    }
};