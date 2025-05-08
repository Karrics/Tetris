#include "../include/Grid.h"
#include "../include/Tetromino.h"

Grid::Grid(int width, int height)
    : width(width), height(height), grid(height, std::vector<bool>(width, false)) {}

bool Grid::checkCollision(const Tetromino<int>& tetromino) const {
    for (size_t i = 0; i < tetromino.getShape().size(); ++i) {
        for (size_t j = 0; j < tetromino.getShape()[i].size(); ++j) {
            if (tetromino.getShape()[i][j]) {
                int x = tetromino.getX() + static_cast<int>(j);
                int y = tetromino.getY() + static_cast<int>(i);
                if (x < 0 || x >= width || y < 0 || y >= height || grid[y][x]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Grid::merge(const Tetromino<int>& tetromino) {
    for (size_t i = 0; i < tetromino.getShape().size(); ++i) {
        for (size_t j = 0; j < tetromino.getShape()[i].size(); ++j) {
            if (tetromino.getShape()[i][j]) {
                int x = tetromino.getX() + static_cast<int>(j);
                int y = tetromino.getY() + static_cast<int>(i);
                grid[y][x] = true;
            }
        }
    }
}

int Grid::clearLines() {
    int linesCleared = 0;
    for (int y = height - 1; y >= 0; --y) {
        bool full = true;
        for (int x = 0; x < width; ++x) {
            if (!grid[y][x]) {
                full = false;
                break;
            }
        }
        if (full) {
            grid.erase(grid.begin() + y);
            grid.insert(grid.begin(), std::vector<bool>(width, false));
            linesCleared++;
        }
    }
    return linesCleared;
}

bool Grid::isOccupied(int x, int y) const {
    return grid[y][x];
}