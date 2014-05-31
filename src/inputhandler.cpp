#include "inputhandler.hpp"

mugg::input::InputHandler::InputHandler() {
}
mugg::input::InputHandler::~InputHandler() {
}

bool mugg::input::InputHandler::IsKeyDown(mugg::input::Key key) {
    if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key)) {
        return true;
    } else {
        return false;
    }
}

bool mugg::input::InputHandler::IsKeyUp(mugg::input::Key key) {
    if(!sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key)) {
        return true;
    } else {
        return false;
    }
}
