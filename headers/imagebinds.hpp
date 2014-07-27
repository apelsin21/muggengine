#ifndef IMAGEBINDS_HPP
#define IMAGEBINDS_HPP

#include <lua.hpp>

#include "image.hpp"
#include "texture2dbinds.hpp"

namespace mugg {
    namespace binds {
        static const char* ImageName = "Image";

        mugg::gui::Image* checkImage(lua_State* L, int n) {
            return *(mugg::gui::Image**)luaL_checkudata(L, n, ImageName);
        }

        int imageDeconstructor(lua_State* L) {
            
            std::cout << "Image deconstructor\n";
            
            return 0;
        }

        int imageSetTexture(lua_State* L) {
            mugg::gui::Image* img = checkImage(L, 1);
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 2);

            img->SetTexture(texture->GetID());

            return 0;
        }

        luaL_Reg imageFuncs[] = {

            {"set_texture", imageSetTexture},

            {"__gc", imageDeconstructor},
            {NULL, NULL},
        };
    }
}

#endif
