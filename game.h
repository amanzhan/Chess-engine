#ifndef GAME_H
#define GAME_H

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
    bool pseudo_legal(U64 from, U64 to, unsigned int piece); 

    private:
    U64 PiecePositions[12];
    bool pieceIsSelected; 
    unsigned int selectedPosition; 

};

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

class MoveGenerator {
    public: 
    U64 generate_pseudo_legal_moves(BitBoard &bitBoard, unsigned int piece, U64 square); 

    private: 
    U64 pseudo_legal_pawn_move(bool white, BitBoard &bitBoard, U64 square);
    U64 pseudo_legal_bishop_move(bool white, BitBoard &bitBoard, U64 square);
    U64 pseudo_legal_knight_move(bool white, BitBoard &bitBoard, U64 square);
    U64 pseudo_legal_rook_move(bool white, BitBoard &bitBoard, U64 square);
    U64 pseudo_legal_queen_move(bool white, BitBoard &bitBoard, U64 square);
    U64 pseudo_legal_king_move(bool white, BitBoard &bitBoard, U64 square);
};
#endif