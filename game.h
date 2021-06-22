#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "helper_functions.h"
#include <math.h>
#include <iostream>

using namespace std;

const unsigned int W_PAWN = 0; 
const unsigned int W_BISHOP = 1; 
const unsigned int W_KNIGHT = 2; 
const unsigned int W_ROOK = 3; 
const unsigned int W_QUEEN = 4;
const unsigned int W_KING = 5;
const unsigned int B_PAWN = 6;
const unsigned int B_BISHOP = 7; 
const unsigned int B_KNIGHT = 8;
const unsigned int B_ROOK = 9;
const unsigned int B_QUEEN = 10;
const unsigned int B_KING = 11;

const unsigned long long W_PAWN_STARTING_POS = 0b0000000000000000000000000000000000000000000000001111111100000000;
const unsigned long long W_BISHOP_STARTING_POS = 0b0000000000000000000000000000000000000000000000000000000000100100;
const unsigned long long W_KNIGHT_STARTING_POS = 0b0000000000000000000000000000000000000000000000000000000001000010;
const unsigned long long W_ROOK_STARTING_POS = 0b0000000000000000000000000000000000000000000000000000000010000001;
const unsigned long long W_QUEEN_STARTING_POS = 0b0000000000000000000000000000000000000000000000000000000000001000;
const unsigned long long W_KING_STARTING_POS = 0b0000000000000000000000000000000000000000000000000000000000010000;

const unsigned long long B_PAWN_STARTING_POS = 0b0000000011111111000000000000000000000000000000000000000000000000;
const unsigned long long B_BISHOP_STARTING_POS = 0b0010010000000000000000000000000000000000000000000000000000000000;
const unsigned long long B_KNIGHT_STARTING_POS = 0b0100001000000000000000000000000000000000000000000000000000000000;
const unsigned long long B_ROOK_STARTING_POS = 0b1000000100000000000000000000000000000000000000000000000000000000;
const unsigned long long B_QUEEN_STARTING_POS = 0b0000100000000000000000000000000000000000000000000000000000000000;
const unsigned long long B_KING_STARTING_POS = 0b0001000000000000000000000000000000000000000000000000000000000000;

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

    void select_piece(unsigned int square) {
        pieceIsSelected = true; 
        selectedPosition = square; 
    }

    void deselect_piece() {
        pieceIsSelected = false; 
    }
    
    unsigned int selected_position() const {
        return selectedPosition;
    }

    unsigned long long At(unsigned int ind) const {
        return PiecePositions[ind];
    }

    void capture_piece(unsigned int piece, unsigned int square); 
    void move_piece(unsigned int piece, unsigned int from, unsigned int to);

    private:
    unsigned long long PiecePositions[12];
    bool pieceIsSelected; 
    unsigned int selectedPosition; 
};

void BitBoard::capture_piece(unsigned int piece, unsigned int square) {
    PiecePositions[piece] -= pow(2, square);
}
void BitBoard::move_piece(unsigned int piece, unsigned int from, unsigned int to) {
    PiecePositions[piece] -= pow(2, from);
    PiecePositions[piece] += pow(2, to);
}

class Game {
    public: 
    Game(bool play_as_white_in) : playAsWhite(play_as_white_in) {}
    const BitBoard get_bitboard() const{
        return bitBoard;
    }
    void handle_click(unsigned int square);

    private:
    bool playAsWhite; 
    BitBoard bitBoard; 
    void move_if_legal(unsigned int from, unsigned int to);
    int get_piece_at_square (unsigned int square);
};

void Game::handle_click(unsigned int square) {
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

int Game::get_piece_at_square (unsigned int square) {
    unsigned long long position = pow(2, square); 
    for (unsigned int piece = 0; piece < 12; piece++) {
        if (bitBoard.At(piece) & position) {
            return piece; 
        }
    }
    return -1; 
}

void Game::move_if_legal (unsigned int from, unsigned int to) {
    unsigned int movingPiece = get_piece_at_square(from); 
    unsigned int capturedPiece = get_piece_at_square(to);
    bitBoard.move_piece(movingPiece, from, to); 
    if (is_piece(capturedPiece)) {
        bitBoard.capture_piece(capturedPiece, to);
    }
}
#endif