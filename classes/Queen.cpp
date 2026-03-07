#include "Queen.hpp"
#include <cmath>
//bishop ya Rook mai say koi aik bhi true hoga tu queen truen kerday gi.
bool Queen :: isvalidmove(int from_row,int from_col,int to_row, int to_col, Board &board){
    return (Bishop::isvalidmove(from_row,from_col,to_row,to_col,board)||Rook::isvalidmove(from_row,from_col,to_row,to_col,board));
}