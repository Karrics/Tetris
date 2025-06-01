#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "Board.hpp"
#include "Tetromino.hpp"

class Game : public QMainWindow {
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

signals:
    void gameOver();

private slots:
    void updateGame();
    void handleKeyPress(int key);

private:
    QGraphicsScene *scene;
    QTimer *timer;
    Board board;
    Tetromino *currentPiece;
    void spawnTetromino();
};

#endif 