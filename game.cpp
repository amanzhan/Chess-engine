#include "game.h"

void Game::handle_click(U64 square) {
    // Highlight the clicked piece
    unsigned int pieceAtSquare = get_piece_at_square(square);
    if ((playAsWhite && is_white(pieceAtSquare)) || (!playAsWhite && is_black(pieceAtSquare))) {
        bitBoard.select_piece(square); 
        return; 
    }
    
    if (bitBoard.piece_is_selected()) {
        move_if_legal(bitBoard.selected_position(), square); 
        bitBoard.deselect_piece(); 
    }
}

int Game::get_piece_at_square (U64 square) {
    U64 position = get_bit_at_square(square); 
    for (unsigned int piece = 0; piece < 12; piece++) {
        if (bitBoard.At(piece) & position) {
            return piece; 
        }
    }
    return -1; 
}

void Game::move_if_legal (U64 from, U64 to) {
    unsigned int movingPiece = get_piece_at_square(from); 
    unsigned int capturedPiece = get_piece_at_square(to);
    bitBoard.move_piece(movingPiece, from, to); 
    if (is_piece(capturedPiece)) {
        bitBoard.capture_piece(capturedPiece, to);
    }
}

void BitBoard::capture_piece(unsigned int piece, U64 square) {
    PiecePositions[piece] -= get_bit_at_square(square);
}
void BitBoard::move_piece(unsigned int piece, U64 from, U64 to) {
    PiecePositions[piece] -= get_bit_at_square(from);
    PiecePositions[piece] += get_bit_at_square(to); 
}