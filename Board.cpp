/* 
 * File:   Board.cpp
 * Author: pj
 * 
 * Created on January 7, 2013, 1:54 AM
 */

#include "Board.h"

Board::Board() {
    reset();
}

bool Board::is_blank(){
    return !(bitboards[WHITE] | bitboards[BLACK]);
}

void Board::add_piece(U8 piece, int square){
#ifdef DEBUG
    assert(is_valid_piece(piece));
    assert(is_valid_square(square));
    assert(board_array[square] == EMPTY);
#endif
    board_array[square] = piece;
    U64 bitboard = 1ULL << square;
    bitboards[piece & 1] |= bitboard;
    bitboards[piece] |= bitboard;
}

void Board::remove_piece(int square){
#ifdef DEBUG
    assert(is_valid_square(square));
    assert(board_array[square] != EMPTY);
#endif
    U8 piece = board_array[square];
    board_array[square] = EMPTY;
    U64 bitboard = ~(1ULL << square);
    bitboards[piece & 1] &= bitboard;
    bitboards[piece]     &= bitboard;
}

void Board::reset(){
    for(int i = 0; i < 64; i++){
        board_array[i] = EMPTY;
    }
    for(int i = 0; i < 14; i++){
        bitboards[i] = 0ULL;
    }
    irrev.half_move_count = 0;
    irrev.castling_rights = FULL_CASTLING_RIGHTS;
    irrev.ep_square = NULL_SQUARE;
    irrev.side_to_move = WHITE;
}

U8 Board::operator [](const int square) const{
#ifdef DEBUG
    assert(is_valid_square(square));
#endif
    return board_array[square];
}

U64 Board::bitboard(const int type) const{
#ifdef DEBUG
    assert(type >= 0 && type <= BLACK_QUEEN);
#endif
    return bitboards[type];
}