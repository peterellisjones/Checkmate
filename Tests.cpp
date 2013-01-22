/* 
 * File:   Tests.cpp
 * Author: pj
 * 
 * Created on January 7, 2013, 9:50 PM
 */

#include "Tests.h"

void Tests::run(){
    cout << "Running all tests..." << endl;
    Tests::board();
    Tests::parser();
    Tests::move();
    Tests::move_list();
    Tests::move_generator();
}

void Tests::board(){
    cout << "Testing Board class:" << endl;
    Tests::board_can_construct();
    Tests::board_can_reset();
    Tests::board_can_add_pieces();
    Tests::board_can_remove_pieces();
}

void Tests::board_can_construct(){
    cout << "- Can construct board" << endl;
    Board board = Board();
    assert(board.is_blank());
}

void Tests::board_can_add_pieces(){
    cout << "- Can add piece" << endl;
    Board board = Board();
    board.add_piece(WHITE_PAWN, D5);
    assert(board[D5] == WHITE_PAWN);
    U64 bitboard = 1ULL << D5;
    assert(board.bitboard(WHITE) & bitboard);
    assert(board.bitboard(WHITE_PAWN) & bitboard);
}

void Tests::board_can_remove_pieces(){
    cout << "- Can remove piece" << endl;
    Board board = Board();
    board.add_piece(BLACK_KING, H4);
    assert(board[H4] == BLACK_KING);
    board.remove_piece(H4);
    assert(board[H4] == EMPTY);
    assert(board.is_blank());
    
}

void Tests::board_can_reset(){
    cout << "- Can reset board" << endl;
    Board board = Board();
    board.add_piece(WHITE_PAWN, D5);
    assert(board[D5] == WHITE_PAWN);
    board.reset();
    assert(board.is_blank());
}

void Tests::parser(){
    cout << "Testing Parser class:" << endl;
    Tests::parser_can_parse_fen();    
}

void Tests::parser_can_parse_fen(){
    cout << "- Can parse FEN" << endl;
    string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    U8 expected_board_A[64] = {
        WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK,
        WHITE_PAWN, WHITE_PAWN,   WHITE_PAWN,   WHITE_PAWN,  WHITE_PAWN, WHITE_PAWN,   WHITE_PAWN,   WHITE_PAWN,
        EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,
        EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,
        EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,
        EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,
        BLACK_PAWN, BLACK_PAWN,   BLACK_PAWN,   BLACK_PAWN,  BLACK_PAWN, BLACK_PAWN,   BLACK_PAWN,   BLACK_PAWN,
        BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK};
    
    Board board = Parser::parse_fen(fen);
    
    for(int i = 0; i < 64; i++){
        assert(board[i] == expected_board_A[i]);
    }
    assert(board.half_move_count() == 0);
    assert(board.castling_rights() == FULL_CASTLING_RIGHTS);
    assert(board.ep_square() == NULL_SQUARE);
    assert(board.side_to_move() == WHITE);
    
    fen = "rnbqkbnr/pppppppp/8/8/P7/8/RPPPPPPP/1NBQKBNR b Qkq a3 5 2";
    U8 expected_board_B[64] = {
        EMPTY,      WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK,
        WHITE_ROOK, WHITE_PAWN,   WHITE_PAWN,   WHITE_PAWN,  WHITE_PAWN, WHITE_PAWN,   WHITE_PAWN,   WHITE_PAWN,
        EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,
        WHITE_PAWN, EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,
        EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,
        EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,
        BLACK_PAWN, BLACK_PAWN,   BLACK_PAWN,   BLACK_PAWN,  BLACK_PAWN, BLACK_PAWN,   BLACK_PAWN,   BLACK_PAWN,
        BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK};
    
    board = Parser::parse_fen(fen);
    
    for(int i = 0; i < 64; i++){
        assert(board[i] == expected_board_B[i]);
    }
    assert(board.half_move_count() == 5);
    assert(board.castling_rights() == WHITE_QUEEN_SIDE | BLACK_KING_SIDE | BLACK_QUEEN_SIDE);
    assert(board.ep_square() == A3);
    assert(board.side_to_move() == BLACK);
}

