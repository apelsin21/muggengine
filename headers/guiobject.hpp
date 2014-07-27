#ifndef GUIOBJECT_HPP
#define GUIOBJECT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>


namespace mugg {
    namespace gui {
        class GUIManager;
        
        class GUIObject {
            protected:
                GLuint texture = 0;
                glm::vec2 position;
                mugg::gui::GUIManager* creator;
            public:
                GUIObject(mugg::gui::GUIManager* creator) {
                    this->creator = creator;
                }

                virtual mugg::gui::GUIManager* GetCreator() {
                    return this->creator;
                }

                virtual void SetPosition(glm::vec2 position) {
                    this->position = position;
                }
                virtual glm::vec2 GetPosition() {
                    return this->position;
                }

                virtual void SetTexture(GLuint texture) {
                    this->texture = texture;
                }
                virtual GLuint GetTexture() {
                    return this->texture;
                }
        };
    }
}

#endif
