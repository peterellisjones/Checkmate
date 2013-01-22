/* 
 * File:   MoveList.h
 * Author: pj
 *
 * Created on January 16, 2013, 2:54 PM
 */

#ifndef MOVELIST_H
#define	MOVELIST_H

#include "Common.h"
#include "Board.h"

const int MAX_MOVELIST_LENGTH = 256;

class MoveList {
private:
    int size;
    U32 data[MAX_MOVELIST_LENGTH];
public:
    MoveList() { size = 0; }
    void inline push(U32 move) { 
      #ifdef DEBUG
        assert(size < MAX_MOVELIST_LENGTH);
      #endif
        data[size++] = move; 
   }
    U32  inline pop() { 
      #ifdef DEBUG
        assert(size > 0);
      #endif
        return data[--size]; 
    }
    void inline reset() { size = 0; }
    U32  inline operator[](const int idx) const { return data[idx]; };
    int  inline length() const { return size; }
    bool contains(U32 move);
    bool contains_duplicates();
    bool contains_valid_moves(const class Board &board);
};

#endif	/* MOVELIST_H */

