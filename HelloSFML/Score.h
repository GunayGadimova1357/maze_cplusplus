#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <string>

class Score {
private:
    int _currentScore;
    sf::Font _font;
    sf::Text _scoreText;



public:
    Score();
    void addPoints(int points);
    int getScore() const;
    void reset();
    void draw(sf::RenderWindow& window) const;
    void updateText();
};

#endif // SCORE_H



