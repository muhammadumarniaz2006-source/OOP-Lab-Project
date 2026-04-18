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

//pieces ko  dynamic allocate kia hai takay movement easy hosakay .
void Board::initBoard() {
    for (int c = 0; c < 8; c++) {
        string pName = "PB" + to_string(c+1);
        squares[1][c] = new Pawn(Pos(1, c), Color::BLACK, pName, this);
    }
    for (int c = 0; c < 8; c++) {
        string pName = "PW" + to_string(c+1);
        squares[6][c] = new Pawn(Pos(6, c), Color::WHITE, pName, this);
    }
    squares[0][0] = new Rook(Pos(0, 0), Color::BLACK, "RB1", this);
    squares[0][7] = new Rook(Pos(0, 7), Color::BLACK, "RB2", this); 
    squares[7][0] = new Rook(Pos(7, 0), Color::WHITE, "WB1", this);
    squares[7][7] = new Rook(Pos(7, 7), Color::WHITE, "WB2", this); 
    
    squares[0][1] = new Knight(Pos(0, 1), Color::BLACK, "NB1", this); 
    squares[0][6] = new Knight(Pos(0, 6), Color::BLACK, "NB2", this); 
    squares[7][1] = new Knight(Pos(7, 1), Color::WHITE, "NW1", this); 
    squares[7][6] = new Knight(Pos(7, 6), Color::WHITE, "NW2", this); 
    
    squares[0][2] = new Bishop(Pos(0, 2), Color::BLACK, "BB1", this); 
    squares[0][5] = new Bishop(Pos(0, 5), Color::BLACK, "BB2", this);
    squares[7][2] = new Bishop(Pos(7, 2), Color::WHITE, "BW1", this);
    squares[7][5] = new Bishop(Pos(7, 5), Color::WHITE, "BW2", this);
    
    squares[0][3] = new Queen(Pos(0, 3), Color::BLACK, "QB", this);
    squares[7][3] = new Queen(Pos(7, 3), Color::WHITE, "QW", this);
    
    squares[0][4] = new King(Pos(0, 4), Color::BLACK, "KB", this);
    squares[7][4] = new King(Pos(7, 4), Color::WHITE, "KW", this);

    recalculateAllMoves(); // Initialize possible moves for all pieces after setting up the board, yeh isliye takay game start hone se pehle har piece ke possible moves calculate ho jayen, taki pehla move karte waqt valid moves available hon.

}

bool Board::isEmpty(Pos pos) const {
    if (pos.x < 0 || pos.x >= 8 || pos.y < 0 || pos.y >= 8) { return false; }//for validation inside board.
    return squares[pos.x][pos.y] == nullptr; //yai true return karay ga ager destination null and valid hogi.
}

bool Board::hasOpponent(Pos pos, Color myColor) const {
    if (pos.x < 0 || pos.x >= 8 || pos.y < 0 || pos.y >= 8)//yai validate keray ga kay move board ki boundry mai hai ya nhi.
        return false;

    Piece *target = squares[pos.x][pos.y];
    if (target == nullptr)  //ager us destination per koi piece nhi hai tu return false kerday ga.
        return false;

    return (target->getcolor() != myColor);//ager opponent piece hoga tu true return karay ga.
}

//yeh function same color piece check karke true return karega warna false
bool Board::hasMate(Pos pos, Color myColor) const {
    return (!hasOpponent(pos, myColor) && !(squares[pos.x][pos.y] == nullptr));
}

// yeh function boundary validation ke liye hai
bool Board::checkBoundary(Pos pos) const {
    return (( pos.x < 8 && pos.x >= 0 && pos.y >= 0 && pos.y < 8 ));
}

// yeh function valid move ko chala dega
bool Board::makeMove(Pos from, Pos to, Color currentTurn){

    // Check if it's the correct player's turn
    if(squares[from.x][from.y]->getcolor() != currentTurn){
        cout << "\nIt's not your turn!" << endl;
        return false;
    }
    
    // Check if positions are within boundaries
    if(!checkBoundary(from) || !checkBoundary(to)){
        cout << "\nMove out of bounds!" << endl;
        return false;
    }

    // Check if there is a piece at the source position
    if(isEmpty(from)){
        cout << "\nNo piece at source position!" << endl;
        return false;
    }

    // Check if the move is valid for that piece
    if(!squares[from.x][from.y]->isValidMove(to)){
        cout << "\nInvalid Move for this piece!" << endl;
        return false;
    }

    // yeh if condition opponent piece ko hatane ke liye hai --> side pieces vector main daalne ke liye
    if(hasOpponent(to, squares[from.x][from.y]->getcolor())){
        sidePieces.push_back(squares[to.x][to.y]);
        squares[to.x][to.y] = nullptr; // Clear the captured piece from the square before moving
    }
    
    // is line pe move hojayegi
    squares[to.x][to.y] = squares[from.x][from.y];
    // is line pe previous position ko null kardenge
    squares[from.x][from.y] = nullptr;
    
    // Piece ko apni new position update karni chahiye
    squares[to.x][to.y]->updatePos(to);

    // Update all pieces' possible moves
    recalculateAllMoves();

    // aur sab sahi raha to return true
    return true;
}

//Yeh function board ke har piece ke possible moves ko recalculate karega, taki game state ke hisab se valid moves update ho jayen. Yeh zaroori hai jab koi piece move karta hai ya capture hota hai, taki baaki pieces ke possible moves bhi sahi rahen.
void Board::recalculateAllMoves() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (squares[r][c] != nullptr) {
                squares[r][c]->calculatePossibleMoves();
            }
        }
    }
}


/*yai function piece ko move kernay aur delete kernay kay liay hai aur iski return type Piece isliay hai kay 
For example capturedPiece=Rook so function must return address of Rook in form of Piece* */
//  Piece* Board::makeMove(int fr,int fc,int tr,int tc)
// {
//     Piece* movingPiece = squares[fr][fc];
//     Piece* capturedPiece = squares[tr][tc];

//     squares[tr][tc] = movingPiece;
//     squares[fr][fc] = nullptr;

//     return capturedPiece;
// }
//jo upper wala function return karay ga captured ko wo ismai use hoga takay move undo kersakay.
// void Board::undoMove(int fr,int fc,int tr,int tc,Piece* capturedPiece)
// {
//     Piece* movingPiece = squares[tr][tc];//pointer isliay return kerwa rahay hai kio kay squares array of 2d pointers hai

//     squares[fr][fc] = movingPiece;
//     squares[tr][tc] = capturedPiece;
// }

void Board::print_board()
{
    string line = "   +---+---+---+---+---+---+---+---+";

    cout << endl << "     a   b   c   d   e   f   g   h" << endl;
    cout << line << endl;

    for (int i = 0; i < 8; i++)
    {
        cout << " " << (8-i) << " |";
        for (int j = 0; j < 8; j++)
        {
            if (squares[i][j] == nullptr)
                cout << " . |";
            else
                cout << " " << squares[i][j]->getSymbol() << " |";
        }
        cout << " " << (8-i) << endl;
        cout << line << endl;
    }

    cout << "     a   b   c   d   e   f   g   h" << endl;


    // for(int i = 0; i < 8; i++){
    //     for(int j = 0; j < 8; j++){
    //         if(squares[i][j] == nullptr) continue;
    //         squares[i][j]->debugPrintPossibleMoves();
    //     }
    // }

}