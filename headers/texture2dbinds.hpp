#ifndef TEXTURE2DBINDS_HPP
#define TEXTURE2DBINDS_HPP

#include <lua.hpp>
#include <iostream>

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
            *texture = new mugg::graphics::Texture2D();

            luaL_getmetatable(L, Texture2DPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int texture2DDeconstructor(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            delete texture;

            return 0;
        }

        int texture2DLoadFromFile(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            const char* filepath = luaL_checkstring(L, 2);
            mugg::graphics::TextureRepeatPattern pattern = (mugg::graphics::TextureRepeatPattern)luaL_checkoption(L, 3, NULL, mugg::graphics::TextureRepeatPatternString);
            mugg::graphics::TextureFilter filter = (mugg::graphics::TextureFilter)luaL_checkoption(L, 4, NULL, mugg::graphics::TextureFilterString);
            
            bool mipMaps = false;

            if(lua_isboolean(L, 5)) {
                mipMaps = lua_toboolean(L, 5);
            } else {
                luaL_error(L, "Argument to load_from_file wasn't a boolean\n");
            }

            texture->LoadFromFile(filepath, pattern, filter, mipMaps);

            return 0;
        }

        int texture2DGetFilepath(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushstring(L, texture->GetFilepath());

            return 1;
        }

        int texture2DGetWidth(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushnumber(L, texture->GetWidth());

            return 1;
        }
        int texture2DGetHeight(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushnumber(L, texture->GetHeight());

            return 1;
        }
        int texture2DGetBPP(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushnumber(L, texture->GetBPP());

            return 1;
        }
        int texture2DGetColorsUsed(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushnumber(L, texture->GetColorsUsed());

            return 1;
        }
        int texture2DGetID(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushnumber(L, texture->GetID());

            return 1;
        }
        int texture2DGetLoaded(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushboolean(L, texture->IsLoaded());

            return 1;
        }
        int texture2DGetHasGeneratedID(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushboolean(L, texture->HasGeneratedID());

            return 1;
        }
        int texture2DGetUsesMipMaps(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushboolean(L, texture->UsesMipMaps());

            return 1;
        }
    
        luaL_Reg texture2DFuncs[] = {
            {"new", texture2DConstructor},

            {"load", texture2DLoadFromFile},
            {"get_filepath", texture2DGetFilepath},

            {"get_width", texture2DGetWidth},
            {"get_height", texture2DGetHeight},

            {"get_bpp", texture2DGetBPP},
            {"get_colors_used", texture2DGetColorsUsed},

            {"get_gl_id", texture2DGetID},

            {"is_loaded", texture2DGetLoaded},
            {"has_generated_id", texture2DGetHasGeneratedID},
            {"uses_mipmaps", texture2DGetUsesMipMaps},

            {"__gc", texture2DDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
