#include "Rook.hpp"
/*Rook logic:
      row difference and col difference nikal ker dono ko check  karay gay
    if dono mai say koi aik bhi 0 hai  hai tu valid move hai aur ager destinated position per apna piece  na ho ya uskay rastay mai koi bhi dosra piece ho 
*/
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
        if (!board.isEmpty(currRow, currCol)) { return false; }//rastay mai aai har piece ko check ker raha hai kay wo empty ha ya nhi ager empty nhi oa tu false return kerday ga
        currRow += rowstep;//for next step
        currCol += colstep;//for next step
    }
    
    if (!board.isEmpty(toRow, toCol) && !board.hasOpponent(toRow, toCol, color)) { return false; }//ager destination per opponent ka piece na ho ya apna piece bhi hotu usi waqt false reurn kerdo
    
    return true;

}

char Rook::getsymbol(){ 
    return (getcolor() == Color::WHITE) ? 'R' : 'r'; 
}
