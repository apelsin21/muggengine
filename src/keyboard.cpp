#include "keyboard.hpp"

mugg::core::Keyboard::Keyboard() {
    this->keys = SDL_GetKeyboardState(&this->numberOfKeys); 
}
mugg::core::Keyboard::~Keyboard() {
}

bool mugg::core::Keyboard::IsKeyDown(const std::string& key) {
    return this->keys[SDL_GetScancodeFromName(key.c_str())] ? true : false;
}
bool mugg::core::Keyboard::IsKeyUp(const std::string& key) {
    return !this->keys[SDL_GetScancodeFromName(key.c_str())] ? true : false;
}
