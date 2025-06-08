#include "../include/Board.hpp"
#include "../include/Tetromino.hpp"
#include <QPainter>


Board::Board(QGraphicsScene *scene)
    : QGraphicsItem(), scene(scene), grid(HEIGHT, QVector<QColor>(WIDTH, Qt::transparent)), gameOver(false) {}

QRectF Board::boundingRect() const {
    return QRectF(0, 0, WIDTH * 30, HEIGHT * 30);
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (grid[y][x] != Qt::transparent) {
                painter->setBrush(grid[y][x]);
                painter->drawRect(x * 30, y * 30, 30, 30);
            }
        }
    }
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
            grid.removeAt(y);
            grid.insert(0, QVector<QColor>(WIDTH, Qt::transparent));
            ++linesCleared;
            ++y; 
            update(); 
        }
    }

    return linesCleared;
}

bool Board::isCollision(const Tetromino &tetromino) const {
    for (const auto &block : tetromino.getBlocks()) {
        int x = tetromino.getX() + block.x();
        int y = tetromino.getY() + block.y();

        if (x < 0 || x >= WIDTH || y >= HEIGHT) {
            return true;
        }

        if (y >= 0 && grid[y][x] != Qt::transparent) {
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
    update(); 
}


void Board::checkGameOver() {
    for (int x = 0; x < WIDTH; ++x) {
        if (grid[0][x] != Qt::transparent) {
            gameOver = true;
            return;
        }
    }
}