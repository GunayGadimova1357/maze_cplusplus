#ifndef ENEMY_H
#define ENEMY_H

#define SIZE 20
#define CELL_WIDTH 35
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"

class Enemy {
private:
    int _pos;

public:

    Enemy(int startPos = 0);

    int getPosition() const;

    void setPosition(int newPos);

    void moveRandom(Cell* maze, int size);

    void draw(sf::RenderWindow& window, const Cell* maze) const;
};

#endif // ENEMY_H


