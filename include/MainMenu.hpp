#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
#include "Game.hpp"

class MainMenu : public QMainWindow {
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void startGame();

private:
    QPushButton *startButton;
    Game *gameWindow;
};

#endif // MAINMENU_H