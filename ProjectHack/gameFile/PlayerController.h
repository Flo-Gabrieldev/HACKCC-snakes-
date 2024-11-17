#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <SFML/Graphics.hpp>
#include "Animation.h" // Assuming Animation is your custom animation class

class PlayerController {
private:
    sf::Vector2f movement;          // Movement vector
    float speed;                    // Player movement speed
    bool isMoving;                  // Is the player moving?
    bool click;                     // Is the player attacking?
    Animation& playerAnimation;     // Reference to the player's animation
    sf::Texture* walkTexture;       // Texture for walking
    sf::Texture* idleTexture;       // Texture for idle
    sf::Texture* attackTexture;     // Texture for attack

public:
    // Constructor
    PlayerController(Animation& animation, float speed, sf::Texture* walk, sf::Texture* idle, sf::Texture* attack)
        : playerAnimation(animation), speed(speed), walkTexture(walk), idleTexture(idle), attackTexture(attack), 
          movement(0.f, 0.f), isMoving(false), click(false) {}

    // Update player logic
    void update(float deltaTime) {
        // Reset movement
        movement = sf::Vector2f(0.f, 0.f);
        isMoving = false;

        // Handle keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movement.x -= speed * deltaTime;
            isMoving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            movement.x += speed * deltaTime;
            isMoving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            movement.y -= speed * deltaTime;
            isMoving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            movement.y += speed * deltaTime;
            isMoving = true;
        }

        // Handle attack
        click = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

        // Update animation based on movement or action
        if (click) {
            playerAnimation.changeTexture(*attackTexture, 4, sf::Vector2i(43, 32), 0.4f);
        } else if (isMoving) {
            playerAnimation.changeTexture(*walkTexture);
        } else {
            playerAnimation.changeTexture(*idleTexture, 4);
        }
    }

    // Get current movement vector
    sf::Vector2f getMovement() const {
        return movement;
    }

    // Check if player is attacking
    bool isAttacking() const {
        return click;
    }
};

#endif // PLAYERCONTROLLER_H

