#ifndef FONT_HPP
#define FONT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <GL/glew.h>

#include "texture2d.hpp"
#include "guiobject.hpp"

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace mugg {
    namespace gui {
        class GUIManager;

        struct Glyph {
            float bitmapWidth, bitmapRows;
            float bitmapLeft, bitmapTop;
            float advanceX, advanceY;
        };

        class Font : public GUIObject {
            private:
                std::vector<Glyph> glyphs;

                GUIManager* parent;
            public:
                Font(GUIManager*);
                ~Font();

                virtual bool Load(const std::string&, int);
        };
    }
}

#endif
