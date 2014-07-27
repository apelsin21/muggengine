#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <iostream>
#include <string>
#include <memory>

#include <GL/glew.h>

#include "graphicsdefs.hpp"
#include "globject.hpp"

namespace mugg {
    namespace graphics {
        class Texture2D : public GLObject {
            private:
                mugg::graphics::TextureFilter minFilter;
                mugg::graphics::TextureFilter magFilter;

                mugg::graphics::TextureWrap uWrap;
                mugg::graphics::TextureWrap vWrap;

                int width, height, bpp, colorsUsed;
                std::string filepath;
                bool loaded, hasGeneratedID, mipMaps;
            public:
                Texture2D() {};
                Texture2D(GLuint id);

                void SetFilepath(std::string);
                std::string GetFilepath();

                void SetWidth(int);
                int GetWidth();

                void SetHeight(int);
                int GetHeight();

                void SetBPP(int);
                int GetBPP();

                void SetColorsUsed(int);
                int GetColorsUsed();
                
                void SetLoaded(bool);
                bool IsLoaded();
                
                void SetUsesMipMaps(bool);
                bool UsesMipMaps();
               
                mugg::graphics::TextureWrap GetUWrap();
                mugg::graphics::TextureWrap GetVWrap();

                mugg::graphics::TextureFilter GetMinFilter();
                mugg::graphics::TextureFilter GetMagFilter();
                
                void SetWrap(mugg::graphics::TextureWrap, mugg::graphics::TextureWrap);
                void SetFilter(mugg::graphics::TextureFilter, mugg::graphics::TextureFilter);

                void Bind();
                void UnBind();
        };
    }
}

#endif
