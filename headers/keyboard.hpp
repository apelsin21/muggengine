#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <iostream>

#include <SDL2/SDL.h>

#include "keydefs.hpp"

namespace mugg {
    namespace core {
        class Keyboard {
            private:
                const Uint8* keys;
                int numberOfKeys;

                SDL_Event sdlEvent;
                SDL_Scancode KeyToScancode(const mugg::core::Key);
            public:
                Keyboard();
                ~Keyboard();

                virtual bool IsKeyDown(const mugg::core::Key);
                virtual bool IsKeyUp(const mugg::core::Key);
        };
    }
}

#endif
