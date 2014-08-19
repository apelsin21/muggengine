#ifndef FONT_HPP
#define FONT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "glyph.hpp"

namespace mugg {
    namespace gui {
        class GUIManager;

        class Font {
            private:
                mugg::gui::GUIManager* parent;
                GLuint textureID;
    
                int width, height;
                
                std::vector<Glyph> glyphs;
            public:
                Font(GUIManager*);
                ~Font();

                bool Load(const std::string&);

                GLuint GetTexture();
        };
    }
}

#endif
