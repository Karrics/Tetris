#include "Game.hpp"
#include <QGraphicsView>
#include <QKeyEvent>
#include "InputHandler.hpp"

Game::Game(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), timer(new QTimer(this)), currentPiece(nullptr) {
    setWindowTitle("Tetris with Qt");
    resize(300, 600);

    // Настройка сцены
    scene->setSceneRect(0, 0, 300, 600);
    QGraphicsView *view = new QGraphicsView(scene, this);
    setCentralWidget(view);

    // Настройка InputHandler
    InputHandler *inputHandler = new InputHandler(this);
    installEventFilter(inputHandler);
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
    currentPiece = new Tetromino();
    scene->addItem(currentPiece);
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
}

void Game::handleKeyPress(int key) {
    if (key == Qt::Key_Left) {
        currentPiece->moveLeft();
    } else if (key == Qt::Key_Right) {
        currentPiece->moveRight();
    } else if (key == Qt::Key_Down) {
        currentPiece->moveDown();
    } else if (key == Qt::Key_Up) {
        currentPiece->rotate();
    }
}