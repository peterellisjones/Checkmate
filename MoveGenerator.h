/* 
 * File:   MoveGenerator.h
 * Author: pj
 *
 * Created on January 16, 2013, 2:49 PM
 */

#ifndef MOVEGENERATOR_H
#define	MOVEGENERATOR_H

#include "Common.h"
#include "MoveList.h"
#include "Move.h"
#include "Board.h"
#include "Output.h"

class MoveGenerator {
    
public:
    static void add_pawn_pushes(class MoveList &list, const class Board &board, const int side);
    static void add_pawn_double_pushes(class MoveList &list, const class Board &board, const int side);
    static void add_pawn_attacks(class MoveList &list, const class Board &board, const int side);
    
    static void add_knight_moves(class MoveList &list, const class Board &board, const int side);
    static void add_king_moves(class MoveList &list, const class Board &board, const int side);
    
    static void generate_move_lookup_tables();
    
private:
    // diff is positive number denoting fixed distance between from and to squares such that:
    // from = (to - diff) % 64
    // ie white pawn push diff = 56, black pawn push diff = 8
    // add_moves assumes moving to blank square
    static void add_moves(U8 from, U64 targets, class MoveList &list, const class Board &board, const U32 flags);
    static void add_moves_with_diff(int diff, U64 targets, class MoveList &list, const class Board &board, const U32 flags);
    static void add_promotions_with_diff(int diff, U64 targets, class MoveList &list, const class Board &board, const U32 flags);
};

#endif	/* MOVEGENERATOR_H */

