/* 
 * File:   Output.h
 * Author: pj
 *
 * Created on January 7, 2013, 11:38 PM
 */

#ifndef OUTPUT_H
#define	OUTPUT_H

#include "Common.h"
#include "Board.h"
#include "Move.h"

class Output {
    
public:
    static string board(class Board board);
    static string bitboard(U64 bb);
    static string move(U32 move, const class Board &board);
    static string movelist(const class MoveList &list, const class Board &board);
    static string square(U8 square);
    static string piece(U8 piece);
};

#endif	/* OUTPUT_H */

