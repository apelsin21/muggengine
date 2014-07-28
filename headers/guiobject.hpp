#ifndef GUIOBJECT_HPP
#define GUIOBJECT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "guimanager.hpp"

namespace mugg {
    namespace gui {
        class GUIObject {
            protected:
                unsigned int index;
                mugg::gui::GUIManager* creator;
            public:
                GUIObject(mugg::gui::GUIManager*, unsigned int);

                virtual mugg::gui::GUIManager* GetCreator();

                virtual void SetPosition(glm::vec2);
                virtual glm::vec2 GetPosition();

                virtual void SetTexture(GLuint);
                virtual GLuint GetTexture();
                
                virtual unsigned int GetIndex();
        };
    }
}

#endif
