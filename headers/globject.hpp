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
                GLuint ID = 0;
                unsigned int index = 0;
                mugg::core::ContentManager* creator;
            public:
                GLObject(mugg::core::ContentManager* creator) {
                    this->creator = creator;
                }
                
                virtual mugg::core::ContentManager* GetCreator() {
                    return this->creator;
                }

                virtual void SetID(GLuint newID) {
                    this->ID = newID;   
                }
                virtual GLuint GetID() {
                    return this->ID;
                }

                virtual void SetIndex(unsigned int index) {
                    this->index = index;
                }
                virtual unsigned int GetIndex() {
                    return this->index;
                }
        };
    }
}

#endif
