#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <stdexcept>

class MusicManager {
private:
    sf::Music coinSound;
    sf::Music backgroundMusic;

public:
    // Load and play the coin sound
    void playCoinSound(const std::string& filePath) {
        if (!coinSound.openFromFile(filePath)) {
            throw std::runtime_error("Failed to load coin sound: " + filePath);
        }
        coinSound.play();
    }

    // Load, configure, and play background music
    void playBackgroundMusic(const std::string& filePath, float volume = 100.f, bool loop = true) {
        try {
            if (!backgroundMusic.openFromFile(filePath)) {
                throw std::runtime_error("Failed to load background music: " + filePath);
            }
            backgroundMusic.setVolume(volume);
            backgroundMusic.setLoop(loop);
            backgroundMusic.play();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};

#endif // MUSIC_MANAGER_H

