#include "Move.hpp"
#include "Board.hpp"

vector<Pos> MoveGenerator::slidingMove(Board& board, Pos pos, Color color, vector<Dir> dirs){
    vector<Pos> moves;
    for(int i = 0; i < dirs.size(); i++){
        int j = 1;
        while(true){
            Pos newMove;
            newMove.x = pos.x + (dirs[i].x * j);
            newMove.y = pos.y + (dirs[i].y * j);
            
            if(!board.checkBoundary(newMove)){
                break;
            }
            
            if(board.hasMate(newMove, color)){
                break;
            }
            
            moves.push_back(newMove);  
            
            if(board.hasOpponent(newMove, color)){
                break;
            }
            j++;
        }
    }
    return moves;
}

vector<Pos> MoveGenerator::knightMove(Board& board, Pos pos, Color color, vector<Dir> dirs){
    vector<Pos> moves;
    for(int i = 0; i < dirs.size(); i++){
        Pos newMove;
        newMove.x = pos.x + dirs[i].x;
        newMove.y = pos.y + dirs[i].y;
        
        if(!board.checkBoundary(newMove) || board.hasMate(newMove, color)){
            continue;
        }
        
        moves.push_back(newMove);
    }
    return moves;
}

vector<Pos> MoveGenerator::pawnMove(Board& board, Pos pos, Color color, Dir dir, bool ifFirst){
    vector<Pos> moves;
    
    // Forward move
    Pos forward(pos.x + dir.x, pos.y);
    if(board.checkBoundary(forward) && board.isEmpty(forward)){
        moves.push_back(forward);
        
        // Double forward on first move
        if(ifFirst){
            Pos doubleForward(pos.x + 2 * dir.x, pos.y);
            if(board.checkBoundary(doubleForward) && board.isEmpty(doubleForward)){
                moves.push_back(doubleForward);
            }
        }
    }
    
    // Captures
    Pos capLeft(pos.x + dir.x, pos.y - 1);
    if(board.checkBoundary(capLeft) && board.hasOpponent(capLeft, color)){
        moves.push_back(capLeft);
    }
    
    Pos capRight(pos.x + dir.x, pos.y + 1);
    if(board.checkBoundary(capRight) && board.hasOpponent(capRight, color)){
        moves.push_back(capRight);
    }
    
    return moves;
}


vector<Pos> MoveGenerator::kingMove(Board& board, Pos pos, Color color, vector<Dir> dirs){
    vector<Pos> moves;
    for(int i = 0; i < dirs.size(); i++){
        Pos newMove;
        newMove.x = pos.x + dirs[i].x;
        newMove.y = pos.y + dirs[i].y;
        
        if(!board.checkBoundary(newMove) || board.hasMate(newMove, color)){
            continue;
        }
        
        moves.push_back(newMove);
    }
    return moves;
}
