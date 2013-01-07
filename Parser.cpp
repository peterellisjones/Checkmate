/* 
 * File:   Parser.cpp
 * Author: pj
 * 
 * Created on January 7, 2013, 11:03 PM
 */

#include "Parser.h"

class Board Parser::parse_fen(string fen){
    Board board = Board();
    
    int len = string::size(fen);   
    
    int pos = 0; // position in string
    int square = A1;
    
    // 8 rows of pieces
    for(int row = 7; row >= 0; row--){
        while(fen[pos] == '/') pos++;
        for(int col = 0; col < 8; col++){
            char c = fen[pos++];
            // if number skip ahead that many columns
            if (c >= '1' && c <= '8'){
                col += c - '1';
            } else { // find piece
                U8 piece = parse_piece(c);
                if(piece) board.add_piece(piece, (row << 3) | col);
            }
        }        
    }
    while(fen[pos] != ' ') if (pos++ >= len) return board;
    while(fen[pos] == ' ') if (pos++ >= len) return board;
    
    // side to move
    U8 side_to_move = Parser::side(fen[pos++]);
    board.set_side_to_move(side_to_move);
    
    while(fen[pos] == ' ') if (pos++ >= len) return board;
    
    // castling rights
    U8 rights = 0;
    while(fen[pos++] != ' '){
        rights |= Parser::castling_right(fen[pos]);
    }
    
    while(fen[pos] == ' ') if (pos++ >= len) return board;
    
    // ep square
    if(fen[pos] == '-') { 
        pos++;    
    } else {
        char square[2] = {fen[pos], fen[pos+1]};
        board.set_ep_square(Parser::square(square));
        while(fen[pos] != ' ') if (pos++ >= len) return board;
    }    
    
    while(fen[pos] == ' ') if (pos++ >= len) return board;
    
    // half-move-count
    int half_move_count = 0;
    while(fen[pos] >= '0' && fen[pos] <= '9'){
        half_move_count = half_move_count * 10 + (fen[pos] - '0');
        if (pos++ >= len) return board;
    }
    
    board.set_half_move_count(half_move_count);
        
    while(fen[pos] == ' ') if (pos++ >= len) return board;
    
    // full-move-count
    int full_move_count = 0;
    while(fen[pos] != ' '){
        full_move_count = full_move_count * 10 + (fen[pos] - '0');
        if (pos++ >= len) return board;
    }
    
    return board;
}

U8 Parser::parse_piece(char piece){
    for(int i = 2; i < 14; i++){
        if(PIECE_CHARS[i] == piece) return i;
    }
    return EMPTY;
}

U8 Parser::side(char c){
    if(c == 'b' || c == 'B') return BLACK;
    return WHITE;
}

U8 Parser::castling_right(char c){
    switch(c){
        case 'K': return WHITE_KING_SIDE;
        case 'Q': return WHITE_QUEEN_SIDE;
        case 'k': return BLACK_KING_SIDE;
        case 'q': return BLACK_QUEEN_SIDE;
    }
    return 0;
}

U8 Parser::square(char sq[]){
    int col = sq[0] - 'a';
    int row = sq[1] - '1';
    return (row << 3) | col;
}