void Tests::move(){
    cout << "Testing Move helper functions" << endl;
    U32 move;
    // test normal move        
    move = build_move(A3, A4);
    assert(move_from(move) == A3);
    assert(move_to(move) == A4);
    assert(!is_capture(move));
    assert(!move_flags(move));
    // test capture
    move = build_capture(A3, B4, BLACK_PAWN);
    assert(move_from(move) == A3);
    assert(move_to(move) == B4);
    assert(move_captured(move) == BLACK_PAWN);
    assert(!move_flags(move));
    // test pawn double push
    move = build_pawn_double_push(A3, A5);
    assert(move_from(move) == A3);
    assert(move_to(move) == A5);
    assert(is_pawn_double_push(move));
    assert(!is_capture(move));
    // test pawn promotion
    move = build_promotion(C7, C8, WHITE_QUEEN);
    assert(move_from(move) == C7);
    assert(move_to(move) == C8);
    assert(is_promotion(move));
    assert(!is_capture(move));
    assert(move_promote_to(move) == WHITE_QUEEN);
    // test pawn promotion capture
    move = build_capture_promotion(C7, D8, BLACK_KNIGHT, WHITE_BISHOP);
    assert(move_from(move) == C7);
    assert(move_to(move) == D8);
    assert(is_promotion(move));
    assert(is_capture(move));
    assert(move_captured(move) == BLACK_KNIGHT);
    assert(move_promote_to(move) == WHITE_BISHOP);
    // test castle
    move = KING_CASTLE;
    assert(is_castle(move));
    // test ep capture
    move = build_ep_capture(C5, D6, BLACK_PAWN);
    assert(move_from(move) == C5);
    assert(move_to(move) == D6);
    assert(is_capture(move));
    assert(is_ep_capture(move));
}

void Tests::move_list(){
    cout << "Testing MoveList class:" << endl;
    Tests::move_list_can_push();
    Tests::move_list_can_reset();
    Tests::move_list_can_pop();
}

void Tests::move_list_can_push(){
    cout << "- Can push" << endl;
    class MoveList list = MoveList();
    assert(list.length() == 0);
    U32 move = build_move(A5, B7);
    assert(list.length() == 0);
    list.push(move);
    assert(list.length() == 1);
    assert(list[0] == move);
}

void Tests::move_list_can_reset(){
    cout << "- Can reset" << endl;
    class MoveList list = MoveList();
    U32 move = build_move(A5, B7);
    list.push(move);
    assert(list.length() == 1);
    assert(list[0] == move);
    list.reset();
    assert(list.length() == 0);
}

void Tests::move_list_can_pop(){
    cout << "- Can pop" << endl;
    class MoveList list = MoveList();
    U32 move = build_move(A5, B7);
    list.push(move);
    U32 popped = list.pop();
    assert(list.length() == 0);
    assert(popped == move);
}

void Tests::move_generator(){
    cout << "Testing MoveGenerator class:" << endl;
    Tests::move_generator_can_generate_pawn_pushes();
    Tests::move_generator_can_generate_pawn_double_pushes();
    Tests::move_generator_can_generate_pawn_attacks();
    Tests::move_generator_can_generate_pawn_promotions();
    Tests::move_generator_can_generate_pawn_capture_promotions();
    Tests::move_generator_can_generate_pawn_en_passant_attacks();
    Tests::move_generator_can_generate_knight_moves();
    Tests::move_generator_can_generate_king_moves();
}

