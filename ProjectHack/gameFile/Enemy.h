#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Animation.h"

class Enemy {
public:
    // Constructor accepts Animation object, position, and optional speed
    Enemy(Animation& animation, sf::Vector2f position, float speed = 100.f)
        : animation(animation), position(position), speed(speed) {
        animation.setPosition(position);
    }

    // Update the enemy's animation and logic
    void update(float deltaTime) {
        // Move the enemy based on the current direction and speed
        position += direction * speed * deltaTime;
        animation.setPosition(position); // Update the animation's position
        animation.update(deltaTime);     // Update the animation
    }

    // Get the sprite for rendering
    sf::Sprite& getSprite() {
        return animation.getSprite();
    }

    // Randomly choose a new direction (up, down, left, right)
    void randomDirection() {
        int dir = rand() % 4; // Generate a random number between 0 and 3
        switch (dir) {
        case 0: direction = {0.f, -1.f}; break; // Move up
        case 1: direction = {0.f, 1.f}; break;  // Move down
        case 2: direction = {-1.f, 0.f}; break; // Move left
        case 3: direction = {1.f, 0.f}; break;  // Move right
        }
    }

private:
    Animation animation;       // Handles the sprite's animation
    sf::Vector2f position;     // Current position of the enemy
    sf::Vector2f direction;    // Direction of movement
    float speed;               // Speed of the enemy
};

#endif

