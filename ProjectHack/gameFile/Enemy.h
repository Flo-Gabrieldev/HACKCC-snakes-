#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Enemy {
public:
    // Constructor accepts Animation object and initial position
    Enemy(Animation& animation, sf::Vector2f position, float speed = 100.f)
        : animation(animation), speed(speed), direction(0.f, 0.f) {
        animation.setPosition(position);
    }

    // Update method to update animation and movement
    void update(float deltaTime) {
        // Update the enemy's animation
        animation.update(deltaTime);

        // Move the enemy based on its direction and speed
        sf::Vector2f movement = direction * speed * deltaTime;
        animation.setPosition(animation.getSprite().getPosition() + movement);
    }

    // Function to get the sprite for rendering
    sf::Sprite& getSprite() {
        return animation.getSprite();
    }

    // Function to randomize movement direction
    void randomDirection() {
        // Randomly choose a direction (up, down, left, right)
        int dir = rand() % 4;
        switch (dir) {
        case 0: direction = {0.f, -1.f}; break; // Move up
        case 1: direction = {0.f, 1.f}; break;  // Move down
        case 2: direction = {-1.f, 0.f}; break; // Move left
        case 3: direction = {1.f, 0.f}; break;  // Move right
        }
    }

private:
    Animation animation;  // Use the Animation class to handle animation
    sf::Vector2f direction;  // Direction in which the enemy is moving
    float speed;            // Speed at which the enemy moves
};

#endif

