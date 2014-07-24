#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <iostream>
#include <string>
#include <memory>

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
                
                mugg::graphics::TextureFilter minFilter;
                mugg::graphics::TextureFilter magFilter;

                mugg::graphics::TextureWrap uWrap;
                mugg::graphics::TextureWrap vWrap;

                unsigned int index;

                int width, height, bpp, colorsUsed;
                std::string filepath;
                bool loaded, hasGeneratedID, mipMaps;
            public:
                Texture2D(GLuint id);
                ~Texture2D();

                void SetFilepath(std::string);
                std::string GetFilepath();

                void SetIndex(unsigned int);
                unsigned int GetIndex();

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
                
                bool HasGeneratedID();
                bool UsesMipMaps();
               
                FREE_IMAGE_FORMAT GetFormat();
                void SetFormat(const FREE_IMAGE_FORMAT&);

                FIBITMAP* GetBitmap();
                void SetBitmap(FIBITMAP*);

                mugg::graphics::TextureWrap GetUWrap();
                mugg::graphics::TextureWrap GetVWrap();

                mugg::graphics::TextureFilter GetMinFilter();
                mugg::graphics::TextureFilter GetMagFilter();
                
                void SetWrap(mugg::graphics::TextureWrap, mugg::graphics::TextureWrap);
                void SetTextureFilter(mugg::graphics::TextureFilter, mugg::graphics::TextureFilter);

                void Bind();
                void UnBind();
        };
    }
}

#endif
