#include "../include/Renderer.h"

Renderer::Renderer(sf::RenderWindow& window) : window(window) {}

void Renderer::drawGrid(const Grid& grid) {
    for (int y = 0; y < grid.getHeight(); ++y) {
        for (int x = 0; x < grid.getWidth(); ++x) {
            if (grid.isOccupied(x, y)) {
                sf::RectangleShape block(sf::Vector2f(30.f, 30.f));  // Явное указание .f
                block.setPosition(
                    static_cast<float>(x * 30),  // Приведение к float
                    static_cast<float>(y * 30)
                );
                block.setFillColor(sf::Color::Cyan);
                window.draw(block);
            }
        }
    }
}

void Renderer::drawTetromino(const Tetromino<int>& tetromino) {
    for (size_t i = 0; i < tetromino.getShape().size(); ++i) {
        for (size_t j = 0; j < tetromino.getShape()[i].size(); ++j) {
            if (tetromino.getShape()[i][j]) {
                sf::RectangleShape block(sf::Vector2f(30.f, 30.f));
                block.setPosition(
                    static_cast<float>((tetromino.getX() + j) * 30),
                    static_cast<float>((tetromino.getY() + i) * 30)
                );
                block.setFillColor(sf::Color::Red);
                window.draw(block);
            }
        }
    }
}