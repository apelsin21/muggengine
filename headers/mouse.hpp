#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SDL2/SDL.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace mugg {
    namespace core {
        class Mouse {
            private:
                glm::vec2 position;
            public:
                Mouse();
                ~Mouse();

                glm::vec2 GetPosition();
                int GetX();
                int GetY();

                bool IsLeftButtonDown();
                bool IsMiddleButtonDown();
                bool IsRightButtonDown();
        };
    }
}

#endif
