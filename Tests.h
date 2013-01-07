/* 
 * File:   Tests.h
 * Author: pj
 *
 * Created on January 7, 2013, 9:50 PM
 */

#ifndef TESTS_H
#define	TESTS_H

#include "Types.h"

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
};

#endif	/* TESTS_H */

