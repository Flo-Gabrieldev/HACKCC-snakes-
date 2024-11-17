#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class Animation {
public:
    Animation(sf::Texture& texture, sf::Vector2i frameSize, int numFrames, float duration)
        : frameSize(frameSize), numFrames(numFrames), duration(duration) {
        this->texture = texture; // Copy texture to allow changes later
        sprite.setTexture(this->texture);
        currentFrame = 0;
        elapsedTime = 0.f;
    }

    void update(float deltaTime) {
        // Update elapsed time
        elapsedTime += deltaTime;

        // If enough time has passed, move to the next frame
        if (elapsedTime >= duration / numFrames) {
            elapsedTime = 0.f;
            currentFrame = (currentFrame + 1) % numFrames; // Loop the animation

            // Set the texture rect for the current frame
            int x = (currentFrame % (texture.getSize().x / frameSize.x)) * frameSize.x;
            int y = (currentFrame / (texture.getSize().x / frameSize.x)) * frameSize.y;
            sprite.setTextureRect(sf::IntRect(x, y, frameSize.x, frameSize.y));
        }
    }

    void setPosition(sf::Vector2f position) {
        sprite.setPosition(position);
    }

    void setScale(sf::Vector2f scale) {
        sprite.setScale(scale);
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

    void changeTexture(const sf::Texture& newTexture, int newNumFrames = 4, const sf::Vector2i& vec = sf::Vector2i(32, 32), float newDuration = 1.f) {
        texture = newTexture;          // Copy the new texture
        sprite.setTexture(texture);    // Update the sprite to use the new texture
        numFrames = newNumFrames;
	frameSize = vec;
	duration = newDuration;
    }

private:
    sf::Texture texture;   // Store the texture by value instead of by reference
    sf::Sprite sprite;     // Sprite for displaying the animation
    sf::Vector2i frameSize; // Size of a single frame (width, height)
    int numFrames;          // Total number of frames in the animation
    float duration;         // Duration of the animation (in seconds)
    int currentFrame;       // Current frame index
    float elapsedTime;      // Time elapsed since the last frame change
};

#endif