void Tests::move_generator_can_generate_pawn_pushes(){
    cout << "- Can generate pawn pushes" << endl;
    Board board;
    // put 8 pieces in whites starting position
    for(U8 sq = A2; sq <= H2; sq++){
        board.add_piece(WHITE_PAWN, sq);
    }
    assert(board.bitboards[WHITE_PAWN] == 0xFF00ULL);
    assert(board.bitboards[WHITE] == 0xFF00ULL);
    assert(board.bitboards[BLACK] == 0x0ULL);
    MoveList list;
    MoveGenerator::add_pawn_pushes(list, board, WHITE);
    // check 8 pushes generated and 8 double pushes
    assert(list.length() == 16);
    assert(!list.contains_duplicates());
    assert(list.contains_valid_moves(board));
    for(U8 sq = A2; sq <= H2; sq++){
        assert(list.contains(build_move(sq, sq+8)));
    }
    // put 3 pieces in random places
    board = Board();
    board.add_piece(WHITE_PAWN, A3);
    // put one piece on row 8
    board.add_piece(WHITE_PAWN, B8);
    board.add_piece(WHITE_PAWN, C6);
    // put black piece in front of piece at C6
    board.add_piece(BLACK_PAWN, C7);
    // generate moves
    list.reset();
    MoveGenerator::add_pawn_pushes(list, board, WHITE);
    // check only one move: A3A4
    assert(list.length() == 1);
    assert(list.contains_valid_moves(board));
    assert(list.contains(build_move(A3, A4)));
    // repeat above with black pieces
    board = Board();
    board.add_piece(BLACK_PAWN, A6);
    board.add_piece(BLACK_PAWN, B1);
    board.add_piece(BLACK_PAWN, C3);
    board.add_piece(WHITE_PAWN, C2);
    list.reset();
    board.set_side_to_move(BLACK);
    MoveGenerator::add_pawn_pushes(list, board, BLACK);
    assert(list.length() == 1);
    assert(list.contains_valid_moves(board));
    assert(list.contains(build_move(A6, A5)));
}

void Tests::move_generator_can_generate_pawn_double_pushes(){
    cout << "- Can generate pawn double pushes" << endl;
    Board board;
    // this should move forward two
    board.add_piece(WHITE_PAWN, A2);
    // this is blocked by a white piece
    board.add_piece(WHITE_PAWN, B2);
    board.add_piece(WHITE_PAWN, B3);
    // this is block by a black piece, further forward
    board.add_piece(WHITE_PAWN, C2);
    board.add_piece(BLACK_PAWN, C4);
    // this is on the wrong row
    board.add_piece(WHITE_PAWN, D7);
    // this should move forward 
    board.add_piece(WHITE_PAWN, E2);
    // check we can calculate for black too
    board.add_piece(BLACK_PAWN, E7);
    MoveList list;
    MoveGenerator::add_pawn_pushes(list, board, WHITE);
    // last two moves should be double pushes
    assert(list.length() == 10);
    assert(list.contains_valid_moves(board));
    assert(!list.contains_duplicates());
    assert(list.contains(build_pawn_double_push(E2, E4)));
    assert(list.contains(build_pawn_double_push(A2, A4)));
    list.reset();
    board.set_side_to_move(BLACK);
    MoveGenerator::add_pawn_pushes(list, board, BLACK);
    assert(list.length() == 3);
    assert(list.contains_valid_moves(board));
    assert(!list.contains_duplicates());
    assert(list.contains(build_pawn_double_push(E7, E5)));
}

void Tests::move_generator_can_generate_pawn_attacks(){
    cout << "- Can generate pawn attacks" << endl;
    Board board;
    board.add_piece(WHITE_PAWN, A4);
    board.add_piece(WHITE_PAWN, B4);
    board.add_piece(WHITE_PAWN, C4);
    board.add_piece(BLACK_PAWN, B5);
    board.add_piece(BLACK_PAWN, C5);
    MoveList list;
    MoveGenerator::add_pawn_attacks(list, board, WHITE);
    U32 move;
    assert(list.length() == 3);
    assert(list.contains_valid_moves(board));
    assert(!list.contains_duplicates());
    assert(list.contains(build_capture(B4, C5, BLACK_PAWN)));
    assert(list.contains(build_capture(A4, B5, BLACK_PAWN)));
    assert(list.contains(build_capture(C4, B5, BLACK_PAWN)));
    list.reset();
    board.set_side_to_move(BLACK);
    MoveGenerator::add_pawn_attacks(list, board, BLACK);
    assert(list.length() == 3);
    assert(list.contains_valid_moves(board));
    assert(!list.contains_duplicates());
    assert(list.contains(build_capture(C5, B4, WHITE_PAWN)));
    assert(list.contains(build_capture(B5, C4, WHITE_PAWN)));
    assert(list.contains(build_capture(B5, A4, WHITE_PAWN)));
}

