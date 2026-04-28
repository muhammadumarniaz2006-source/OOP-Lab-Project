#include "Move.hpp"
#include "Board.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"

// slidingMove: Queen, Rook, aur Bishop ke liye rasta clear hone tak moves calculate karta hai.
vector<Pos> MoveGenerator::slidingMove(Board& board, Piece* piece, bool checkSafety){
    vector<Pos> moves;
    for(int i = 0; i < piece->Directions.size(); i++){
        int j = 1;
        while(true){
            Pos newMove;
            newMove.x = piece->pos.x + (piece->Directions[i].x * j);
            newMove.y = piece->pos.y + (piece->Directions[i].y * j);
            
            if(!board.checkBoundary(newMove)) break;
            
            // Cannot capture own piece
            if(board.hasMate(newMove, piece->color)) break;
            
            // If we are checking safety (check/pin), verify if move is legal
            if(checkSafety) {
                if(!board.checkPin(piece, newMove)) {
                    moves.push_back(newMove);
                }
            } else {
                // For attack range calculation, we don't care about pins
                moves.push_back(newMove);
            }
            
            // If square is occupied (by opponent or friend), path is blocked
            if(!board.isEmpty(newMove)) break;
            j++;
        }
    }
    return moves;
}

// knightMove: Knight (Ghoray) ki unique 'L' shaped moves calculate karta hai.
vector<Pos> MoveGenerator::knightMove(Board& board, Knight* knight, bool checkSafety){
    vector<Pos> moves;
    for(int i = 0; i < knight->Directions.size(); i++){
        Pos newMove;
        newMove.x = knight->pos.x + knight->Directions[i].x;
        newMove.y = knight->pos.y + knight->Directions[i].y;
        
        if(!board.checkBoundary(newMove)) continue;
        if(board.hasMate(newMove, knight->color)) continue;
        
        if(checkSafety) {
            if(!board.checkPin(knight, newMove)) moves.push_back(newMove);
        } else {
            moves.push_back(newMove);
        }
    }
    return moves;
}

// pawnMove: Pawn ki sidhi movement aur diagonal capturing (samait En Passant) calculate karta hai.
vector<Pos> MoveGenerator::pawnMove(Board& board, Pawn* pawn, bool checkSafety){
    vector<Pos> moves;
    
    // Normal Move Calculation (including safety)
    if(checkSafety) {
        // Forward 1
        Pos forward(pawn->pos.x + pawn->Directions[0].x, pawn->pos.y);
        if(board.checkBoundary(forward) && board.isEmpty(forward)){
            if(!board.checkPin(pawn, forward)) moves.push_back(forward);
            
            // Forward 2
            if(pawn->ifFirstMove) {
                Pos doubleForward(pawn->pos.x + 2 * pawn->Directions[0].x, pawn->pos.y);
                if(board.checkBoundary(doubleForward) && board.isEmpty(doubleForward)){
                    if(!board.checkPin(pawn, doubleForward)) moves.push_back(doubleForward);
                }
            }
        }
        
        // Diagonals (Normal captures + En Passant)
        int cols[] = {pawn->pos.y - 1, pawn->pos.y + 1};
        for(int c : cols) {
            Pos diag(pawn->pos.x + pawn->Directions[0].x, c);
            if(board.checkBoundary(diag)) {
                if(board.hasOpponent(diag, pawn->color) || diag == board.enPassantTarget) {
                    if(!board.checkPin(pawn, diag)) moves.push_back(diag);
                }
            }
        }
    } else {
        // Only diagonal attacks for isSquareAttacked
        int cols[] = {pawn->pos.y - 1, pawn->pos.y + 1};
        for(int c : cols) {
            Pos diag(pawn->pos.x + pawn->Directions[0].x, c);
            if(board.checkBoundary(diag)) moves.push_back(diag);
        }
    }
    
    return moves;
}

// kingMove: King ki 1-step moves aur Castling (short/long) ki sharait check karke moves deta hai.
vector<Pos> MoveGenerator::kingMove(Board& board, King& king, bool checkSafety){
    vector<Pos> moves;
    for(int i = 0; i < king.Directions.size(); i++){
        Pos newMove;
        newMove.x = king.pos.x + king.Directions[i].x;
        newMove.y = king.pos.y + king.Directions[i].y;
        
        if(!board.checkBoundary(newMove)) continue;
        if(board.hasMate(newMove, king.color)) continue;
        
        if(checkSafety) {
            if(!board.kingCheckValidation(king, newMove)) moves.push_back(newMove);
        } else {
            moves.push_back(newMove);
        }
    }

    // Castling Logic (Only if checking safety)
    if (checkSafety && king.ifFirstMove && !board.isCheck(king.color)) {
        int r = king.pos.x;
        PieceColor opponent = (king.color == PieceColor::WHITE_PIECE ? PieceColor::BLACK_PIECE : PieceColor::WHITE_PIECE);
        
        // King-side
        Piece* r1 = board.getSquare(r, 7);
        if (r1 && r1->isFirstMove() && board.isEmpty(Pos(r, 5)) && board.isEmpty(Pos(r, 6))) {
            if (!board.isSquareAttacked(Pos(r, 5), opponent) && !board.isSquareAttacked(Pos(r, 6), opponent)) {
                moves.push_back(Pos(r, 6));
            }
        }
        
        // Queen-side
        Piece* r2 = board.getSquare(r, 0);
        if (r2 && r2->isFirstMove() && board.isEmpty(Pos(r, 1)) && board.isEmpty(Pos(r, 2)) && board.isEmpty(Pos(r, 3))) {
            if (!board.isSquareAttacked(Pos(r, 2), opponent) && !board.isSquareAttacked(Pos(r, 3), opponent)) {
                moves.push_back(Pos(r, 2));
            }
        }
    }
    
    return moves;
}
