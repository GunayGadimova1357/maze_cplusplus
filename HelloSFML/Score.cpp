#include "Score.h"
#include <stdexcept>

Score::Score() : _currentScore(0) {
    if (!_font.loadFromFile("resources/PixelifySans-VariableFont_wght.ttf")) {
        throw std::runtime_error("Failed to load font!");
    }
    _scoreText.setFont(_font);
    _scoreText.setCharacterSize(24);
    _scoreText.setFillColor(sf::Color::White);
    _scoreText.setPosition(400, 10);
    updateText();
}


void Score::updateText() {
    _scoreText.setString("Score: " + std::to_string(_currentScore));
}


void Score::addPoints(int points) {
    _currentScore += points;
    updateText();
}


int Score::getScore() const {
    return _currentScore;
}


void Score::reset() {
    _currentScore = 0;
    updateText();
}


void Score::draw(sf::RenderWindow& window) const {
    window.draw(_scoreText);
}

