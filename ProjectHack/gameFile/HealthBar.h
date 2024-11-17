#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include <SFML/Graphics.hpp>

class HealthBar {
private:
    sf::RectangleShape backgroundBar; // Full bar (background)
    sf::RectangleShape foregroundBar; // Current health (foreground)
    int maxHealth;
    int currentHealth;

public:
    // Constructor
    HealthBar(int maxHealth, float width, float height, sf::Vector2f position)
        : maxHealth(maxHealth), currentHealth(maxHealth) {
        // Configure the background bar
        backgroundBar.setSize(sf::Vector2f(width, height));
        backgroundBar.setFillColor(sf::Color(100, 100, 100)); // Grey
        backgroundBar.setPosition(position);

        // Configure the foreground bar
        foregroundBar.setSize(sf::Vector2f(width, height));
        foregroundBar.setFillColor(sf::Color(255, 0, 0)); // Red
        foregroundBar.setPosition(position);
    }

    // Set current health
    void setHealth(int health) {
        currentHealth = std::max(0, std::min(health, maxHealth)); // Clamp value between 0 and maxHealth
        float healthRatio = static_cast<float>(currentHealth) / maxHealth;
        foregroundBar.setSize(sf::Vector2f(backgroundBar.getSize().x * healthRatio, backgroundBar.getSize().y));
    }

    // Get current health
    int getHealth() const {
        return currentHealth;
    }

    // Draw the health bar
    void draw(sf::RenderWindow& window) const {
        window.draw(backgroundBar);
        window.draw(foregroundBar);
    }

    // Optional: Update bar position (e.g., to follow a character)
    void setPosition(sf::Vector2f position) {
        backgroundBar.setPosition(position);
        foregroundBar.setPosition(position);
    }

    // Optional: Change color dynamically based on health
    void updateColor() {
        if (currentHealth > maxHealth * 0.5)
            foregroundBar.setFillColor(sf::Color::Green); // Healthy
        else if (currentHealth > maxHealth * 0.2)
            foregroundBar.setFillColor(sf::Color::Yellow); // Warning
        else
            foregroundBar.setFillColor(sf::Color::Red); // Critical
    }
};
#endif
