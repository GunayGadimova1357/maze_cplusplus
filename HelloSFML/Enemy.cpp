#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(int startPos) : _pos(startPos) {}

int Enemy::getPosition() const {
    return _pos;
}

void Enemy::setPosition(int newPos) {
    _pos = newPos;
}

void Enemy::moveRandom(Cell* maze, int size) {
    std::vector<int> possibleMoves;

    if (!maze[_pos].getWall(0)) possibleMoves.push_back(_pos - size);
    if (!maze[_pos].getWall(1)) possibleMoves.push_back(_pos + 1);
    if (!maze[_pos].getWall(2)) possibleMoves.push_back(_pos + size);
    if (!maze[_pos].getWall(3)) possibleMoves.push_back(_pos - 1);

    if (!possibleMoves.empty())
        _pos = possibleMoves[rand() % possibleMoves.size()];
}

void Enemy::draw(sf::RenderWindow& window, const Cell* maze) const {

    sf::RectangleShape rect(sf::Vector2f(CELL_WIDTH - 5, CELL_WIDTH - 5));
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("resources/ghost2.PNG")) {
        throw std::runtime_error("Error: Could not load player texture from 'resources/ghost2.png'.");
    }

   rect.setTexture(&enemyTexture);
    rect.setPosition(maze[_pos].getX() + 2.5f, maze[_pos].getY() + 2.5f);
    window.draw(rect);
}



