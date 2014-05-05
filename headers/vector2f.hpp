#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

#include <glm/glm.hpp>

namespace mugg {
    class Vector2f {
        private:
            glm::vec2 vec;
        public:
            Vector2f();
            ~Vector2f();

            void SetX(float what);
            float GetX();

            void SetY(float what);
            float GetY();
    };
}

#endif
