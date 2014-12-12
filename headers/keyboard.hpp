#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "keydefs.hpp"

namespace mugg {
    namespace core {
        class Keyboard {
            private:
                const Uint8* keys;
                int numberOfKeys;

                std::vector<SDL_Scancode> repeatedKeys;

                SDL_Event sdlEvent;
            public:
                Keyboard();
                ~Keyboard();
                
                bool IsKeyDown(const std::string&);
                bool IsKeyUp(const std::string&);
        };
    }
}

#endif
