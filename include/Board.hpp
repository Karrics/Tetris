#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QColor>
#include "Tetromino.hpp"

class Board {
public:
    static const int WIDTH = 10;
    static const int HEIGHT = 20;

    Board();
    bool isCollision(const Tetromino &tetromino) const;
    void placeTetromino(const Tetromino &tetromino);
    int clearLines();
    bool isGameOver() const { return gameOver; }

private:
    QVector<QVector<QColor>> grid;
    bool gameOver;

    void checkGameOver(); // Метод для проверки завершения игры
};

#endif 