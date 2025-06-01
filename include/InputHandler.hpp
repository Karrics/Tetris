#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QObject>
#include <QKeyEvent>

class InputHandler : public QObject {
    Q_OBJECT 

public:
    explicit InputHandler(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void keyPressed(int key); 
};

#endif 