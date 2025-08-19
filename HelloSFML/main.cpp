#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include "Cell.h"
#include "Lives.h"
#include "Enemy.h"
#include "Buff.h"
#include "Score.h"
#include "Maze.h"
#include "FileOperations.h"

#define SIZE 20
#define CELL_WIDTH 35

int main() {
    srand(static_cast<unsigned int>(time(0)));
    const std::string filename = "game_results.txt";
    int currentPos = 0;
    Lives playerLives(3);
    Score playerScore;

    sf::RenderWindow window(sf::VideoMode(CELL_WIDTH * SIZE + 200, CELL_WIDTH * SIZE + 100), "funeral maze.");
    std::vector<std::string> previousResults = loadGameResults(filename);


    sf::SoundBuffer  loseLifeBuffer, winSoundBuffer;
    if (!loseLifeBuffer.loadFromFile("resources/lose_life.wav")) {
        throw std::runtime_error("Error: Could not load 'resources/lose_life.wav'.");
    }
    if (!winSoundBuffer.loadFromFile("resources/win.wav")) {
        throw std::runtime_error("Error: Could not load 'resources/win.wav'.");
    }

    sf::Sound loseLifeSound(loseLifeBuffer);
    sf::Sound winSound(winSoundBuffer);


    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("resources/background_music.wav")) {
        throw std::runtime_error("Error: Could not load 'resources/background_music.wav'.");
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(30.f);
    backgroundMusic.play();

    const int mazeOffsetX = 100;
    const int mazeOffsetY = 50;
    Cell* maze = new Cell[SIZE * SIZE];
    for (int i = mazeOffsetY, k = 0; i < mazeOffsetY + CELL_WIDTH * SIZE; i += CELL_WIDTH) {
        for (int j = mazeOffsetX; j < mazeOffsetX + CELL_WIDTH * SIZE; j += CELL_WIDTH, k++) {
            maze[k] = Cell(j, i, k, CELL_WIDTH);
        }
    }

    makeMaze(maze, SIZE);

    sf::RectangleShape player(sf::Vector2f(CELL_WIDTH - 5, CELL_WIDTH - 5));
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("resources/reaper2.PNG")) {
        throw std::runtime_error("Error: Could not load player texture from 'resources/reaper2.png'.");
    }
    player.setTexture(&playerTexture);

    sf::RectangleShape exitShape(sf::Vector2f(CELL_WIDTH - 5, CELL_WIDTH - 5));
    sf::Texture exitTexture;
    if (!exitTexture.loadFromFile("resources/grave.PNG")) {
        throw std::runtime_error("Error: Could not load exit texture from 'resources/grave.png'.");
    }
    exitShape.setTexture(&exitTexture);
    exitShape.setPosition(maze[SIZE * SIZE - 1].getX() + 2.5f, maze[SIZE * SIZE - 1].getY() + 2.5f);

    const int numEnemies = 3;
    Enemy enemies[numEnemies];
    for (int i = 0; i < numEnemies; i++) {
        enemies[i] = Enemy(rand() % (SIZE * SIZE));
    }
    const int numBuffs = 2;
    Buff buffs[numBuffs];
    for (int i = 0; i < numBuffs; i++) {
        buffs[i] = Buff(rand() % (SIZE * SIZE));
    }

    sf::Clock enemyMoveClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                handleMove(event, maze, &currentPos, SIZE);
        }

        for (int i = 0; i < numBuffs; i++) {
            if (buffs[i].isActive() && buffs[i].getPosition() == currentPos) {
                buffs[i].gain();

                if (playerLives.isMaxLives()) {
                    playerScore.addPoints(10);
                } else {
                    playerLives.gainLife();
                }
            }
        }

        if (maze[currentPos].hasCollectible()) {
            maze[currentPos].setCollectible(false);
            playerScore.addPoints(1);
        }

        if (enemyMoveClock.getElapsedTime().asSeconds() > 0.2f) {
            for (int i = 0; i < numEnemies; i++) {
                enemies[i].moveRandom(maze, SIZE);
                if (enemies[i].getPosition() == currentPos) {
                    loseLifeSound.play();
                    playerLives.loseLife();
                    // currentPos = 0; //не решила оставить или нет лол
                }
            }
            enemyMoveClock.restart();
        }

        if (!playerLives.hasLives()) {
            if (playerScore.getScore() > 0) {
                saveGameResults(filename, playerScore.getScore());
            }
            playerLives.reset();
            playerScore.reset();
            currentPos = 0;
            makeMaze(maze, SIZE);
        }

        if (currentPos == SIZE * SIZE - 1) {
            winSound.play();
            if (playerScore.getScore() > 0) {
                saveGameResults(filename, playerScore.getScore());
            }
            currentPos = 0;
            makeMaze(maze, SIZE);
            playerLives.reset();
            playerScore.reset();
        }

        window.clear(sf::Color(29, 30, 30, 1));

        for (int i = 0; i < SIZE * SIZE; i++) {
            maze[i].    draw(window);
        }

        player.setPosition(maze[currentPos].getX() + 2.5f, maze[currentPos].getY() + 2.5f);

        window.draw(player);
        window.draw(exitShape);

        for (int i = 0; i < numEnemies; i++) {
            enemies[i].draw(window, maze);
        }
        for (int i = 0; i < numBuffs; i++) {
            buffs[i].draw(window, maze);
        }

        playerLives.draw(window, 20, 20);
        playerScore.draw(window);

        window.display();
    }

    delete[] maze;
    return 0;
}
