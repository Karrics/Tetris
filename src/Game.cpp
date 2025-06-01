#include "Game.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"
#include "InputHandler.hpp"
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>


Game::Game(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)), timer(new QTimer(this)), 
      board(scene), 
      currentPiece(nullptr) {
    setWindowTitle("Tetris with Qt");
    resize(300, 600);

    scene->setSceneRect(0, 0, 300, 600);
    QGraphicsView *view = new QGraphicsView(scene, this);
    setCentralWidget(view);
    scene->addItem(&board);

    InputHandler *inputHandler = new InputHandler(this);
    view->installEventFilter(inputHandler);
    connect(inputHandler, &InputHandler::keyPressed, this, &Game::handleKeyPress);

    connect(timer, &QTimer::timeout, this, &Game::updateGame);
    timer->start(500);

    spawnTetromino();
}



Game::~Game() {
    delete scene;
    delete timer;
    delete currentPiece;
}

void Game::spawnTetromino() {
    if (currentPiece) {
        scene->removeItem(currentPiece); 
        delete currentPiece;
    }
    currentPiece = new Tetromino();
    scene->addItem(currentPiece);
    scene->update();
}

void Game::updateGame() {
    if (board.isGameOver()) {
        timer->stop();
        emit gameOver();


        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Game Over");
        msgBox.setText("Игра окончена!");
        msgBox.setIconPixmap(QPixmap("../resources/icons/game_over.png")); // Путь к вашей иконке
        msgBox.addButton(QMessageBox::Ok);


        msgBox.exec();


        QTimer::singleShot(0, this, [this]() {
            this->hide();
        });
        return;
    }

    currentPiece->moveDown();
    if (board.isCollision(*currentPiece)) {
        currentPiece->moveUp();
        board.placeTetromino(*currentPiece);
        board.clearLines();
        spawnTetromino();
    }
    scene->update();
}

void Game::handleKeyPress(int key) {
    if (!currentPiece) return;

    qDebug() << "Key pressed:" << key; 

    int prevX = currentPiece->getX();
    int prevY = currentPiece->getY();

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

    if (board.isCollision(*currentPiece)) {
        currentPiece->setX(prevX);
        currentPiece->setY(prevY);
        if (key == Qt::Key_Up) {
            currentPiece->rotateBack(); 
        }
    }

    scene->update();
}