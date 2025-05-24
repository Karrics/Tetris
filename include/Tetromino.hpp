#ifndef TETROMINO_H
#define TETROMINO_H

#include <QGraphicsItem>
#include <QVector>
#include <QColor>
#include <QPoint>

class Tetromino : public QGraphicsItem {
public:
    Tetromino();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    void rotate();

    int getX() const { return x; }
    int getY() const { return y; }
    QVector<QPoint> getBlocks() const { return blocks; }
    QColor getColor() const { return color; }

private:
    QVector<QPoint> blocks;
    int x, y;
    QColor color;
};

#endif 