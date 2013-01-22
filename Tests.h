/* 
 * File:   Tests.h
 * Author: pj
 *
 * Created on January 7, 2013, 9:50 PM
 */

#ifndef TESTS_H
#define	TESTS_H

#include "Common.h"
#include "Board.h"
#include "MoveGenerator.h"
#include "MoveList.h"
#include "Parser.h"

class Tests {
    
public:
    static void run();
   
private:
    static void board();
    
    static void board_can_add_pieces();
    static void board_can_remove_pieces();
    static void board_can_construct();
    static void board_can_reset(); 
    
    static void parser();
    static void parser_can_parse_fen();
    
    static void move();
    
    static void move_list();
    static void move_list_can_push();
    static void move_list_can_reset();
    static void move_list_can_pop();
    
    static void move_generator();
    
    static void move_generator_can_generate_pawn_pushes();
    static void move_generator_can_generate_pawn_double_pushes();
    static void move_generator_can_generate_pawn_attacks();
    static void move_generator_can_generate_pawn_promotions();
    static void move_generator_can_generate_pawn_capture_promotions();
    static void move_generator_can_generate_pawn_en_passant_attacks();
    
    static void move_generator_can_generate_knight_moves();
    static void move_generator_can_generate_king_moves();
};

#endif	/* TESTS_H */

