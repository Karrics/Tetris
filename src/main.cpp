#include <QApplication>
#include "Game.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Game game;
    game.show();
    return app.exec();
}