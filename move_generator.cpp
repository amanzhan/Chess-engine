
#include "game.h"
#include "helper_functions.h"

U64 MoveGenerator::pseudo_legal_pawn_move(bool white, BitBoard &bitBoard, U64 square) {
    return 0;
}
U64 MoveGenerator::pseudo_legal_bishop_move(bool white, BitBoard &bitBoard, U64 square) {
    return 0;
}   
U64 MoveGenerator::pseudo_legal_knight_move(bool white, BitBoard &bitBoard, U64 square) {
    return 0;
}
U64 MoveGenerator::pseudo_legal_rook_move(bool white, BitBoard &bitBoard, U64 square) {
    return 0;
}
U64 MoveGenerator::pseudo_legal_queen_move(bool white, BitBoard &bitBoard, U64 square) {
    return 0;
}
U64 MoveGenerator::pseudo_legal_king_move(bool white, BitBoard &bitBoard, U64 square) {
    return 0;
}

U64 MoveGenerator::generate_pseudo_legal_moves(BitBoard &bitBoard, unsigned int piece, U64 square) {
    switch (piece)
    {
    case W_PAWN:
        pseudo_legal_pawn_move(true, bitBoard, square);
        break;
    case W_BISHOP:
        pseudo_legal_bishop_move(true, bitBoard, square);
        break;
    case W_KNIGHT:
        pseudo_legal_knight_move(true, bitBoard, square);
        break;
    case W_ROOK:
        pseudo_legal_rook_move(true, bitBoard, square);
        break; 
    case W_QUEEN:
        pseudo_legal_queen_move(true, bitBoard, square);
        break;
    case W_KING:
        pseudo_legal_king_move(true, bitBoard, square);
        break;
    case B_PAWN:
        pseudo_legal_pawn_move(false, bitBoard, square);
        break;
    case B_BISHOP:
        pseudo_legal_bishop_move(false, bitBoard, square);
        break;
    case B_KNIGHT:
        pseudo_legal_knight_move(false, bitBoard, square);
        break;
    case B_ROOK:
        pseudo_legal_rook_move(false, bitBoard, square);
        break; 
    case B_QUEEN:
        pseudo_legal_queen_move(false, bitBoard, square);
        break;
    case B_KING:
        pseudo_legal_king_move(false, bitBoard, square);
        break;
    default:
        break;
    }
    return 1; 
}
