#include "Pawn.hpp"
#include "Move.hpp"

Pawn::Pawn(Pos p, Color c, string name, Board* b): Piece(p, c, name, b) {
    if(getcolor() == Color::WHITE){
        Directions = {{-1,0}}; //White pawn ke liye direction upar ki taraf hai
    } else {
        Directions = {{1,0}}; //Black pawn ke liye direction neeche ki taraf hai
    }
    calculatePossibleMoves();
}

char Pawn::getSymbol(){
    return (getcolor() == Color::WHITE) ? 'P' : 'p';
}

void Pawn::calculatePossibleMoves() {
    Possiblemoves.clear();
    Possiblemoves = MoveGenerator::pawnMove(*board, pos, color, Directions[0], ifFirstMove);
}

// bool Pawn::isvalidmove(int from_row,int from_col,int to_row, int to_col, Board &board)
// {
//     int direction;      // direction variable jo batayega pawn upar jayega ya neeche
//     if(color==Piece::getcolor())
//     {
//         direction=-1;
//     }
//     else 
//     {
//         direction=1;
//     }
//     int row_diff=to_row-from_row;
//     int col_diff=to_col-from_col;

//     // Agar first move ho chuka hai mtlb ke kahin beech hai pawn
//     if(col_diff==0 && row_diff == direction && board.isEmpty(to_row,to_col))          //col move nhi hona chaye /sirff ek step row ki direction mai move hona chaye/ agay wala square empty hona chaye
//     {
//     move_two_square=false;      //kyun ke pawn beech mai kahin board ke hai
//     return true;
//     }

//     //Agar pawn base pe hai  / sirf phele move mai allow hai / column change nhi hoga/ 2 step move karega direction mai / jis step pe jaraha hai woh empty hona chaye/ jis step ko jump maar kar jaraha hai yani beech wala step bhi empty hona chaye
//     if(first_move && col_diff==0 &&row_diff==2*direction && board.isEmpty(to_row,to_col)&& board.isEmpty(from_row+direction, from_col))
//     {
//     move_two_square=true;   // 2 sqaure move hogaye
//     return true;
//     }

//     //Diagonal caputring / ek column left pe ya right pe / ek step agay direction / capturing ke baad jis box mai jaye ga woh empty hona chaye/ beech mai opponent ka piece hona chaye
//     if(abs(col_diff)==1 && row_diff==direction && !board.isEmpty(to_row,to_col) && board.hasOpponent(to_row, to_col, color))
//     {
//     move_two_square=false;  //caputring hai 2 step movement nhi hai 2 step mai beech hai koi piece nhi hota dono empty hote hain
//     return true;
//     }
//     return false;
// }



// char Pawn::getsymbol(){
//     return (getcolor() == Color::WHITE) ? 'P' : 'p'; 
// }
