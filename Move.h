/* 
 * File:   Moves.h
 * Author: pj
 *
 * Created on January 16, 2013, 3:42 PM
 */

#ifndef MOVES_H
#define	MOVES_H

#include "Common.h"

const U32 KING_CASTLE = 64 << 16;
const U32 QUEEN_CASTLE = 128 << 16;

// FLAGS (note all in fourth byte)
static const U32 NO_FLAGS = 0 << 16;
// Promotions
// to create promotion just put piece to promote to in flags
// fourth bit denotes double pawn push
static const U32 PAWN_DOUBLE_PUSH = 16 << 16;
// fifth bit denote EP capture
static const U32 EP_CAPTURE = 32 << 16;
// sixth and seventh bit denotes castle
static const U32 CASTLE_MASK = KING_CASTLE | QUEEN_CASTLE;

U32 inline build_move(U8 from, U8 to) { return from | (to << 8); }
U32 inline build_capture(U8 from, U8 to, U8 capture){ return from | (to << 8) | (capture << 24); }
U32 inline build_ep_capture(U8 from, U8 to, U8 capture){ return from | (to << 8) | (capture << 24) | EP_CAPTURE; }
U32 inline build_promotion(U8 from, U8 to, U8 promote_to){ return from | (to << 8) | (promote_to << 16); }
U32 inline build_capture_promotion(U8 from, U8 to, U8 capture, U8 promote_to){ return from | (to << 8) | (capture << 24) | (promote_to << 16); }
U32 inline build_pawn_double_push(U8 from, U8 to){ return from | (to << 8) | PAWN_DOUBLE_PUSH; }

bool inline is_capture(U32 move){ return move & (0xFF << 24); }
bool inline is_promotion(U32 move){ return move & (15 << 16); } // mask all pieces 
bool inline is_ep_capture(U32 move){ return move & EP_CAPTURE; }
bool inline is_castle(U32 move){ return move & CASTLE_MASK; }
bool inline is_pawn_double_push(U32 move){ return move & PAWN_DOUBLE_PUSH; }

U32 inline move_from(U32 move){ return (move & 0xFFULL); }
U32 inline move_to(U32 move){ return (move & 0xFF00) >> 8; }
U32 inline move_captured(U32 move){ return (move & 0xFF000000) >> 24; }
U32 inline move_flags(U32 move){ return move & 0xFF0000; }
U32 inline move_promote_to(U32 move){ return (move & 0xFF0000) >> 16; }


#endif	/* MOVES_H */

