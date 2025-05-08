#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Tetromino.h"

class Renderer {
public:
    Renderer(sf::RenderWindow& window);
    void drawGrid(const Grid& grid);
    void drawTetromino(const Tetromino<int>& tetromino);

private:
    sf::RenderWindow& window;
};

#endif // RENDERER_H