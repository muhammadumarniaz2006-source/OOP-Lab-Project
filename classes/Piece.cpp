 #include "Piece.hpp"
#include "Board.hpp"
 void Piece::generateMoves(int row,int col,Board& board){
    movecount=0;
    for(int r=0;r<8;r++){
        for(int c=0;c<8;c++){
           if(isvalidmove(row,col,r,c,board)){
            Possiblemove[movecount]={r,c};
            movecount++;
           }
        }
    }
 }
 