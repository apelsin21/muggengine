#ifndef GLOBJECT_HPP
#define GLOBJECT_HPP

#include <GL/glew.h>

namespace mugg {
    namespace core {
        class ContentManager;
    }
    
    namespace graphics {
        class GLObject {
            protected:
                GLuint ID = -1;
                unsigned int index = 0;
                mugg::core::ContentManager* parent;
                bool hasGeneratedID;
            public:
                GLObject(mugg::core::ContentManager* parent) {
                    this->parent = parent;
                    this->hasGeneratedID = false;
                }
                
                mugg::core::ContentManager* GetParent() {
                    return this->parent;
                }

                void SetID(GLuint newID) {
                    this->ID = newID;   
                }
                GLuint GetID() {
                    return this->ID;
                }

                bool HasGeneratedID() {
                    return this->hasGeneratedID;
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
