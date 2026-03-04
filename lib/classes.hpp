#include <iostream>
#include <string>
#include <cmath>

using namespace std;
class Piece;
enum class Color { WHITE, BLACK };
typedef struct
{
    int x;
    int y;
} Position;
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
void initializeBoard()
{
   
    for (int c = 0; c < 8; c++)
    {
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
    Position pos;

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

class Pawn : public Piece
{
private:
    bool first_move;
    bool move_two_square;

public:
    Pawn():Piece()
    {
        first_move=true;
        move_two_square=false;
    }

    bool isvalidmove(int from_row,int from_col,int to_row, int to_col, Board &board)
    {
        int direction;      // direction variable jo batayega pawn upar jayega ya neeche
        if(color==Piece::getcolor())
        {
            direction=-1;
        }
        else 
        {
            direction=1;
        }
       int row_diff=to_row-from_row;
       int col_diff=to_col-from_col;

       // Agar first move ho chuka hai mtlb ke kahin beech hai pawn
       if(col_diff==0 && row_diff== direction && board.isempty(to_row,to_col))          //col move nhi hona chaye /sirff ek step row ki direction mai move hona chaye/ agay wala square empty hona chaye
       {
        move_two_square=false;      //kyun ke pawn beech mai kahin board ke hai
        return true;
       }

       //Agar pawn base pe hai  / sirf phele move mai allow hai / column change nhi hoga/ 2 step move karega direction mai / jis step pe jaraha hai woh empty hona chaye/ jis step ko jump maar kar jaraha hai yani beech wala step bhi empty hona chaye
       if(first_move && col_diff==0 &&row_diff==2*direction && board.isempty(to_row,to_col)&& board.isempty(from_row+direction, from_col))
       {
        move_two_square=true;   // 2 sqaure move hogaye
        return true;
       }

       //Diagonal caputring / ek column left pe ya right pe / ek step agay direction / capturing ke baad jis box mai jaye ga woh empty hona chaye/ beech mai opponent ka piece hona chaye
       if(abs(col_diff)==1 && row_diff==direction && !board.isempty(to_row,to_col) && board.hasopponent(to_row, to_col, color))
       {
        move_two_square=false;  //caputring hai 2 step movement nhi hai 2 step mai beech hai koi piece nhi hota dono empty hote hain
        return true;
       }

    }
};