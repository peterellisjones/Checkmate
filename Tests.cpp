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