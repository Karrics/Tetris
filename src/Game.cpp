#include "Game.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"
#include "InputHandler.hpp"
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>


Game::Game(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), timer(new QTimer(this)), 
      board(scene), // Передаем сцену в конструктор Board
      currentPiece(nullptr) {
    setWindowTitle("Tetris with Qt");
    resize(300, 600);

    // Настройка сцены
    scene->setSceneRect(0, 0, 300, 600);
    QGraphicsView *view = new QGraphicsView(scene, this);
    setCentralWidget(view);
    scene->addItem(&board);

    // Настройка InputHandler
    InputHandler *inputHandler = new InputHandler(this);
    view->installEventFilter(inputHandler);
    connect(inputHandler, &InputHandler::keyPressed, this, &Game::handleKeyPress);

    // Настройка таймера
    connect(timer, &QTimer::timeout, this, &Game::updateGame);
    timer->start(500);

    // Создаем первую фигуру
    spawnTetromino();
}



Game::~Game() {
    delete scene;
    delete timer;
    delete currentPiece;
}

void Game::spawnTetromino() {
    if (currentPiece) {
        scene->removeItem(currentPiece); // Удаляем текущую фигуру из сцены
        delete currentPiece;
    }
    currentPiece = new Tetromino();
    scene->addItem(currentPiece);
    scene->update();
}

void Game::updateGame() {
    if (board.isGameOver()) {
        timer->stop();
        return;
    }

    currentPiece->moveDown();
    if (board.isCollision(*currentPiece)) {
        currentPiece->moveUp();
        board.placeTetromino(*currentPiece);
        board.clearLines();
        spawnTetromino();
    }
    scene->update(); // Обновляем всю сцену
}

// Обработчик нажатий клавиш
void Game::handleKeyPress(int key) {
    if (!currentPiece) return;

    qDebug() << "Key pressed:" << key; // Отладочный вывод

    // Сохраняем предыдущие координаты
    int prevX = currentPiece->getX();
    int prevY = currentPiece->getY();

    // Двигаем фигуру
    switch (key) {
        case Qt::Key_Left:
            currentPiece->moveLeft();
            break;
        case Qt::Key_Right:
            currentPiece->moveRight();
            break;
        case Qt::Key_Down:
            currentPiece->moveDown();
            break;
        case Qt::Key_Up:
            currentPiece->rotate();
            break;
        default:
            return;
    }

    // Проверяем коллизию после движения
    if (board.isCollision(*currentPiece)) {
        // Откатываем изменения, если есть коллизия
        currentPiece->setX(prevX);
        currentPiece->setY(prevY);
        if (key == Qt::Key_Up) {
            currentPiece->rotateBack(); // Откатываем вращение
        }
    }

    // Обновляем графику
    scene->update();
}