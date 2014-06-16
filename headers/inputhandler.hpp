#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SFML/System.hpp>

#include "keydefs.hpp"

namespace mugg {
    namespace input {
        class InputHandler {
            private:
            public:
                InputHandler();
                ~InputHandler();

                bool IsKeyDown(mugg::input::Key key);
                bool IsKeyUp(mugg::input::Key key);
        };
    }
}

#endif
