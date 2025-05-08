#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Window/Keyboard.hpp>  // Для sf::Keyboard::Key

class InputHandler {
public:
    bool isKeyPressed(sf::Keyboard::Key key) const {
        return sf::Keyboard::isKeyPressed(key);
    }
};

#endif // INPUTHANDLER_H