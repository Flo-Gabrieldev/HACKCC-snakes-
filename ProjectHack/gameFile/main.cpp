#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "Animation.h"
#include "Enemy.h"
#include "HealthBar.h"
#include "MusicManager.h"
#include "BackgroundManager.h"
#include "FontManager.h"
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Project-X");
    sf::Vector2u windowSize = window.getSize();

   //player'score
   int score = 0;

   //font
   // Initialize FontManager with the path to the font file
    FontManager fontManager("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/character/Font/Planes_ValMore.ttf");

    // Create text for ending message
    sf::Text ending = fontManager.createText("Press A to reset", 40, sf::Color::White, sf::Vector2f(300.f, 400.f));
    sf::Text kiwiName = fontManager.createText("KIWI THE BOSS", 30, sf::Color::Black, sf::Vector2f(400.f, 0.f));
    
    
    HealthBar healthBar(100000, 600.f, 20.f, sf::Vector2f(200.f, 50.f));
    
    // Load background music
    MusicManager musicManager;

    // Load and play music
    try {
      musicManager.playBackgroundMusic("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/Music/pixel-song-27-72476.ogg", 80.f, true);
   
    } catch (const std::exception& e) {
        std::cerr << "Failed to start background music: " << e.what() << std::endl;
        return -1;
    }


    // Load the texture for coin
    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/map/coin.png")) {
        return -1;
    }

    // Create a sprite and set its texture for coin
    sf::Sprite coinSprite;
    coinSprite.setTexture(coinTexture);
    coinSprite.setPosition(570.f, 400.f);    
    coinSprite.setScale(0.07f, 0.07f); // Scale the coin to 50% of its original size
    coinSprite.setRotation(45.f);   // Rotate the coin 45 degrees

    // Load background texture
    BackgroundManager bgManager(window);
	  

    // Load textures for the enemies
    sf::Texture enemyTexture, enemyTexture2, kiwi;
    if (!enemyTexture.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/character/2 Owlet_Monster/Owlet_Monster_Walk_6.png")) {
        return -1; // Error loading texture
    }

    if (!enemyTexture2.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/character/2 Owlet_Monster/Owlet_Monster_Walk_6.png")) {
        return -1; // Error loading texture
    }

    if (!kiwi.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/character/1 Pink_Monster/Pink_Monster_Walk+Attack_6.png")) {
        return -1; // Error loading texture
    }

    // Create enemy objects using Animation class
    sf::Vector2i enemyFrameSize(32, 32);
    float enemyDuration = 1.0f;  // Adjust based on how fast you want the enemy animation
    Animation enemyAnimation(enemyTexture, enemyFrameSize, 6, enemyDuration); // Assuming 6 frames in the enemy texture
    enemyAnimation.setScale({2.f, 2.f});
    
    Animation kiwiAnimation(kiwi, enemyFrameSize, 6, enemyDuration); // Assuming 6 frames in the enemy texture
    kiwiAnimation.setScale({5.f, 5.f});

    Enemy enemy1(enemyAnimation, {300.f, 200.f}, 150.f);  // Set speed as 150
    Enemy enemy2(enemyAnimation, {400.f, 300.f}, 100.f);  // Set speed as 100
    Enemy kiwiBoss(kiwiAnimation, {700.f, 300.f}, 100.f);  // Set speed as 100
    

    // Load textures for the player animation
    sf::Texture walkTexture, idleTexture, attackTexture;
    if (!walkTexture.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/character/3 Dude_Monster/Dude_Monster_Walk_6.png")) {
        return -1;
    }

    if (!idleTexture.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/character/3 Dude_Monster/Dude_Monster_Idle_4.png")) {
        return -1;
    }


    if (!attackTexture.loadFromFile("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/character/Attack2.png")) {
        return -1;
    }

    
    // Create player animation

    sf::Vector2i frameSize(32, 32);
    float duration = 1.0f;
    Animation playerAnimation(idleTexture, frameSize, 4, duration);

    // Set player animation position and scale
    playerAnimation.setPosition({200, 0});
    playerAnimation.setScale({2.f, 2.f}); // Scale to make it visually clear

    // Speed of the sprite movement
    float speed = 200.f;

    // Clock for deltaTime and random direction timer
    sf::Clock clock;
    sf::Clock randomDirectionClock;
    
    bool checkNewMap = true;

