#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell {
private:
    int _x, _y;
    int _pos;
    float _size;
    float _thickness;
    bool _walls[4];
    bool _visited;
    bool _hasCollectible;

public:
    Cell();
    Cell(int x, int y, int pos, float size = 30.f, float thickness = 2.f);

    ~Cell();


    int getX() const;
    int getY() const;
    int getPos() const;
    float getSize() const;
    bool isVisited() const;
    bool getWall(int index) const;
    bool hasCollectible() const;


    void setCollectible(bool state);
    void setVisited(bool state);
    void setWall(int index, bool state);


    void draw(sf::RenderWindow& window) const;
};

#endif // CELL_H