void Tests::move_generator_can_generate_pawn_promotions(){
    cout << "- Can generate pawn promotions" << endl;
    Board board;
    board.add_piece(WHITE_PAWN, C7);
    board.add_piece(BLACK_PAWN, C2);
    MoveList list;
    MoveGenerator::add_pawn_pushes(list, board, WHITE);
    assert(list.length() == 4);
    assert(list.contains_valid_moves(board));
    assert(!list.contains_duplicates());
    assert(list.contains(build_promotion(C7, C8, WHITE_QUEEN)));
    assert(list.contains(build_promotion(C7, C8, WHITE_BISHOP)));
    assert(list.contains(build_promotion(C7, C8, WHITE_ROOK)));
    assert(list.contains(build_promotion(C7, C8, WHITE_KNIGHT)));
    list.reset();
    board.set_side_to_move(BLACK);
    MoveGenerator::add_pawn_pushes(list, board, BLACK);
    assert(list.length() == 4);
    assert(list.contains_valid_moves(board));
    assert(!list.contains_duplicates());
    assert(list.contains(build_promotion(C2, C1, BLACK_QUEEN)));
    assert(list.contains(build_promotion(C2, C1, BLACK_BISHOP)));
    assert(list.contains(build_promotion(C2, C1, BLACK_ROOK)));
    assert(list.contains(build_promotion(C2, C1, BLACK_KNIGHT)));
}

void Tests::move_generator_can_generate_pawn_capture_promotions(){
    cout << "- Can generate pawn capture promotions" << endl;
    Board board;
    board.add_piece(WHITE_PAWN, C7);
    board.add_piece(BLACK_ROOK, C8);
    board.add_piece(BLACK_KNIGHT, B8);
    board.add_piece(BLACK_PAWN, C2);
    board.add_piece(WHITE_KNIGHT, C1);
    board.add_piece(WHITE_ROOK, D1);
    MoveList list;
    MoveGenerator::add_pawn_attacks(list, board, WHITE);
    assert(list.length() == 4);
    assert(list.contains_valid_moves(board));
    assert(!list.contains_duplicates());
    assert(list.contains(build_capture_promotion(C7, B8, BLACK_KNIGHT, WHITE_QUEEN)));
    assert(list.contains(build_capture_promotion(C7, B8, BLACK_KNIGHT, WHITE_BISHOP)));
    assert(list.contains(build_capture_promotion(C7, B8, BLACK_KNIGHT, WHITE_KNIGHT)));
    assert(list.contains(build_capture_promotion(C7, B8, BLACK_KNIGHT, WHITE_ROOK)));
    list.reset();
    board.set_side_to_move(BLACK);
    MoveGenerator::add_pawn_attacks(list, board, BLACK);
    assert(list.length() == 4);
    assert(!list.contains_duplicates());
    assert(list.contains(build_capture_promotion(C2, D1, WHITE_ROOK, BLACK_QUEEN)));
    assert(list.contains(build_capture_promotion(C2, D1, WHITE_ROOK, BLACK_KNIGHT)));
    assert(list.contains(build_capture_promotion(C2, D1, WHITE_ROOK, BLACK_ROOK)));
    assert(list.contains(build_capture_promotion(C2, D1, WHITE_ROOK, BLACK_BISHOP)));
}

void Tests::move_generator_can_generate_pawn_en_passant_attacks(){
    cout << "- Can generate pawn en-passant attacks" << endl;
    Board board;
    board.add_piece(BLACK_PAWN, C5);
    board.add_piece(WHITE_PAWN, D5);
    board.set_ep_square(C6);
    MoveList list;
    MoveGenerator::add_pawn_attacks(list, board, WHITE);
    assert(list.length() == 1);
    assert(list.contains_valid_moves(board));
    assert(list.contains(build_ep_capture(D5, C6, BLACK_PAWN)));
    list.reset();
    board.reset();
    board.add_piece(WHITE_PAWN, B4);
    board.add_piece(BLACK_PAWN, A4);
    board.add_piece(WHITE_PAWN, H3);
    board.set_ep_square(B3);
    board.set_side_to_move(BLACK);
    MoveGenerator::add_pawn_attacks(list, board, BLACK);
    assert(list.length() == 1);
    assert(list.contains(build_ep_capture(A4, B3, WHITE_PAWN)));
}


