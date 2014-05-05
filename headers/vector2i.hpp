#ifndef VECTOR2I_HPP
#define VECTOR2I_HPP

#include <glm/glm.hpp>

namespace mugg {
    class Vector2i {
    private:
        glm::vec2 vec;
    public:
        Vector2i() {};

        Vector2i(int x, int y);

        void SetX(int x);
        int GetX();

        void SetY(int y);
        int GetY();
        

    };
}

#endif
