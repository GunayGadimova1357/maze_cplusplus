#include "Buff.h"
#define SIZE 20
#define CELL_WIDTH 35
Buff::Buff(int startPos) : _pos(startPos) {}

int Buff::getPosition() const {
    return _pos;
}

void Buff::remove() {
    _pos = -1;
}

bool Buff::isActive() const {
    return _pos != -1;
}

void Buff::draw(sf::RenderWindow& window, const Cell* maze) const {
    if (!isActive()) return;


    sf::CircleShape buff(15);
    sf::Texture buffTexture;
    if (!buffTexture.loadFromFile("resources/apple.PNG")) {
        throw std::runtime_error("Error: Could not load player texture from 'resources/apple.png'.");
    }

    buff.setTexture(&buffTexture);
    buff.setPosition(
        maze[_pos].getX() + CELL_WIDTH / 4.0f,
        maze[_pos].getY() + CELL_WIDTH / 4.0f
    );
    window.draw(buff);
}

void Buff::gain() {
    remove();
}
