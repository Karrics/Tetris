#include "../include/Tetromino.hpp"
#include <QPainter>
#include <QRandomGenerator>

Tetromino::Tetromino() : x(4), y(0) {
    static const QVector<QVector<QPoint>> shapes = {
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}}, // I
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}}, // O
        {{0, 0}, {1, 0}, {2, 0}, {1, 1}}, // T
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}}, // L
        {{0, 1}, {1, 1}, {2, 1}, {2, 0}}  // J
    };
    blocks = shapes[QRandomGenerator::global()->bounded(shapes.size())];
    color = QColor(QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256),
                   QRandomGenerator::global()->bounded(256));
}

QRectF Tetromino::boundingRect() const {
    return QRectF(-1, -1, 300, 600); 
}

void Tetromino::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(color);
    for (const auto &block : blocks) {
        int blockX = (x + block.x()) * 30;
        int blockY = (y + block.y()) * 30;
        painter->drawRect(blockX, blockY, 30, 30);
    }
}

void Tetromino::moveDown() {
    y++; 
    update(); 
}

void Tetromino::moveUp() {
    y--; 
    update(); 
}

void Tetromino::moveLeft() {
    x--;
    update();
}

void Tetromino::moveRight() {
    x++;
    update();
}

void Tetromino::rotate() {
    for (auto &block : blocks) {
        int temp = block.x();
        block.rx() = block.y();
        block.ry() = -temp;
    }
    update(); 
}

void Tetromino::rotateBack() {
    for (auto &block : blocks) {
        int temp = block.x();
        block.rx() = -block.y();
        block.ry() = temp;
    }
    update();
}

