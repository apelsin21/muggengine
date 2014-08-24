#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "guiobject.hpp"
#include "texture2d.hpp"

namespace mugg {
    namespace gui {
        class GUIManager;
        
        class Image : public GUIObject {
            private:
                unsigned int spriteBatchIndex;
            public:
                Image(mugg::gui::GUIManager*, unsigned int);
                ~Image();

                virtual unsigned int GetSpriteBatchIndex();
                virtual void SetSpriteBatchIndex(unsigned int);
        };
    }
}

#endif
