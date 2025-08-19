#ifndef LIVES_H
#define LIVES_H

#include <SFML/Graphics.hpp>

class Lives {
private:
    int _maxLives;
    int _currentLives;

public:
    Lives(int lives);

    void loseLife();
    bool hasLives() const;
    void reset();
    void draw(sf::RenderWindow& window, float x, float y) const;
    bool isMaxLives() const;
    void gainLife();
};

#endif // LIVES_H

