#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <FreeImage.h>

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
                std::string filepath;
                bool loaded, hasGeneratedID, mipMaps;
                
                bool GenID();
            public:
                Texture2D();
                ~Texture2D();

                bool Load(std::string, mugg::graphics::TextureRepeatPattern, mugg::graphics::TextureFilter, bool);
                bool Load(std::string);
                std::string GetFilepath();

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
