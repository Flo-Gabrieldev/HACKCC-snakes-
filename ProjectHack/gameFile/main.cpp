#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(1000, 500), "Project-X");

 // Load the texture
    sf::Texture characterTexture;
    if (!characterTexture.loadFromFile("/Users/hashi/Downloads/ProjectHack/character/character/3\ Dude_Monster/Dude_Monster.png"))
    {
        std::cerr << "Error loading texture!" << std::endl;
        return -1;
    }

    // Create a sprite
    sf::Sprite characterSprite;
    characterSprite.setTexture(characterTexture);

    // Position the sprite
    characterSprite.setPosition(400, 300);


    // Main game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
	    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        	window.close();
        }

        // Clear the window
        window.clear();

        // Draw the ball
        window.draw(characterSprite);

        // Display the content of the window
        window.display();
    }

    return 0;
}

