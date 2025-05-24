#include "Board.hpp"

Board::Board() : grid(HEIGHT, QVector<QColor>(WIDTH, Qt::transparent)), gameOver(false) {}

bool Board::isCollision(const Tetromino &tetromino) const {
    for (const auto &block : tetromino.getBlocks()) {
        int x = tetromino.getX() + block.x();
        int y = tetromino.getY() + block.y();
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || grid[y][x] != Qt::transparent) {
            return true;
        }
    }
    return false;
}

void Board::placeTetromino(const Tetromino &tetromino) {
    for (const auto &block : tetromino.getBlocks()) {
        int x = tetromino.getX() + block.x();
        int y = tetromino.getY() + block.y();
        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
            grid[y][x] = tetromino.getColor();
        }
    }
    checkGameOver();
}

int Board::clearLines() {
    int linesCleared = 0;
    for (int y = HEIGHT - 1; y >= 0; --y) {
        bool full = true;
        for (int x = 0; x < WIDTH; ++x) {
            if (grid[y][x] == Qt::transparent) {
                full = false;
                break;
            }
        }
        if (full) {
            grid.remove(y);
            grid.insert(0, QVector<QColor>(WIDTH, Qt::transparent));
            ++linesCleared;
            ++y; 
        }
    }
    return linesCleared;
}

void Board::checkGameOver() {
    for (int x = 0; x < WIDTH; ++x) {
        if (grid[0][x] != Qt::transparent) {
            gameOver = true;
            return;
        }
    }
}