#ifndef IMAGEBINDS_HPP
#define IMAGEBINDS_HPP

#include <lua.hpp>

#include "image.hpp"
#include "texture2dbinds.hpp"
#include "vec2binds.hpp"

namespace mugg {
    namespace binds {
        static const char* ImageName = "Image";

        mugg::gui::Image* checkImage(lua_State* L, int n) {
            return *(mugg::gui::Image**)luaL_checkudata(L, n, ImageName);
        }

        int imageSetTexture(lua_State* L) {
            mugg::gui::Image* img = checkImage(L, 1);
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 2);

            img->SetTexture(texture->GetID());

            return 0;
        }

        int imageSetPosition(lua_State* L) {
            mugg::gui::Image* img = checkImage(L, 1);
            glm::vec2* vec = checkVec2(L, 2);
            
            img->SetPosition(*vec);

            return 0;
        }
        int imageGetPosition(lua_State* L) {
            mugg::gui::Image* img = checkImage(L, 1);

            glm::vec2** vec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
            *vec = new glm::vec2(img->GetPosition());

            luaL_getmetatable(L, Vec2Name);
            lua_setmetatable(L, -2);
            
            return 1;
        }

        luaL_Reg imageFuncs[] = {
            {"set_texture", imageSetTexture},
            
            {"set_position", imageSetPosition},
            {"get_position", imageGetPosition},

            {NULL, NULL},
        };
    }
}

#endif
