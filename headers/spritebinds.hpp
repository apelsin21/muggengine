#ifndef spriteBINDS_HPP
#define spriteBINDS_HPP

#include <lua.hpp>

#include "sprite.hpp"
#include "texture2dbinds.hpp"
#include "vec2binds.hpp"

namespace mugg {
    namespace binds {
        static const char* SpriteName = "Sprite";

        mugg::gui::Sprite* checkSprite(lua_State* L, int n) {
            return *(mugg::gui::Sprite**)luaL_checkudata(L, n, SpriteName);
        }

        int spriteSetTexture(lua_State* L) {
            mugg::gui::Sprite* sprite = checkSprite(L, 1);
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 2);

            sprite->SetTexture(texture);

            return 0;
        }
        int spriteGetTexture(lua_State* L) {
            mugg::gui::Sprite* sprite = checkSprite(L, 1);

            mugg::graphics::Texture2D** texture = (mugg::graphics::Texture2D**)lua_newuserdata(L, sizeof(mugg::graphics::Texture2D*));
            *texture = sprite->GetTexture();

            luaL_getmetatable(L, Texture2DName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int spriteSetPosition(lua_State* L) {
            mugg::gui::Sprite* sprite = checkSprite(L, 1);
            glm::vec2* vec = checkVec2(L, 2);
            
            sprite->SetPosition(*vec);

            return 0;
        }
        int spriteGetPosition(lua_State* L) {
            mugg::gui::Sprite* sprite = checkSprite(L, 1);

            glm::vec2** vec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
            *vec = new glm::vec2(sprite->GetPosition());

            luaL_getmetatable(L, Vec2Name);
            lua_setmetatable(L, -2);
            
            return 1;
        }

        int spriteSetScale(lua_State* L) {
            mugg::gui::Sprite* sprite = checkSprite(L, 1);
            glm::vec2* vec = checkVec2(L, 2);
            
            sprite->SetScale(*vec);

            return 0;
        }
        int spriteGetScale(lua_State* L) {
            mugg::gui::Sprite* sprite = checkSprite(L, 1);

            glm::vec2** vec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
            *vec = new glm::vec2(sprite->GetScale());

            luaL_getmetatable(L, Vec2Name);
            lua_setmetatable(L, -2);
            
            return 1;
        }

        int spriteSetRotation(lua_State* L) {
            mugg::gui::Sprite* sprite = checkSprite(L, 1);
           
            float angle = luaL_checknumber(L, 2);

            sprite->SetRotation(angle);

            return 0;
        }
        int spriteGetRotation(lua_State* L) {
            mugg::gui::Sprite* sprite = checkSprite(L, 1);

            lua_pushnumber(L, sprite->GetRotation());
            
            return 1;
        }

        luaL_Reg spriteFuncs[] = {
            {"set_texture", spriteSetTexture},
            {"get_texture", spriteGetTexture},
            
            {"set_position", spriteSetPosition},
            {"get_position", spriteGetPosition},

            {"set_scale", spriteSetScale},
            {"get_scale", spriteGetScale},

            {"set_rotation", spriteSetRotation},
            {"get_rotation", spriteGetRotation},

            {NULL, NULL},
        };
    }
}

#endif
