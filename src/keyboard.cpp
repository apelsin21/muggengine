#include "keyboard.hpp"

mugg::core::Keyboard::Keyboard() {
    this->keys = SDL_GetKeyboardState(&this->numberOfKeys); 
}
mugg::core::Keyboard::~Keyboard() {
}

SDL_Scancode mugg::core::Keyboard::KeyToScancode(const mugg::core::Key key) {
    int keyAsNumber = key;
    //Fucking inconsistent enums, atleast SFML did it right
    //For every jump, add jump size to keyAsNumber
    if(key > 0) {
        keyAsNumber += 3;
    }
    
    return (SDL_Scancode)keyAsNumber;
}

bool mugg::core::Keyboard::IsKeyDown(const mugg::core::Key key) {
    SDL_Scancode scancode = this->KeyToScancode(key);

    std::cout << "Mugg key: " << key << " AKA: " << mugg::core::KeyString[key] << std::endl;
    std::cout << "SDL_Scancode: " << scancode << " AKA: " << SDL_GetScancodeName(scancode) << std::endl;

    for(unsigned int i = 0; i <= this->numberOfKeys; i++) {
        if(this->keys[scancode]) {
            return true;
        }
    }
    return false;
}
bool mugg::core::Keyboard::IsKeyUp(const mugg::core::Key key) {
}
