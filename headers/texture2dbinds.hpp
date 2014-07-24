#ifndef TEXTURE2DBINDS_HPP
#define TEXTURE2DBINDS_HPP

#include <lua.hpp>
#include <iostream>

#include "texture2d.hpp"
#include "contentmanager.hpp"

namespace mugg {
    namespace binds {
        static const char* Texture2DName = "Texture2D";

        mugg::graphics::Texture2D* checkTexture2D(lua_State* L, int n) {
            return *(mugg::graphics::Texture2D**)luaL_checkudata(L, n, Texture2DName);
        }

        int texture2DDeconstructor(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);


            mugg::core::ContentManager::GetInstance().DeleteTexture2D(texture->GetIndex(), texture->GetID());

            return 0;
        }
        
        int texture2DGetFilepath(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushstring(L, texture->GetFilepath().c_str());

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
