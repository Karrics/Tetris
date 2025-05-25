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

    Board(QGraphicsScene *scene = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    bool isCollision(const Tetromino &tetromino) const;
    void placeTetromino(const Tetromino &tetromino);
    int clearLines();
    bool isGameOver() const { return gameOver; }

private:
    QVector<QVector<QColor>> grid;
    QGraphicsScene *scene;
    bool gameOver;

    void checkGameOver();
};

#endif // BOARD_H