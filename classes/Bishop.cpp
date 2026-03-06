#include "Bishop.hpp"
#include <cmath>

bool Bishop::isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) {
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
        if (!board.isEmpty(currRow, currCol))
            { return false; }
        currRow += rowstep;
        currCol += colstep;
    }
    return true;
} 
