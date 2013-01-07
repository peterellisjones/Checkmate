/* 
 * File:   Parser.h
 * Author: pj
 *
 * Created on January 7, 2013, 11:03 PM
 */

#ifndef PARSER_H
#define	PARSER_H

#include "Types.h"

class Parser {
public:
    static class Board parse_fen(string fen);
    static U8 parse_piece(char piece);
    static U8 side(char c);
    static U8 castling_right(char c);
    static U8 square(char sq[]);
    
private:

};

#endif	/* PARSER_H */

