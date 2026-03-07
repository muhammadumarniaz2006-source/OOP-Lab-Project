#include "Rook.hpp"

bool Rook::isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) {
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
        if (!board.isEmpty(currRow, currCol)) { return false; }
        currRow += rowstep;
        currCol += colstep;
    }
    
    if (!board.isEmpty(toRow, toCol) && !board.hasOpponent(toRow, toCol, color)) { return false; }
    
    return true;

}

char Rook::getsymbol(){ 
    return (getcolor() == Color::WHITE) ? 'R' : 'r'; 
}
