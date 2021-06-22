#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game.h"
#include "helper_functions.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std; 

const int HEIGHT = 800; 
const int WIDTH  = 800; 

const unsigned int CHESSBOARD = 12; 


// A1 is LSB
// H8 is MSB
// 56 57 58 59 60 61 62 63 
// .......................
// 0  1  2  3  4  5  6  7


class Coordinate {
    public:
    Coordinate(unsigned int rank_in, unsigned int file_in): rank(rank_in), file(file_in) {}

    unsigned int get_rank() {
        return rank;
    }
    unsigned int get_file() {
        return file; 
    }
    
    private:
    unsigned int rank; 
    unsigned int file; 
};

class Graphics {
    public: 
    Graphics(bool playAsWhite_in): playAsWhite(playAsWhite_in) {
        load_textures(); 
    }

    vector<Coordinate> convert_bits_to_coordinate(U64 bits, unsigned int piece);
    void load_board(const BitBoard &bitBoard); 

    vector<sf::Sprite> get_sprites() {
        return sprites; 
    }

    unsigned int convert_pixel_to_square(int x, int y) {
        unsigned int rank = 7 - y / 100; 
        unsigned int file = x / 100; 
        if (playAsWhite) {
            return rank * 8 + file; 
        } else {
            return (7 - rank) * 8 + (7-file);
        }
    }
    
    private: 
    bool playAsWhite; 
    sf::Texture textures[13];
    vector<sf::Sprite> sprites; 
    void load_textures();
    void render_pieces (vector<Coordinate> &coords, unsigned int piece, const BitBoard &bitBoard); 
};

void Graphics::load_textures() {
    textures[CHESSBOARD].loadFromFile("Images/ChessBoard.png"); 
    textures[W_PAWN].loadFromFile("Images/WhitePawn.png"); 
    textures[W_BISHOP].loadFromFile("Images/WhiteBishop.png"); 
    textures[W_KNIGHT].loadFromFile("Images/WhiteKnight.png"); 
    textures[W_ROOK].loadFromFile("Images/WhiteRook.png"); 
    textures[W_QUEEN].loadFromFile("Images/WhiteQueen.png"); 
    textures[W_KING].loadFromFile("Images/WhiteKing.png"); 
    textures[B_PAWN].loadFromFile("Images/BlackPawn.png"); 
    textures[B_BISHOP].loadFromFile("Images/BlackBishop.png"); 
    textures[B_KNIGHT].loadFromFile("Images/BlackKnight.png"); 
    textures[B_ROOK].loadFromFile("Images/BlackRook.png"); 
    textures[B_QUEEN].loadFromFile("Images/BlackQueen.png"); 
    textures[B_KING].loadFromFile("Images/BlackKing.png"); 
}

vector<Coordinate> Graphics::convert_bits_to_coordinate (U64 bits, unsigned int piece) {
    vector<Coordinate> retval;
    for (unsigned int i = 0; i < 64; i++) {
        if (!bits) {
            break; 
        }
        if (bits & 1) { // i'th LSB is set to 1
            retval.push_back(Coordinate(i / 8, i % 8));
        }

        bits = bits >> (U64) 1; 
    }
    return retval;
}

void Graphics::render_pieces (vector<Coordinate> &coords, unsigned int piece, const BitBoard &bitBoard) {
    for (auto coord : coords) {
        sf::Sprite sprite(textures[piece]);
        if (is_black(piece)) {
            sprite.setColor(sf::Color(88,88,88));
        }
        if (playAsWhite) {
            sprite.setPosition(100 * coord.get_file() + 10, 100 * (7 - coord.get_rank()) + 10);
        } else {
            sprite.setPosition(100 * (7 - coord.get_file()) + 10, 100 * coord.get_rank() + 10);
        }
        if (8 * coord.get_rank() + coord.get_file() == bitBoard.selected_position()) {
            sprite.setColor(sf::Color::Red);
        }
        sprites.push_back(sprite);
    }
}

void Graphics::load_board(const BitBoard &bitBoard) {
    sprites.clear(); 
    sprites.push_back(sf::Sprite(textures[CHESSBOARD]));
    for (unsigned int piece = 0; piece < 12; piece++) {
        vector<Coordinate> coords = convert_bits_to_coordinate(bitBoard.At(piece), piece);
        render_pieces(coords, piece, bitBoard);
    }
}

#endif