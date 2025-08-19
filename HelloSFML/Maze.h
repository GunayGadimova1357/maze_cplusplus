#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"

void resetMaze(Cell* maze, int size);
void removeWallsBetween(Cell* maze, Cell* current, Cell* chosen, int size);
void makeMaze(Cell* maze, int size);
void handleMove(sf::Event event, Cell* maze, int* currentPos, int size);



#endif //MAZE_H
