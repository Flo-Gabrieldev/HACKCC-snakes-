#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

class FontManager {
public:
    // Constructor to load a font file
    FontManager(const std::string& fontFilePath) {
        if (!font.loadFromFile(fontFilePath)) {
            throw std::runtime_error("Failed to load font from file: " + fontFilePath);
        }
    }

    // Function to create text with specific settings
    sf::Text createText(const std::string& textString, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position,
int score = 0) {
        sf::Text text;
        text.setFont(font);
	if(score == 0) text.setString(textString);
	else text.setString("Score: " + std::to_string(score));
        text.setCharacterSize(characterSize);
        text.setFillColor(color);
        text.setPosition(position);
        return text;
    }

private:
    sf::Font font;
};

#endif // FONTMANAGER_H

