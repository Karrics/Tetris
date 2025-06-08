#include "../include/MainMenu.hpp"
#include <QVBoxLayout>
#include <QApplication>

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent), gameWindow(nullptr) {
    setWindowTitle("Tetris - Main Menu");
    resize(300, 200);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    startButton = new QPushButton("Начать игру", this);
    layout->addWidget(startButton);

    setCentralWidget(centralWidget);

    connect(startButton, &QPushButton::clicked, this, &MainMenu::startGame);
}

MainMenu::~MainMenu() {
    delete gameWindow;
}

void MainMenu::startGame() {
    if (!gameWindow) {
        gameWindow = new Game();
        connect(gameWindow, &Game::gameOver, this, [this]() {
            this->show(); 
            gameWindow->hide(); 
            gameWindow = nullptr;
        });
    }
    gameWindow->show();
    this->hide();
}