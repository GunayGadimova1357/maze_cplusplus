#include "Maze.h"
#include <stack>
#include <cstdlib>

void resetMaze(Cell* maze, int size) {
    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < 4; j++) maze[i].setWall(j, true);
        maze[i].setVisited(false);
    }
}

void removeWallsBetween(Cell* maze, Cell* current, Cell* chosen, int size) {
    if (current->getPos() - size == chosen->getPos()) {
        current->setWall(0, false);
        chosen->setWall(2, false);
    } else if (current->getPos() + 1 == chosen->getPos()) {
        current->setWall(1, false);
        chosen->setWall(3, false);
    } else if (current->getPos() + size == chosen->getPos()) {
        current->setWall(2, false);
        chosen->setWall(0, false);
    } else if (current->getPos() - 1 == chosen->getPos()) {
        current->setWall(3, false);
        chosen->setWall(1, false);
    }
}
void makeMaze(Cell* maze, int size) {
    resetMaze(maze, size);

    std::stack<Cell*> stack;
    maze[0].setVisited(true);
    stack.push(&maze[0]);

    while (!stack.empty()) {
        Cell* current = stack.top();
        int pos = current->getPos();
        std::vector<int> neighbours;

        if (pos % size != 0 && !maze[pos - 1].isVisited()) // Left
            neighbours.push_back(pos - 1);
        if ((pos + 1) % size != 0 && !maze[pos + 1].isVisited()) // Right
            neighbours.push_back(pos + 1);
        if (pos + size < size * size && !maze[pos + size].isVisited()) // Down
            neighbours.push_back(pos + size);
        if (pos - size >= 0 && !maze[pos - size].isVisited()) // Up
            neighbours.push_back(pos - size);

        if (!neighbours.empty()) {
            int randIndex = rand() % neighbours.size();
            Cell* chosen = &maze[neighbours[randIndex]];

            removeWallsBetween(maze, current, chosen, size);
            chosen->setVisited(true);
            stack.push(chosen);
        } else {
            stack.pop();
        }
    }
    for (int i = 0; i < size * size; i++) {
        if (i != 0 && i != size * size - 1) {
            maze[i].setCollectible(true);
        }
    }

}
void handleMove(sf::Event event, Cell* maze, int* currentPos, int size) {
    if (event.key.code == sf::Keyboard::Left && !maze[*currentPos].getWall(3))
        (*currentPos)--;
    else if (event.key.code == sf::Keyboard::Right && !maze[*currentPos].getWall(1))
        (*currentPos)++;
    else if (event.key.code == sf::Keyboard::Up && !maze[*currentPos].getWall(0))
        (*currentPos) -= size;
    else if (event.key.code == sf::Keyboard::Down && !maze[*currentPos].getWall(2))
        (*currentPos) += size;

}
