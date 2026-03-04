#include<iostream>
#include<string>
#include<cmath>

using namespace std;
enum class Color{White,Black};
typedef struct{
    int x;
    int y;
} Pos;
class Board{
    public:
    Color color;
    bool isempty(int row,int col){

    }
    bool hasopponent(int row,int col,Color c){

    }
};
class Piece{
    private:
        Pos pos;
    public:
    Color color;
    Board *board;
        string name;
        int* possibleMoves(){
            int arr[5];  //example func
            return arr;
        }
        
};
class Bishop: public Piece{
    bool isvalidmove(int fromRow,int fromCol,int toRow,int toCol,Board& board){
        int rowdiff=fromRow-toRow;
        int coldiff=fromCol-toCol;
        if(abs(rowdiff)!=abs(coldiff)) return false;
        if(fromRow==toRow||fromCol==toCol) return false;
        if(board.hasopponent(toRow,toCol,color)) return false; 
        int rowstep=(toRow>fromRow)? 1 : -1;
        int colstep=(toCol>fromCol) ? 1: -1;
        int currRow=fromRow+rowstep;
        int currCol=fromCol+colstep;
        while(currRow!=toRow && currCol!=toCol){
            if(!board.isempty(currCol,currRow)) return false;
            currRow+=rowstep;
            currCol+=colstep;
        }
        return true;
    }
};