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
            public:
                Image(mugg::gui::GUIManager*);
                ~Image();
        };
    }
}

#endif
