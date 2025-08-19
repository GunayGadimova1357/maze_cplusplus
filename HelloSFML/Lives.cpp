#include "Lives.h"

Lives::Lives(int lives) : _maxLives(lives), _currentLives(lives) {}

void Lives::loseLife() { if (_currentLives > 0) _currentLives--; }
bool Lives::hasLives() const { return _currentLives > 0; }
void Lives::reset() { _currentLives = _maxLives; }
bool Lives::isMaxLives() const { return _currentLives >= _maxLives; }
void Lives::gainLife() { if (_currentLives < _maxLives) _currentLives++; }

void Lives::draw(sf::RenderWindow& window, float x, float y) const {
    for (int i = 0; i < _currentLives; i++) {
        sf::CircleShape heart(15);
        sf::Texture heartTexture;
        if (!heartTexture.loadFromFile("resources/scull.PNG")) {
            throw std::runtime_error("Error: Could not load player texture from 'resources/scull.png'.");
        }

        heart.setTexture(&heartTexture);
        heart.setPosition(x + i * 27, y);
        window.draw(heart);
    }
}

