#include "Cell.h"


Cell::Cell()
    : _x(0), _y(0), _pos(0), _size(30.f), _thickness(2.f), _visited(false), _hasCollectible(false) {
    for (int i = 0; i < 4; i++) _walls[i] = true;
}


Cell::Cell(int x, int y, int pos, float size, float thickness)
    : _x(x), _y(y), _pos(pos), _size(size), _thickness(thickness), _visited(false), _hasCollectible(false) {
    for (int i = 0; i < 4; i++) _walls[i] = true;
}


Cell::~Cell() {}


int Cell::getX() const { return _x; }
int Cell::getY() const { return _y; }
int Cell::getPos() const { return _pos; }
float Cell::getSize() const { return _size; }
bool Cell::isVisited() const { return _visited; }
bool Cell::getWall(int index) const { return _walls[index]; }
bool Cell::hasCollectible() const { return _hasCollectible; }

void Cell::setCollectible(bool state) { _hasCollectible = state; }
void Cell::setVisited(bool state) { _visited = state; }
void Cell::setWall(int index, bool state) { _walls[index] = state; }

void Cell::draw(sf::RenderWindow& window) const {
    sf::RectangleShape rect;

    rect.setFillColor(sf::Color(103, 40, 61));

    if (_walls[0]) {
        rect.setSize(sf::Vector2f(_size, _thickness));
        rect.setPosition(_x, _y);
        window.draw(rect);
    }

    if (_walls[1]) {
        rect.setSize(sf::Vector2f(_thickness, _size));
        rect.setPosition(_x + _size, _y);
        window.draw(rect);
    }

    if (_walls[2]) {
        rect.setSize(sf::Vector2f(_size, _thickness));
        rect.setPosition(_x, _y + _size);
        window.draw(rect);
    }

    if (_walls[3]) {
        rect.setSize(sf::Vector2f(_thickness, _size));
        rect.setPosition(_x, _y);
        window.draw(rect);
    }

    if (_hasCollectible) {
        sf::CircleShape collectible(3);
        // sf::Texture pointsTexture;
        // if (!pointsTexture.loadFromFile("resources/points.PNG")) {
        //     throw std::runtime_error("Error: Could not load player texture from 'resources/sandclock.png'.");
        // }
        collectible.setFillColor(sf::Color(185, 203, 229));
        collectible.setPosition(_x + _size / 2 - 2.5f, _y + _size / 2 - 2.5f);
        window.draw(collectible);
    }
}

