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

                virtual glm::vec2 GetPosition();
                virtual int GetX();
                virtual int GetY();

                virtual bool IsLeftButtonDown();
                virtual bool IsMiddleButtonDown();
                virtual bool IsRightButtonDown();
        };
    }
}

#endif
