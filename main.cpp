#include "graphics.h"
#include "moveHandler.h"

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
