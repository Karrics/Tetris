#include "../include/Game.h"
#include <cstdlib>
#include <ctime>

Game::Game()
    : window(sf::VideoMode(sf::Vector2u(300u, 600u)), "Tetris"),  // Vector2u для SFML 3.0.0
      grid(10, 20),
      renderer(window),
      inputHandler(),
      currentTetromino(createRandomTetromino()),
      score(0) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Game::processInput() {
    // Исправление: event->type -> event->type (без EventType)
    while (auto event = window.pollEvent()) {
        if (event->type == sf::Event::Closed) {  // Убран EventType
            window.close();
        }
    }

    // Исправление 3: Используем sf::Keyboard::Key::XXX
    if (inputHandler.isKeyPressed(sf::Keyboard::Key::Left)) {
        currentTetromino->move(-1, 0);
        if (grid.checkCollision(*currentTetromino)) {
            currentTetromino->move(1, 0);
        }
    }
    if (inputHandler.isKeyPressed(sf::Keyboard::Key::Right)) {
        currentTetromino->move(1, 0);
        if (grid.checkCollision(*currentTetromino)) {
            currentTetromino->move(-1, 0);
        }
    }
    if (inputHandler.isKeyPressed(sf::Keyboard::Key::Down)) {
        currentTetromino->move(0, 1);
        if (grid.checkCollision(*currentTetromino)) {
            currentTetromino->move(0, -1);
        }
    }
    if (inputHandler.isKeyPressed(sf::Keyboard::Key::Up)) {
        currentTetromino->rotate();
        if (grid.checkCollision(*currentTetromino)) {
            // Откат поворота (упрощенно)
            currentTetromino->rotate();
            currentTetromino->rotate();
            currentTetromino->rotate();
        }
    }
}

void Game::update() {
    static sf::Clock fallClock;
    if (fallClock.getElapsedTime().asSeconds() >= 0.5f) {
        currentTetromino->move(0, 1);
        if (grid.checkCollision(*currentTetromino)) {
            currentTetromino->move(0, -1);
            grid.merge(*currentTetromino);
            score += grid.clearLines();
            currentTetromino = createRandomTetromino();
            if (grid.checkCollision(*currentTetromino)) {
                reset();
            }
        }
        fallClock.restart();
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    renderer.drawGrid(grid);
    renderer.drawTetromino(*currentTetromino);
    window.display();
}

std::unique_ptr<Tetromino<int>> Game::createRandomTetromino() {
    static const std::vector<std::vector<std::vector<int>>> shapes = {
        {{1, 1, 1, 1}},  // I
        {{1, 1}, {1, 1}}, // O
        {{0, 1, 0}, {1, 1, 1}}, // T
        {{1, 0, 0}, {1, 1, 1}}, // L
        {{0, 0, 1}, {1, 1, 1}}  // J
    };
    int index = rand() % shapes.size();
    return std::make_unique<Tetromino<int>>(shapes[index], 4, 0);
}

void Game::reset() {
    grid = Grid(10, 20);
    currentTetromino = createRandomTetromino();
    score = 0;
}

void Game::run() {
    while (window.isOpen()) {
        processInput();
        update();
        render();
    }
}