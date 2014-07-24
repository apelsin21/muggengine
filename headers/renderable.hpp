#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <GL/glew.h>

namespace mugg {
    namespace graphics {
        class Renderable {
            protected:
                GLuint ID;
            public:
                void SetID(GLuint newID) {
                    this->ID = newID;   
                }
                GLuint GetID() {
                    return this->ID;
                }
        };
    }
}

#endif
