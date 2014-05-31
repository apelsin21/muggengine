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
bool mugg::input::InputHandler::IsKeyDown(const char* keyAsString) {
    if(keyAsString == "A")
        return this->IsKeyDown(mugg::input::Key::A);
    else if(keyAsString == "B")
        return this->IsKeyDown(mugg::input::Key::B);
    else if(keyAsString == "C")
        return this->IsKeyDown(mugg::input::Key::C);
    else if(keyAsString == "D")
        return this->IsKeyDown(mugg::input::Key::D);
    else if(keyAsString == "F")
        return this->IsKeyDown(mugg::input::Key::F);
    else if(keyAsString == "G")
        return this->IsKeyDown(mugg::input::Key::G);
    else if(keyAsString == "H")
        return this->IsKeyDown(mugg::input::Key::H);
    else if(keyAsString == "I")
        return this->IsKeyDown(mugg::input::Key::I);
    else if(keyAsString == "J")
        return this->IsKeyDown(mugg::input::Key::J);
    else if(keyAsString == "K")
        return this->IsKeyDown(mugg::input::Key::K);
    else if(keyAsString == "L")
        return this->IsKeyDown(mugg::input::Key::L);
    else if(keyAsString == "M")
        return this->IsKeyDown(mugg::input::Key::M);
    else if(keyAsString == "N")
        return this->IsKeyDown(mugg::input::Key::N);
    else if(keyAsString == "O")
        return this->IsKeyDown(mugg::input::Key::O);
    else if(keyAsString == "P")
        return this->IsKeyDown(mugg::input::Key::P);
    else if(keyAsString == "Q")
        return this->IsKeyDown(mugg::input::Key::Q);
    else if(keyAsString == "R")
        return this->IsKeyDown(mugg::input::Key::R);
    else if(keyAsString == "S")
        return this->IsKeyDown(mugg::input::Key::S);
    else if(keyAsString == "T")
        return this->IsKeyDown(mugg::input::Key::T);
    else if(keyAsString == "U")
        return this->IsKeyDown(mugg::input::Key::U);
    else if(keyAsString == "V")
        return this->IsKeyDown(mugg::input::Key::V);
    else if(keyAsString == "W")
        return this->IsKeyDown(mugg::input::Key::W);
    else if(keyAsString == "X")
        return this->IsKeyDown(mugg::input::Key::X);
    else if(keyAsString == "Y")
        return this->IsKeyDown(mugg::input::Key::Y);
    else if(keyAsString == "Z")
        return this->IsKeyDown(mugg::input::Key::Z);
    else if(keyAsString == "Escape")
        return this->IsKeyDown(mugg::input::Key::Escape);
    else
        return this->IsKeyDown(mugg::input::Key::Unknown);
}

bool mugg::input::InputHandler::IsKeyUp(mugg::input::Key key) {
    if(!sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key)) {
        return true;
    } else {
        return false;
    }
}
