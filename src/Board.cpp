#include "Board.hpp"
#include "Tetromino.hpp"
#include <QPainter>

Board::Board(QGraphicsScene *scene)
    : QGraphicsItem(), scene(scene), grid(HEIGHT, QVector<QColor>(WIDTH, Qt::transparent)), gameOver(false) {}

QRectF Board::boundingRect() const {
    return QRectF(0, 0, WIDTH * 30, HEIGHT * 30); // Размер доски
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

    // Проходим по всем строкам снизу вверх
    for (int y = HEIGHT - 1; y >= 0; --y) {
        bool full = true;
        for (int x = 0; x < WIDTH; ++x) {
            if (grid[y][x] == Qt::transparent) {
                full = false;
                break;
            }
        }

        if (full) {
            // Удаляем заполненную строку
            grid.removeAt(y);
            // Добавляем пустую строку вверху
            grid.insert(0, QVector<QColor>(WIDTH, Qt::transparent));
            ++linesCleared;
            ++y; // Проверяем ту же строку снова
            update(); // Обновляем графику
        }
    }

    return linesCleared;
}

// Остальные методы остаются без изменений
bool Board::isCollision(const Tetromino &tetromino) const {
    for (const auto &block : tetromino.getBlocks()) {
        int x = tetromino.getX() + block.x();
        int y = tetromino.getY() + block.y();

        // Проверяем выход за границы поля
        if (x < 0 || x >= WIDTH || y >= HEIGHT) { // Убрано условие y < 0
            return true;
        }

        // Проверяем столкновение с другими блоками
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
    update(); // Обновляем графику после размещения фигуры
}


void Board::checkGameOver() {
    for (int x = 0; x < WIDTH; ++x) {
        if (grid[0][x] != Qt::transparent) {
            gameOver = true;
            return;
        }
    }
}