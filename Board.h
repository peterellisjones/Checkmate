/* 
 * File:   Board.h
 * Author: pj
 *
 * Created on January 7, 2013, 1:54 AM
 */

#ifndef BOARD_H
#define	BOARD_H

#include "Common.h"

class Board {
    friend class MoveGenerator;
    friend class Tests;
    
private:
    U64 bitboards[14];
    U8 board_array[64];
    
    struct IrreversibleData {
      U8 half_move_count;
      U8 castling_rights;
      U8 ep_square;
      U8 side_to_move;
    } irrev;
    
public:
    Board();
    bool is_blank();
    void add_piece(U8 piece, int square);
    void remove_piece(int square);
    void reset();
    U8 operator[](const int square) const; // return piece on that square
    U64 bitboard(const int type) const;
    U8 half_move_count() const { return irrev.half_move_count; };
    U8 castling_rights() const { return irrev.castling_rights; };
    U8 ep_square()       const { return irrev.ep_square; };
    U8 side_to_move()    const { return irrev.side_to_move; };
    void set_side_to_move(U8 side) { irrev.side_to_move = side; };
    void set_castling_rights(U8 rights) { irrev.castling_rights = rights; };
    void set_ep_square(U8 square) { irrev.ep_square = square; };
    void set_half_move_count(U8 count) { irrev.half_move_count = count; };
};

#endif	/* BOARD_H */