while (window.isOpen()) {
        // Handle events
        sf::Event event;
     if(healthBar.getHealth() != 0) {
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
        bool click = false;

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


	 // Check for mouse click
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {

		 click = true;
         }

        // Change texture based on movement
        if (isMoving) {
            playerAnimation.changeTexture(walkTexture);
        } else {
            playerAnimation.changeTexture(idleTexture, 4);
        }
	
        if(click)
	{
	  playerAnimation.changeTexture(attackTexture, 4, sf::Vector2i(43, 32), .4f);
	  
        } //else playerAnimation.changeTexture(idleTexture, 4);




        // Update sprite position for player
        sf::Vector2f newPosition = playerAnimation.getSprite().getPosition() + movement;

        // Updated sprite size considering scaling
        sf::Vector2f playerSize = playerAnimation.getSprite().getGlobalBounds().getSize();


        // Enforce boundaries for player
        if (newPosition.x < 0)
            newPosition.x = 0;
        if (newPosition.y < 0)
            newPosition.y = 0;
        if (newPosition.x + playerSize.x >= 1000)  // Using playerSize for accurate boundary check
            newPosition.x = 1000 - playerSize.x;
        if (newPosition.y + playerSize.y > 850) {   // If player goes past the y-boundary
            if (checkNewMap) {
                newPosition.y = newPosition.y - 760;  // Reset player position on the new map
                checkNewMap = false;     // Switch to map 2
            }
        } 
        else if (newPosition.y < 10 && !checkNewMap) {  // If player crosses back from map 2 to map 1
            newPosition.y = 850 - playerSize.y;  // Reset player position to map 1
            checkNewMap = true;    // Switch back to map 1
        }

        if(newPosition.y + playerSize.y >= 850 && !checkNewMap) {
            newPosition.y = 750;  // Reset player position to map 1
        }            

        playerAnimation.setPosition(newPosition);

        // Update animation for the player
        playerAnimation.update(deltaTime);

        // Randomly change direction every 3 seconds
        if (randomDirectionClock.getElapsedTime().asSeconds() > 3.f) {
            enemy1.randomDirection();
            enemy2.randomDirection();
	    kiwiBoss.randomDirection();
            randomDirectionClock.restart(); // Reset the timer
        }

        // Update enemy positions
        enemy1.update(deltaTime);
        enemy2.update(deltaTime);
        kiwiBoss.update(deltaTime);

        // Enforce boundaries for enemies
        sf::Vector2f enemy1Pos = enemy1.getSprite().getPosition();
        sf::Vector2f enemy2Pos = enemy2.getSprite().getPosition();
        sf::Vector2f enemy1Size(enemy1.getSprite().getGlobalBounds().width, enemy1.getSprite().getGlobalBounds().height);
        sf::Vector2f enemy2Size(enemy2.getSprite().getGlobalBounds().width, enemy2.getSprite().getGlobalBounds().height);
        sf::Vector2f kiwipos = kiwiBoss.getSprite().getPosition();
       sf::Vector2f kiwiSize(kiwiBoss.getSprite().getGlobalBounds().width, kiwiBoss.getSprite().getGlobalBounds().height);

        // Check and enforce boundaries for enemy1
        if (enemy1Pos.x < 0)
            enemy1Pos.x = 0;
        if (enemy1Pos.y < 0)
            enemy1Pos.y = 0;
        if (enemy1Pos.x + enemy1Size.x > 1000)
            enemy1Pos.x = 1000 - enemy1Size.x;
        if (enemy1Pos.y + enemy1Size.y > 850)
            enemy1Pos.y = 850 - enemy1Size.y;

        // Update enemy1 position
        enemy1.getSprite().setPosition(enemy1Pos);

        // Check and enforce boundaries for enemy2
        if (enemy2Pos.x < 0)
            enemy2Pos.x = 0;
        if (enemy2Pos.y < 0)
            enemy2Pos.y = 0;
        if (enemy2Pos.x + enemy2Size.x > 1000)
            enemy2Pos.x = 1000 - enemy2Size.x;
        if (enemy2Pos.y + enemy2Size.y > 850)
            enemy2Pos.y = 850 - enemy2Size.y;

        // Update enemy2 position
        enemy2.getSprite().setPosition(enemy2Pos);

	// Check and enforce boundaries for kiwi
        if (kiwipos.x < 0)
            kiwipos.x = 0;
        if (kiwipos.y < 0)
            kiwipos.y = 0;
        if (kiwipos.x + kiwiSize.x > 1000)
            kiwipos.x = 1000 - kiwiSize.x;
        if (kiwipos.y + kiwiSize.y > 850)
            kiwipos.y = 850 - kiwiSize.y;

        // Update kiwi position
        kiwiBoss.getSprite().setPosition(kiwipos);


        // Check if player collects the coin
        if (playerAnimation.getSprite().getGlobalBounds().intersects(coinSprite.getGlobalBounds())) {
            score++;  // Increment the score
            coinSprite.setPosition(-100.f, -100.f);  // Move the coin off-screen or set visibility to false
            try {
                   musicManager.playCoinSound("/Users/hashi/Desktop/HACKCC-snakes-/ProjectHack/Music/coin-257878.ogg");
                } catch (const std::exception& e) {
                    std::cerr << "Failed to play coin sound: " << e.what() << std::endl;
                }
        }

        // Respawn the coin if it's off-screen
        if (coinSprite.getPosition().x == -100.f && coinSprite.getPosition().y == -100.f) {
            coinSprite.setPosition(rand() % (windowSize.x - 50), rand() % (windowSize.y - 50));  // Random position within window
        }

       // Create the score text
        sf::Text scoreText = fontManager.createText("Score: " + std::to_string(score), 24, sf::Color::White, sf::Vector2f(10.f, 10.f), score);


if (click) {
    sf::FloatRect playerBounds = playerAnimation.getSprite().getGlobalBounds();
    sf::FloatRect enemy1Bounds = enemy1.getSprite().getGlobalBounds();
    sf::FloatRect enemy2Bounds = enemy2.getSprite().getGlobalBounds();
    sf::FloatRect kiwiBounds = kiwiBoss.getSprite().getGlobalBounds();

    // Check collisions and handle them
   if (playerBounds.intersects(enemy1Bounds)) {
        // Handle collision with enemy1 (e.g., eliminate enemy1)
        score += 1;
    }
    if (playerBounds.intersects(enemy2Bounds)) {
        // Handle collision with enemy2
        score += 1;
    }


    if (playerBounds.intersects(kiwiBounds)) {
        // Handle collision with kiwi boss
        score += 5;
	healthBar.setHealth(healthBar.getHealth() - 10);
        healthBar.updateColor(); // Update color based on new health
    }
}


        // Draw everything
        window.clear();
	bgManager.draw(window, checkNewMap);

        if (checkNewMap) {
            window.draw(enemy1.getSprite());
            window.draw(enemy2.getSprite());
        } else {
            window.draw(kiwiBoss.getSprite());
	    healthBar.draw(window);
	    window.draw(kiwiName);
        }
	
        window.draw(playerAnimation.getSprite());
        window.draw(coinSprite);  // Draw the coin if it hasn't been collected
        window.draw(scoreText);   // Draw the score on the screen
        window.display();
  }

  else
  {
	playerAnimation.setPosition({600, 0});

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

                 healthBar.setHealth(100000);
         }
      window.clear();
      window.draw(ending);
      window.display();

   }

 
}

    return 0;
}
