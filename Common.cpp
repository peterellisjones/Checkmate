/* 
 * File:   Common.cpp
 * Author: pj
 * 
 * Created on January 7, 2013, 1:54 AM
 */

#include "Common.h"
#include "Output.h"

string static is_valid_move_err(U32 move, const class Board &board);

bool is_valid_move(U32 move, const class Board &board){
    string error = is_valid_move_err(move, board);
    if(string == "") return true;
    cerr << "INVALID MOVE: " << error << endl;
    return false;
}

string is_valid_move_err(U32 move, const class Board &board){
    int side = board.side_to_move();
    int from = move_from(move);
    int to = move_to(move);
    int mover = board[from];
    int captured = move_captured(move);
    int promote_to = move_promote_to(move);
    int flags = move_flags(move);
    // check castle first
    if(is_castle(move)){
        if((move & 0xFFFFFF) != 0) return "Castle move shouldn't have data in lower 3 bytes";
        if(move != KING_CASTLE && move != QUEEN_CASTLE) return "Invalid castle move";
        if(move == KING_CASTLE){
            if(side == WHITE){
                if(!(board.castling_rights() & WHITE_KING_SIDE)) return "White doesn't have king-side castling rights";
            } else {
                if(!(board.castling_rights() & BLACK_KING_SIDE)) return "Black doesn't have king-side castling rights";
            }
        }    
        if(move == QUEEN_CASTLE){
            if(side == WHITE){
                if(!(board.castling_rights() & WHITE_QUEEN_SIDE)) return "White doesn't have queen-side castling rights";
            } else {
                if(!(board.castling_rights() & BLACK_QUEEN_SIDE)) return "Black doesn't have queen-side castling rights";
            }
        }
        // still need to add checks
        assert(false); // implement stuff
    }
    if(mover == EMPTY) return "mover doesn't exist in board";
    if((mover&1) != side) return "mover belongs to wrong side";
    // if capture make sure something to capture
    if(is_capture(move) && !is_ep_capture(move)){
        if(captured == EMPTY) return "can't find captured piece";
        if((captured&1) == side) return "can't capture friendly piece";
    }
    // if EP capture make sure correct square
    if(is_ep_capture(move)){
        if(side == BLACK){
            if(board.ep_square() != to) return "no ep square set";
            if(mover != BLACK_PAWN) return "can't ep move non-pawn";
            if(captured != WHITE_PAWN) return "can't ep capture non-pawn";
            if((from & 56) != (3*8)) return "ep capture from wrong row";
            if((to & 56) != (2*8)) return "ep capture to wrong row";
        } else {
            if(board.ep_square() != to) return "no ep square set";
            if(mover != WHITE_PAWN) return "can't ep move non-pawn";
            if(captured != BLACK_PAWN) return "can't ep capture non-pawn";
            if((from & 56) != (4*8)) return "ep capture from wrong row";
            if((to & 56) != (5*8)) return "ep capture to wrong row";      
        }
    }
    // if promotion make sure on right square
    if(is_promotion(move)){
        if(side == BLACK){
            if((from & 56) != (1*8)) return "promotion from wrong row";
            if((to & 56) != (0*8)) return "promotion to wrong row";
            if(promote_to != BLACK_QUEEN && 
               promote_to != BLACK_ROOK &&
               promote_to != BLACK_BISHOP &&
               promote_to != BLACK_KNIGHT) return "invalid promote_to piece";            
        } else {
            if((from & 56) != (6*8)) return "promotion from wrong row";
            if((to & 56) != (7*8)) return "promotion to wrong row";
            if(promote_to != WHITE_QUEEN && 
               promote_to != WHITE_ROOK &&
               promote_to != WHITE_BISHOP &&
               promote_to != WHITE_KNIGHT) return "invalid promote_to piece";         
        }
    }
    if(is_pawn_double_push(move)){
        if(side == BLACK){
            if((from & 56) != (6*8)) return "pawn double push from wrong row";
            if((to & 56) != (4*8)) return "pawn double push to wrong row";
            if(from-to != 16) return "pawn double push should move two rows";
            if(mover != BLACK_PAWN) return "only pawn can pawn double push";            
        } else {
            if((from & 56) != (1*8)) return "pawn double push from wrong row";
            if((to & 56) != (3*8))return "pawn double push to wrong row";
            if(to-from != 16) return "pawn double push should move two rows";
            if(mover != WHITE_PAWN) return "only pawn can pawn double push";
        }
    }
    U32 rows = abs((from&56)-(to&56))>>3; 
    U32 files = abs((from&7)-(to&7));      
    // if knight make sure rows moved ^ files moves = 3
    if((mover&(~1))==KNIGHT){
        if((rows^files) != 3) return "knight must move 2 rows and 1file (or vice versa)";
    }
    // if pawn make sure rows moved and files moved make sense
    if((mover&(~1))==PAWN){
        if(rows > 2) return "pawn can't move more than 2 rows";
        if(rows == 0) return "pawn must move 1 row";
        if(files > 1) return "pawn can't move more than 1 file";
    }
    // if king check rows and files 0 or 1
    if((mover&(~1))==KING){
        if(rows > 1) return "king can't move more than 1 row";
        if(files > 1) return "king can't move more than 1 file";
    }
    return "";
}