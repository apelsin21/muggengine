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

            if(texture != nullptr) {
                delete texture;
            }

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
        int texture2DGetLoaded(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushboolean(L, texture->IsLoaded());

            return 1;
        }
        int texture2DGetUsesMipMaps(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            lua_pushboolean(L, texture->UsesMipMaps());

            return 1;
        }
    
        int texture2DSetFilter(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            mugg::graphics::TextureFilter minFilter = (mugg::graphics::TextureFilter)luaL_checkoption(L, 2, NULL, mugg::graphics::TextureFilterString);
            mugg::graphics::TextureFilter magFilter = (mugg::graphics::TextureFilter)luaL_checkoption(L, 3, NULL, mugg::graphics::TextureFilterString);
        
            texture->SetFilter(minFilter, magFilter);

            return 0;
        }
        int texture2DGetMinFilter(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            const char* minFilter = mugg::graphics::TextureFilterString[texture->GetMinFilter()];

            lua_pushstring(L, minFilter);

            return 1;
        }
        int texture2DGetMagFilter(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1);

            const char* magFilter = mugg::graphics::TextureFilterString[texture->GetMagFilter()];

            lua_pushstring(L, magFilter);

            return 1;
        }

        int texture2DSetWrap(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1); 
            
            mugg::graphics::TextureWrap uWrap = (mugg::graphics::TextureWrap)luaL_checkoption(L, 2, NULL, mugg::graphics::TextureWrapString);
            mugg::graphics::TextureWrap vWrap = (mugg::graphics::TextureWrap)luaL_checkoption(L, 3, NULL, mugg::graphics::TextureWrapString);
        
            texture->SetWrap(uWrap, vWrap);

            return 0;
        }
        int texture2DGetUWrap(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1); 
            
            const char* uWrap = mugg::graphics::TextureWrapString[texture->GetUWrap()];

            lua_pushstring(L, uWrap);

            return 1;
        }
        int texture2DGetVWrap(lua_State* L) {
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 1); 
        
            const char* vWrap = mugg::graphics::TextureWrapString[texture->GetVWrap()];

            lua_pushstring(L, vWrap);

            return 1;
        }

        luaL_Reg texture2DFuncs[] = {
            {"get_filepath", texture2DGetFilepath},

            {"get_width", texture2DGetWidth},
            {"get_height", texture2DGetHeight},

            {"get_bpp", texture2DGetBPP},
            {"get_colors_used", texture2DGetColorsUsed},

            {"set_filter", texture2DSetFilter},
            {"get_min_filter", texture2DGetMinFilter},
            {"get_mag_filter", texture2DGetMagFilter},

            {"set_wrap", texture2DSetWrap},
            {"get_u_wrap", texture2DGetUWrap},
            {"get_v_wrap", texture2DGetVWrap},

            {"is_loaded", texture2DGetLoaded},
            {"uses_mipmaps", texture2DGetUsesMipMaps},

            {"__gc", texture2DDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
