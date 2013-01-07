/* 
 * File:   Output.cpp
 * Author: pj
 * 
 * Created on January 7, 2013, 11:38 PM
 */

#include "Output.h"

void Output::board(Board board){
    cout << "  12345678  " << endl;
    for(int row = 7; row >= 0; row--){
        cout << row + 1 << '|';
        for(int col = 0; col < 7; col++){
            int square = (row << 3) | col;
            cout << PIECE_CHARS[board[square]];
        }
        cout << '|' << row + 1 << endl;;
    }
    cout << "  12345678  " << endl;
}

