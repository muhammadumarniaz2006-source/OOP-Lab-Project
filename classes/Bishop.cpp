#include "Bishop.hpp"
#include <cmath>
//override likhna optional hota hai.
/*Bishop logic:
    row difference and col difference nikal ker dono kko compare karay gay
    if dono brabar hai tu valid move hai ager destinated position per apna piece  na ho ya uskay rastay mai koi bhi dosra piece ho
*/
bool Bishop::isvalidmove(int fromRow, int fromCol, int toRow, int toCol, Board &board) {
    int rowdiff = fromRow - toRow;
    int coldiff = fromCol - toCol;
    if (abs(rowdiff) != abs(coldiff)) { return false; }
    
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
