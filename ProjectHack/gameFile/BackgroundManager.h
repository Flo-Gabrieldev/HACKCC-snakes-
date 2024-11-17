#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

#include <SFML/Graphics.hpp>
#include <stdexcept>

class BackgroundManager {
public:
    // Constructor to initialize the backgrounds
    BackgroundManager(sf::RenderWindow& window) {
        if (!backgroundTexture1.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/map/grass_tileset_16x16_preview_0.png")) {
            throw std::runtime_error("Error loading texture for background 1");
        }
        backgroundSprite1.setTexture(backgroundTexture1);
        scaleSpriteToWindow(backgroundSprite1, window);

        if (!backgroundTexture2.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/map/pixel-art-dungeon-map-featuring-door-window_811279-24918.png")) {
            throw std::runtime_error("Error loading texture for background 2");
        }
        backgroundSprite2.setTexture(backgroundTexture2);
        scaleSpriteToWindow(backgroundSprite2, window);
    }

    // Draw the appropriate background based on the map state
    void draw(sf::RenderWindow& window, bool checkNewMap) {
        if (checkNewMap) {
            window.draw(backgroundSprite1);
        } else {
            window.draw(backgroundSprite2);
        }
    }

    void scaleSpriteToWindow(sf::Sprite& sprite, sf::RenderWindow& window) {
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2u textureSize = sprite.getTexture()->getSize();

        sprite.setScale(
            static_cast<float>(windowSize.x) / textureSize.x,
            static_cast<float>(windowSize.y) / textureSize.y
        );
    }

private:
    sf::Texture backgroundTexture1;
    sf::Sprite backgroundSprite1;

    sf::Texture backgroundTexture2;
    sf::Sprite backgroundSprite2;
};

#endif // BACKGROUNDMANAGER_H

