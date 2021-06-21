#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std; 

const int HEIGHT = 800; 
const int WIDTH  = 800; 

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
const unsigned int CHESSBOARD = 12; 


// A1 is LSB
// H8 is MSB
// 56 57 58 59 60 61 62 63 
// .......................
// 0  1  2  3  4  5  6  7
class BitBoard {
    public: 
    BitBoard() {
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

    unsigned long long At(unsigned int ind) {
        return PiecePositions[ind];
    }

    private:
    unsigned long long PiecePositions[12];
};

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
    Graphics() {
        load_textures(); 
    }

    vector<Coordinate> convert_bits_to_coordinate(unsigned long long bits, unsigned int piece);
    void render_pieces (vector<Coordinate> &coords, unsigned int piece);
    void load_board(BitBoard &bitBoard); 
    void load_textures(); 
    vector<sf::Sprite> get_sprites() {
        return sprites; 
    }
    

    private: 
    bool white; 
    sf::Texture textures[13];
    vector<sf::Sprite> sprites; 
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

vector<Coordinate> Graphics::convert_bits_to_coordinate (unsigned long long bits, unsigned int piece) {
    vector<Coordinate> retval;
    for (unsigned int i = 0; i < 64; i++) {
        if (!bits) {
            break; 
        }
        if (bits & 1) { // i'th LSB is set to 1
            retval.push_back(Coordinate(i / 8, i % 8));
        }

        bits = bits >> 1; 
    }
    return retval;
}

void Graphics::render_pieces (vector<Coordinate> &coords, unsigned int piece) {
    for (auto coord : coords) {
        sprites.push_back(sf::Sprite());
        sprites.back().setTexture(textures[piece]);
        sprites.back().setPosition(100 * coord.get_file() + 10, 100 * (7 -coord.get_rank()) + 10);
        
    }
}

void Graphics::load_board(BitBoard &bitBoard) {
    sprites.clear(); 
    sprites.push_back(sf::Sprite(textures[CHESSBOARD]));
    for (unsigned int piece = 0; piece < 12; piece++) {
        vector<Coordinate> coords = convert_bits_to_coordinate(bitBoard.At(piece), piece);
        render_pieces(coords, piece);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Chess The Game Of Kings!");
    Graphics graphic; 
    BitBoard bitboard; 
    while (window.isOpen())
    {
        graphic.load_board(bitboard);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for (auto sprite : graphic.get_sprites()) {
            window.draw(sprite);
        }
        window.display(); 
    }
}