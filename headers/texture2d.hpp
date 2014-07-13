#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <FreeImage.h>
#include <iostream>
#include <GL/glew.h>

#include "graphicsdefs.hpp"
#include "renderable.hpp"

namespace mugg {
    namespace graphics {
        class Texture2D : public Renderable {
            private:
                FREE_IMAGE_FORMAT format;
                FIBITMAP* bitmap;
                
                mugg::graphics::TextureFilter filter;
                mugg::graphics::TextureRepeatPattern pattern;

                int width, height, bpp, colorsUsed;
                const char* filepath;
                bool loaded, hasGeneratedID, mipMaps;
                
                bool GenID();
            public:
                Texture2D();
                ~Texture2D();

                bool LoadFromFile(const char* filepath, mugg::graphics::TextureRepeatPattern pattern, mugg::graphics::TextureFilter filter, bool mipMaps);
                const char* GetFilepath();

                int GetWidth();
                int GetHeight();
                int GetBPP();
                int GetColorsUsed();
                
                bool IsLoaded();
                bool HasGeneratedID();
                bool UsesMipMaps();
                
                mugg::graphics::TextureRepeatPattern GetPattern();
                mugg::graphics::TextureFilter GetFilter();
                
                void Bind();
                void UnBind();
        };
    }
}

#endif
