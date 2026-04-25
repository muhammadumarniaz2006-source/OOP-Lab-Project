#include "Move.hpp"
#include "Board.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"

vector<Pos> MoveGenerator::slidingMove(Board& board, Piece* piece, bool checkSafety){
    vector<Pos> moves;
    for(int i = 0; i < piece->Directions.size(); i++){
        int j = 1;
        while(true){
            Pos newMove;
            newMove.x = piece->pos.x + (piece->Directions[i].x * j);
            newMove.y = piece->pos.y + (piece->Directions[i].y * j);
            
            if(!board.checkBoundary(newMove)){
                break;
            }
            
            if(board.hasMate(newMove, piece->color)){
                break;
            }
            if(checkSafety && board.checkPin(piece, newMove)){
                // CRITICAL FIX: Even if the move is illegal (pinned), 
                // if there is a piece here, it BLOCKS the path.
                if(!board.isEmpty(newMove)) break; 
                j++; 
                continue;
            }
            moves.push_back(newMove);  
            
            if(board.hasOpponent(newMove, piece->color)){
                break;
            }
            j++;
        }
    }
    return moves;
}

vector<Pos> MoveGenerator::knightMove(Board& board, Knight* knight, bool checkSafety){
    vector<Pos> moves;
    for(int i = 0; i < knight->Directions.size(); i++){
        Pos newMove;
        newMove.x = knight->pos.x + knight->Directions[i].x;
        newMove.y = knight->pos.y + knight->Directions[i].y;
        
        if(!board.checkBoundary(newMove) || board.hasMate(newMove, knight->color)){
            continue;
        }
        if(checkSafety && board.checkPin(knight, newMove)){
            continue;
        }
        moves.push_back(newMove);
    }
    return moves;
}

vector<Pos> MoveGenerator::pawnMove(Board& board, Pawn* pawn, bool checkSafety){
    vector<Pos> moves;
    // Forward move
    Pos forward(pawn->pos.x + pawn->Directions[0].x, pawn->pos.y);
    if(board.checkBoundary(forward) && board.isEmpty(forward)){
        if(!checkSafety || !board.checkPin(pawn, forward)){
            moves.push_back(forward);
        }
    }
    // Double forward on first move
    if(pawn->ifFirstMove){
        Pos forward1(pawn->pos.x + pawn->Directions[0].x, pawn->pos.y);
        Pos doubleForward(pawn->pos.x + 2 * pawn->Directions[0].x, pawn->pos.y);
        if(board.checkBoundary(doubleForward) && board.isEmpty(forward1) && board.isEmpty(doubleForward)){
            if(!checkSafety || !board.checkPin(pawn, doubleForward)){
                moves.push_back(doubleForward);
            }
        }
    }
    // Captures
    Pos capLeft(pawn->pos.x + pawn->Directions[0].x, pawn->pos.y - 1);
    if(board.checkBoundary(capLeft) && board.hasOpponent(capLeft, pawn->color)){
        if(!checkSafety || !board.checkPin(pawn, capLeft)){
            moves.push_back(capLeft);
        }
    }
    
    Pos capRight(pawn->pos.x + pawn->Directions[0].x, pawn->pos.y + 1);
    if(board.checkBoundary(capRight) && board.hasOpponent(capRight, pawn->color)){
        if(!checkSafety || !board.checkPin(pawn, capRight)){
            moves.push_back(capRight);
        }
    }

    // En Passant Move Generation
    // Check if either diagonal forward square is the current enPassantTarget
    Pos epLeft(pawn->pos.x + pawn->Directions[0].x, pawn->pos.y - 1);
    Pos epRight(pawn->pos.x + pawn->Directions[0].x, pawn->pos.y + 1);

    if (board.checkBoundary(epLeft) && epLeft == board.enPassantTarget) {
        // En Passant ke liye bhi pin check karna zaroori hai
        if (!checkSafety || !board.checkPin(pawn, epLeft)) {
            moves.push_back(epLeft);
        }
    }
    if (board.checkBoundary(epRight) && epRight == board.enPassantTarget) {
        if (!checkSafety || !board.checkPin(pawn, epRight)) {
            moves.push_back(epRight);
        }
    }
    
    return moves;
}

vector<Pos> MoveGenerator::kingMove(Board& board, King& king, bool checkSafety){
    vector<Pos> moves;
    for(int i = 0; i < king.Directions.size(); i++){
        Pos newMove;
        newMove.x = king.pos.x + king.Directions[i].x;
        newMove.y = king.pos.y + king.Directions[i].y;
        if(!board.checkBoundary(newMove) || board.hasMate(newMove, king.color)) continue;
        
        // Base case: if not checking safety, just add the move (avoids recursion)
        if(checkSafety && board.kingCheckValidation(king, newMove)) continue;
        
        moves.push_back(newMove);
    }

    // Castling Logic
    // King aur Rook dono ne pehle move na kiya ho, aur rasta khali ho
    if (checkSafety && king.isFirstMove() && !board.isCheck(king.getcolor())) {
        int r = king.getPos().x;
        
        // 1. King-side Castling (Short)
        Piece* rookShort = board.getSquare(r, 7);
        if (rookShort != nullptr && rookShort->isFirstMove()) {
            // Beech ke squares khali aur safe honay chahiyen
            if (board.isEmpty(Pos(r, 5)) && board.isEmpty(Pos(r, 6))) {
                if (!board.isSquareAttacked(Pos(r, 5), (king.getcolor() == PieceColor::WHITE_PIECE ? PieceColor::BLACK_PIECE : PieceColor::WHITE_PIECE)) &&
                    !board.isSquareAttacked(Pos(r, 6), (king.getcolor() == PieceColor::WHITE_PIECE ? PieceColor::BLACK_PIECE : PieceColor::WHITE_PIECE))) {
                    moves.push_back(Pos(r, 6));
                }
            }
        }

        // 2. Queen-side Castling (Long)
        Piece* rookLong = board.getSquare(r, 0);
        if (rookLong != nullptr && rookLong->isFirstMove()) {
            if (board.isEmpty(Pos(r, 1)) && board.isEmpty(Pos(r, 2)) && board.isEmpty(Pos(r, 3))) {
                if (!board.isSquareAttacked(Pos(r, 2), (king.getcolor() == PieceColor::WHITE_PIECE ? PieceColor::BLACK_PIECE : PieceColor::WHITE_PIECE)) &&
                    !board.isSquareAttacked(Pos(r, 3), (king.getcolor() == PieceColor::WHITE_PIECE ? PieceColor::BLACK_PIECE : PieceColor::WHITE_PIECE))) {
                    moves.push_back(Pos(r, 2));
                }
            }
        }
    }
    
    return moves;
}