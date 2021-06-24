#include "game.h"
#include "graphics.h"


using namespace std;

int main() {
    string response; 
    cout << "Would you like to play as W or B?" << endl; 
    bool playAsWhite = false;
    while(true) {
        cin >> response; 
        if (response == "W") {
            playAsWhite = true;
            break; 
        } else if (response == "B") {
            break; 
        } else {
            cout << endl << "Please enter W or B" << endl;
        }
    }
        
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Chess Engine");
    Graphics graphic(playAsWhite); 
    Game game(playAsWhite); 
    BitBoard bitboard; 
    graphic.load_board(game.get_bitboard());
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                unsigned int square = graphic.convert_pixel_to_square(event.mouseButton.x, event.mouseButton.y);
                game.handle_click(square);
                graphic.load_board(game.get_bitboard());
            }
            window.clear();
        }
        for (auto sprite : graphic.get_sprites()) {
            window.draw(sprite);
        }
        window.display(); 
    }
}
