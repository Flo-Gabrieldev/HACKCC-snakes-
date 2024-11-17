#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"  // Assuming you have an Animation class

class Player {
public:

Player::Player(const sf::Texture& idleTex, const sf::Texture& walkTex, const sf::Texture& attackTex)
    : idleTexture(idleTex), walkTexture(walkTex), attackTexture(attackTex), 
      playerAnimation(idleTex, sf::Vector2i(32, 32), 4, 1.0f) {
    
    // Set initial position and scale for the animation
    playerAnimation.setPosition({200, 0});
    playerAnimation.setScale({2.f, 2.f});
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);  // Update movement and input logic

    // Change the texture based on movement
    if (isMoving) {
        playerAnimation.changeTexture(walkTexture);
    } else {
        playerAnimation.changeTexture(idleTexture, 4);
    }

    // Handle attack texture if click is pressed
    if (click) {
        playerAnimation.changeTexture(attackTexture, 4, sf::Vector2i(43, 32), 0.4f);
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(playerAnimation.getSprite());  // Assuming Animation has a method to get the sprite
}

void Player::handleInput(float deltaTime) {
    isMoving = false;  // Reset movement state

    // Movement controls (keyboard input)
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

    // Check for mouse click or key press (Z)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        click = true;
    } else {
        click = false;
    }

    // Update player position
    playerAnimation.setPosition(playerAnimation.getPosition() + movement);
    movement = sf::Vector2f(0.f, 0.f);  // Reset movement after applying it
}


private:
    // Member variables
    sf::Vector2f movement;
    float speed = 200.f;
    bool isMoving = false;
    bool click = false;

    // Animation
    Animation playerAnimation;

    // Textures
    const sf::Texture& idleTexture;
    const sf::Texture& walkTexture;
    const sf::Texture& attackTexture;

    // Handle player input
    void handleInput(float deltaTime);
};

#endif // PLAYER_H

