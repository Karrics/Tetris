#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsItem>
#include <QVector>
#include <QColor>
#include "Tetromino.hpp"

class Board : public QGraphicsItem {
public:
    static const int WIDTH = 10;
    static const int HEIGHT = 20;
    QColor getColorAt(int x, int y) const {
        return grid[y][x];
    }
    Board(QGraphicsScene *scene = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool isCollision(const Tetromino &tetromino) const;
    void placeTetromino(const Tetromino &tetromino);
    int clearLines();
    bool isGameOver() const { return gameOver; }

    void placeBlock(int x, int y, const QColor &color) {
        if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
            grid[y][x] = color;
        }
    }
    void checkGameOver();

private:
    QVector<QVector<QColor>> grid;
    QGraphicsScene *scene;
    bool gameOver;

    //void checkGameOver();
};

#endif // BOARD_H