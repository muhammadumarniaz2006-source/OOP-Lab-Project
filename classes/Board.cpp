#include "Board.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp" 
using namespace std;

Board::Board() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            squares[r][c] = nullptr;
        }
    }
}

Board::~Board() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            delete squares[r][c];
            squares[r][c] = nullptr;
        }
    }
}
//pices ko  dynamic allocate kia hai takay movement easy hosakay .
void Board::initBoard() {
    for (int c = 0; c < 8; c++) {
        squares[1][c] = new Pawn(Color::BLACK);
        squares[1][c]->setBoard(this);
        squares[6][c] = new Pawn(Color::WHITE);
        squares[6][c]->setBoard(this);
    }
    squares[0][0] = new Rook(Color::BLACK); squares[0][0]->setBoard(this);
    squares[0][7] = new Rook(Color::BLACK); squares[0][7]->setBoard(this);
    squares[7][0] = new Rook(Color::WHITE); squares[7][0]->setBoard(this);
    squares[7][7] = new Rook(Color::WHITE); squares[7][7]->setBoard(this);
    
    squares[0][1] = new Knight(Color::BLACK); squares[0][1]->setBoard(this);
    squares[0][6] = new Knight(Color::BLACK); squares[0][6]->setBoard(this);
    squares[7][1] = new Knight(Color::WHITE); squares[7][1]->setBoard(this);
    squares[7][6] = new Knight(Color::WHITE); squares[7][6]->setBoard(this);
    
    squares[0][2] = new Bishop(Color::BLACK); squares[0][2]->setBoard(this);
    squares[0][5] = new Bishop(Color::BLACK); squares[0][5]->setBoard(this);
    squares[7][2] = new Bishop(Color::WHITE); squares[7][2]->setBoard(this);
    squares[7][5] = new Bishop(Color::WHITE); squares[7][5]->setBoard(this);
    
    squares[0][3] = new Queen(Color::BLACK); squares[0][3]->setBoard(this);
    squares[7][3] = new Queen(Color::WHITE); squares[7][3]->setBoard(this);
    
    squares[0][4] = new King(Color::BLACK); squares[0][4]->setBoard(this);
    squares[7][4] = new King(Color::WHITE); squares[7][4]->setBoard(this);
}

bool Board::isEmpty(int row, int col) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) { return false; }//for validation inside board.
    return squares[row][col] == nullptr;//yai true return karay ga ager destination true hoga.
}

bool Board::hasOpponent(int row, int col, Color myColor) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8)//yai validate keray ga kay move board ki boundry mai hai ya nhi.
        return false;

    Piece *target = squares[row][col];
    if (target == nullptr)  //ager us destination per koi piece nhi hai tu return false kerday ga.
        return false;

    return (target->getcolor() != myColor);//ager opponent piece hoga tu true return karay ga.
}
/*yai function piece ko move kernay aur delete kernay kay liay hai aur iski return type Piece isliay hai kay 
For example capturedPiece=Rook so function must return address of Rook in form of Piece* */
 Piece* Board::makeMove(int fr,int fc,int tr,int tc)
{
    Piece* movingPiece = squares[fr][fc];
    Piece* capturedPiece = squares[tr][tc];

    squares[tr][tc] = movingPiece;
    squares[fr][fc] = nullptr;

    return capturedPiece;
}
//jo upper wala function return karay ga captured ko wo ismai use hoga takay move undo kersakay.
void Board::undoMove(int fr,int fc,int tr,int tc,Piece* capturedPiece)
{
    Piece* movingPiece = squares[tr][tc];//pointer isliay return kerwa rahay hai kio kay squares array of 2d pointers hai

    squares[fr][fc] = movingPiece;
    squares[tr][tc] = capturedPiece;
}

void Board::print_board()
{
    string line = "   +---+---+---+---+---+---+---+---+";

    cout << endl << "     1   2   3   4   5   6   7   8" << endl;
    cout << line << endl;

    for (int i = 0; i < 8; i++)
    {
        cout << " " << (8-i) << " |";
        for (int j = 0; j < 8; j++)
        {
            if (squares[i][j] == nullptr)
                cout << " . |";
            else
                cout << " " << squares[i][j]->getsymbol() << " |";
        }
        cout << " " << (8-i) << endl;
        cout << line << endl;
    }

    cout << "     1   2   3   4   5   6   7   8" << endl;

}