#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Enemy.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Boundaries Example");

    // Load textures for the enemies
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/character/1 Pink_Monster/Pink_Monster_Walk+Attack_6.png")) {
        return -1; // Error loading texture
    }

    // Create enemy objects using Animation class
    sf::Vector2i enemyFrameSize(32, 32);
    float enemyDuration = 1.0f;  // Adjust based on how fast you want the enemy animation
    Animation enemyAnimation(enemyTexture, enemyFrameSize, 6, enemyDuration); // Assuming 6 frames in the enemy texture

    Enemy enemy1(enemyAnimation, {200.f, 200.f}, 150.f);  // Set speed as 150
    Enemy enemy2(enemyAnimation, {400.f, 300.f}, 100.f);  // Set speed as 100

    // Load textures for the player animation
    sf::Texture walkTexture, idleTexture;
    if (!walkTexture.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/character/3 Dude_Monster/Dude_Monster_Walk_6.png")) {
        return -1;
    }

    if (!idleTexture.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/character/3 Dude_Monster/Dude_Monster_Idle_4.png")) {
        return -1;
    }

    // Create player animation
    sf::Vector2i frameSize(32, 32);
    float duration = 1.0f;
    Animation playerAnimation(idleTexture, frameSize, 4, duration);

    // Set player animation position and scale
    playerAnimation.setPosition({0, 0});
    playerAnimation.setScale({2.f, 2.f}); // Scale to make it visually clear

    // Speed of the sprite movement
    float speed = 200.f;

    // Clock for deltaTime and random direction timer
    sf::Clock clock;
    sf::Clock randomDirectionClock;

    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Delta time
        float deltaTime = clock.restart().asSeconds();

        // Movement vector for player
        sf::Vector2f movement(0.f, 0.f);
        bool isMoving = false;

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

        // Change texture based on movement
        if (isMoving) {
            playerAnimation.changeTexture(walkTexture);
        } else {
            playerAnimation.changeTexture(idleTexture, 4);
        }

        // Update sprite position for player
        sf::Vector2f newPosition = playerAnimation.getSprite().getPosition() + movement;

        // Enforce boundaries for player
        if (newPosition.x < 0)
            newPosition.x = 0;
        if (newPosition.y < 0)
            newPosition.y = 0;
        if (newPosition.x + frameSize.x * 2 > 1000) // Multiply by scale factor
            newPosition.x = 1000 - frameSize.x * 2;
        if (newPosition.y + frameSize.y * 2 > 500) // Multiply by scale factor
            newPosition.y = 500 - frameSize.y * 2;

        playerAnimation.setPosition(newPosition);

        // Update animation for the player
        playerAnimation.update(deltaTime);

        // Randomly change direction every 3 seconds
        if (randomDirectionClock.getElapsedTime().asSeconds() > 3.f) {
            enemy1.randomDirection();
            enemy2.randomDirection();
            randomDirectionClock.restart(); // Reset the timer
        }

        // Update enemy positions
        enemy1.update(deltaTime);
        enemy2.update(deltaTime);

        // Enforce boundaries for enemies
        sf::Vector2f enemy1Pos = enemy1.getSprite().getPosition();
        sf::Vector2f enemy2Pos = enemy2.getSprite().getPosition();

        // Check and enforce boundaries for enemy1
        if (enemy1Pos.x < 0)
            enemy1Pos.x = 0;
        if (enemy1Pos.y < 0)
            enemy1Pos.y = 0;
        if (enemy1Pos.x + enemyFrameSize.x * 2 > 1000)
            enemy1Pos.x = 1000 - enemyFrameSize.x * 2;
        if (enemy1Pos.y + enemyFrameSize.y * 2 > 500)
            enemy1Pos.y = 500 - enemyFrameSize.y * 2;

        // Set the new position after boundary enforcement
        enemy1.getSprite().setPosition(enemy1Pos);

        // Check and enforce boundaries for enemy2
        if (enemy2Pos.x < 0)
            enemy2Pos.x = 0;
        if (enemy2Pos.y < 0)
            enemy2Pos.y = 0;
        if (enemy2Pos.x + enemyFrameSize.x * 2 > 1000)
            enemy2Pos.x = 1000 - enemyFrameSize.x * 2;
        if (enemy2Pos.y + enemyFrameSize.y * 2 > 500)
            enemy2Pos.y = 500 - enemyFrameSize.y * 2;

        // Set the new position after boundary enforcement
        enemy2.getSprite().setPosition(enemy2Pos);

        // Render
        window.clear();
        window.draw(playerAnimation.getSprite());  // Draw the player sprite
        window.draw(enemy1.getSprite());           // Draw enemy1
        window.draw(enemy2.getSprite());           // Draw enemy2
        window.display();
    }

    return 0;
}

