#ifndef TEXTURE2DBINDS_HPP
#define TEXTURE2DBINDS_HPP

#include <lua.hpp>

#include "graphicsdefs.hpp"
#include "texture2d.hpp"

namespace mugg {
    namespace binds {
        static const char* Texture2DPrivateName = "mugg_Texture2D";
        static const char* Texture2DPublicName = "Texture2D";

        mugg::graphics::Texture2D* checkTexture2D(lua_State* L, int n) {
            return *(mugg::graphics::Texture2D**)luaL_checkudata(L, n, Texture2DPrivateName);
        }

        int texture2DConstructor(lua_State* L) {
            mugg::graphics::Texture2D** texture = (mugg::graphics::Texture2D**)lua_newuserdata(L, sizeof(mugg::graphics::Texture2D*));

            const char* filepath = luaL_checkstring(L, 1);

            *texture = new mugg::graphics::Texture2D(filepath);

            luaL_getmetatable(L, Texture2DPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int texture2DDeconstructor(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            delete texture;
            return 0;
        }

        int texture2DGetWidth(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushnumber(L, texture->GetResolution().x);

            return 1;
        }

        int texture2DGetHeight(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushnumber(L, texture->GetResolution().y);
            
            return 1;
        }

        luaL_Reg texture2DFuncs[] = {
            {"new", texture2DConstructor},

            {"get_width", texture2DGetWidth},
            {"get_height", texture2DGetHeight},

            {"__gc", texture2DDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
