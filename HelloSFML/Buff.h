#ifndef BUFF_H
#define BUFF_H

#include <SFML/Graphics.hpp>
#include "Cell.h"

class Buff {
private:
    int _pos;

public:

    Buff(int startPos = 0);

    int getPosition() const;

    void remove();

    bool isActive() const;

    void draw(sf::RenderWindow& window, const Cell* maze) const;

    void gain();
};

#endif // BUFF_H


