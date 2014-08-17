#ifndef GUIOBJECT_HPP
#define GUIOBJECT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace mugg {
    namespace graphics {
        class Texture2D;
    }

    namespace gui {
        class GUIManager;

        class GUIObject {
            protected:
                unsigned int index;
                mugg::gui::GUIManager* parent;
                mugg::graphics::Texture2D* texture;
                glm::vec2 position, rotation, scale;
                float rotationAngle;
            public:
                GUIObject(mugg::gui::GUIManager*, unsigned int);

                virtual mugg::gui::GUIManager* GetParent();

                virtual void SetScale(const glm::vec2&);
                virtual glm::vec2 GetScale();

                virtual void SetRotation(const glm::vec2&);
                virtual glm::vec2 GetRotation();

                virtual void SetRotationAngle(float);
                virtual float GetRotationAngle();

                virtual void SetPosition(const glm::vec2&);
                virtual glm::vec2 GetPosition();

                virtual void SetTexture(mugg::graphics::Texture2D*);
                virtual mugg::graphics::Texture2D* GetTexture();
                
                virtual unsigned int GetIndex();
        };
    }
}

#endif