void Tests::move_generator_can_generate_knight_moves(){
    cout << "- Can generate knight moves" << endl;
    Board board;
    board.add_piece(WHITE_KNIGHT, D4);
    MoveList list;
    // check normal moves
    MoveGenerator::add_knight_moves(list, board, WHITE);
    assert(list.length() == 8); 
    assert(list.contains_valid_moves(board)); 
    assert(!list.contains_duplicates());  
    assert(list.contains(build_move(D4, B5)));
    assert(list.contains(build_move(D4, C6)));
    assert(list.contains(build_move(D4, E6)));
    assert(list.contains(build_move(D4, F5)));
    assert(list.contains(build_move(D4, B3)));
    assert(list.contains(build_move(D4, C2)));
    assert(list.contains(build_move(D4, E2)));
    assert(list.contains(build_move(D4, F3)));
    list.reset();
    // check captures
    board.add_piece(BLACK_KNIGHT, B3);
    board.set_side_to_move(BLACK);
    MoveGenerator::add_knight_moves(list, board, BLACK);
    assert(list.contains(build_capture(B3, D4, WHITE_KNIGHT)));
    list.reset();
    // check corners only have two moves
    board.reset();
    board.add_piece(WHITE_KNIGHT, A1);
    board.set_side_to_move(WHITE);
    MoveGenerator::add_knight_moves(list, board, WHITE);
    assert(list.contains(build_move(A1, B3)));
    assert(list.contains(build_move(A1, C2)));
    assert(list.length() == 2);  
    assert(!list.contains_duplicates()); 
    board.reset();
    list.reset();
    board.add_piece(WHITE_KNIGHT, H8);
    MoveGenerator::add_knight_moves(list, board, WHITE);
    assert(list.contains(build_move(H8, F7)));
    assert(list.contains(build_move(H8, G6)));
    assert(list.length() == 2);     
}

void Tests::move_generator_can_generate_king_moves(){
    cout << "- Can generate king moves" << endl;
    Board board;
    board.add_piece(WHITE_KING, D4);
    MoveList list;
    // check normal moves
    MoveGenerator::add_king_moves(list, board, WHITE);
    assert(list.length() == 8);  
    assert(list.contains_valid_moves(board));
    assert(!list.contains_duplicates());  
    assert(list.contains(build_move(D4, D5)));
    assert(list.contains(build_move(D4, D3)));
    assert(list.contains(build_move(D4, E4)));
    assert(list.contains(build_move(D4, C4)));
    assert(list.contains(build_move(D4, E5)));
    assert(list.contains(build_move(D4, C5)));
    assert(list.contains(build_move(D4, E3)));
    assert(list.contains(build_move(D4, C3)));
    list.reset();
    // check only three moves at corners, and captures
    board.reset();
    board.add_piece(BLACK_KING, A1);
    board.add_piece(WHITE_QUEEN, B2);
    board.set_side_to_move(BLACK);
    MoveGenerator::add_king_moves(list, board, BLACK);
    assert(list.contains(build_move(A1, A2)));
    assert(list.contains(build_move(A1, B1)));
    assert(list.contains(build_capture(A1, B2, WHITE_QUEEN)));
    assert(list.length() == 3); 
    assert(list.contains_valid_moves(board));
    assert(!list.contains_duplicates());  
    board.reset();
    board.set_side_to_move(BLACK);
    list.reset();
    board.add_piece(BLACK_KING, H8);
    board.add_piece(WHITE_QUEEN, G7);
    MoveGenerator::add_king_moves(list, board, BLACK);
    assert(list.contains(build_move(H8, G8)));
    assert(list.contains(build_move(H8, H7)));
    assert(list.contains(build_capture(H8, G7, WHITE_QUEEN)));
    assert(list.length() == 3); 
    assert(!list.contains_duplicates());
    assert(list.contains_valid_moves(board));
}