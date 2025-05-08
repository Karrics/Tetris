#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Tetromino.h"  // <--- Добавьте эту строку

class Grid {
public:
    Grid(int width, int height);
    bool checkCollision(const Tetromino<int>& tetromino) const;
    void merge(const Tetromino<int>& tetromino);
    int clearLines();
    bool isOccupied(int x, int y) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width, height;
    std::vector<std::vector<bool>> grid;
};

#endif // GRID_H