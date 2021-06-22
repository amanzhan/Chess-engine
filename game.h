#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "helper_functions.h"
#include <math.h>
#include <iostream>

using namespace std;



class BitBoard {
    public: 
    BitBoard() : pieceIsSelected(false) {
        PiecePositions[W_PAWN] = W_PAWN_STARTING_POS;
        PiecePositions[W_BISHOP] = W_BISHOP_STARTING_POS;
        PiecePositions[W_KNIGHT] = W_KNIGHT_STARTING_POS;
        PiecePositions[W_ROOK] = W_ROOK_STARTING_POS;
        PiecePositions[W_QUEEN] = W_QUEEN_STARTING_POS;
        PiecePositions[W_KING] = W_KING_STARTING_POS;

        PiecePositions[B_PAWN] = B_PAWN_STARTING_POS;
        PiecePositions[B_BISHOP] = B_BISHOP_STARTING_POS;
        PiecePositions[B_KNIGHT] = B_KNIGHT_STARTING_POS;
        PiecePositions[B_ROOK] = B_ROOK_STARTING_POS;
        PiecePositions[B_QUEEN] = B_QUEEN_STARTING_POS;
        PiecePositions[B_KING] = B_KING_STARTING_POS;
    }
    bool piece_is_selected() const {
        return pieceIsSelected;
    }

    void select_piece(U64 square) {
        pieceIsSelected = true; 
        selectedPosition = square; 
    }

    void deselect_piece() {
        pieceIsSelected = false; 
    }
    
    unsigned int selected_position() const {
        return selectedPosition;
    }

    U64 At(unsigned int ind) const {
        return PiecePositions[ind];
    }

    void capture_piece(unsigned int piece, U64 square); 
    void move_piece(unsigned int piece, U64 from, U64 to);

    private:
    U64 PiecePositions[12];
    bool pieceIsSelected; 
    unsigned int selectedPosition; 
};

void BitBoard::capture_piece(unsigned int piece, U64 square) {
    PiecePositions[piece] -= (U64) 1 << square;
}
void BitBoard::move_piece(unsigned int piece, U64 from, U64 to) {
    PiecePositions[piece] -= (U64) 1 << from;
    PiecePositions[piece] += (U64) 1 << to; 
}

class Game {
    public: 
    Game(bool play_as_white_in) : playAsWhite(play_as_white_in) {}
    const BitBoard get_bitboard() const{
        return bitBoard;
    }
    void handle_click(U64 square);

    private:
    bool playAsWhite; 
    BitBoard bitBoard; 
    void move_if_legal(U64 from, U64 to);
    int get_piece_at_square (U64 square);
};

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
    U64 position = (U64)1 << square; 
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
#endif