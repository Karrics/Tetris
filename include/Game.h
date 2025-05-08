#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Tetromino.h"
#include "Renderer.h"
#include "InputHandler.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Grid grid;
    Renderer renderer;
    InputHandler inputHandler;
    std::unique_ptr<Tetromino<int>> currentTetromino;
    int score;

    std::unique_ptr<Tetromino<int>> createRandomTetromino();
    void processInput();
    void update();
    void render();
    void reset();
};

#endif // GAME_H