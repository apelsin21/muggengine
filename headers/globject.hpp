#ifndef GLOBJECT_HPP
#define GLOBJECT_HPP

#include <GL/glew.h>

namespace mugg {
    namespace graphics {
        class GLObject {
            protected:
                GLuint ID;
                unsigned int index;
            public:
                void SetID(GLuint newID) {
                    this->ID = newID;   
                }
                GLuint GetID() {
                    return this->ID;
                }

                void SetIndex(unsigned int index) {
                    this->index = index;
                }
                unsigned int GetIndex() {
                    return this->index;
                }
        };
    }
}

#endif
