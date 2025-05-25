#include "InputHandler.hpp"
#include <QKeyEvent>

InputHandler::InputHandler(QObject *parent)
    : QObject(parent) {}

bool InputHandler::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        emit keyPressed(keyEvent->key()); // Генерация сигнала
        return true;
    }
    return QObject::eventFilter(obj, event);
}