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

            img->SetTexture(texture);

            return 0;
        }
        int imageGetTexture(lua_State* L) {
            mugg::gui::Image* img = checkImage(L, 1);

            mugg::graphics::Texture2D** texture = (mugg::graphics::Texture2D**)lua_newuserdata(L, sizeof(mugg::graphics::Texture2D*));
            *texture = img->GetTexture();

            luaL_getmetatable(L, Texture2DName);
            lua_setmetatable(L, -2);

            return 1;
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

        int imageSetScale(lua_State* L) {
            mugg::gui::Image* img = checkImage(L, 1);
            glm::vec2* vec = checkVec2(L, 2);
            
            img->SetScale(*vec);

            return 0;
        }
        int imageGetScale(lua_State* L) {
            mugg::gui::Image* img = checkImage(L, 1);

            glm::vec2** vec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
            *vec = new glm::vec2(img->GetScale());

            luaL_getmetatable(L, Vec2Name);
            lua_setmetatable(L, -2);
            
            return 1;
        }

        int imageSetRotationAngle(lua_State* L) {
            mugg::gui::Image* img = checkImage(L, 1);
           
            float angle = luaL_checknumber(L, 2);

            img->SetRotationAngle(angle);

            return 0;
        }
        int imageGetRotationAngle(lua_State* L) {
            mugg::gui::Image* img = checkImage(L, 1);

            lua_pushnumber(L, img->GetRotationAngle());
            
            return 1;
        }

        luaL_Reg imageFuncs[] = {
            {"set_texture", imageSetTexture},
            {"get_texture", imageGetTexture},
            
            {"set_position", imageSetPosition},
            {"get_position", imageGetPosition},

            {"set_scale", imageSetScale},
            {"get_scale", imageGetScale},

            {"set_rotation_angle", imageSetRotationAngle},
            {"get_rotation_angle", imageGetRotationAngle},

            {NULL, NULL},
        };
    }
}

#endif
