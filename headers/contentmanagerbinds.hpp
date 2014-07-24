#ifndef CONTENTMANAGERBINDS_HPP
#define CONTENTMANAGERBINDS_HPP

#include "contentmanager.hpp"

#include <lua.hpp>
#include <iostream>
#include <string>
#include <memory>

#include "texture2dbinds.hpp"

namespace mugg {
    namespace binds {
        static const char* ContentManagerName = "ContentManager";
        
        int contentManagerLoad(lua_State* L) {
            mugg::core::LoadableType type = (mugg::core::LoadableType)luaL_checkoption(L, 1, NULL, mugg::core::LoadableTypeString);
            const char* path = lua_tostring(L, 2);

            if(type ==mugg::core::LoadableType::Texture2D) {
                    mugg::graphics::Texture2D** texture = (mugg::graphics::Texture2D**)lua_newuserdata(L, sizeof(mugg::graphics::Texture2D*));
                    *texture = mugg::core::ContentManager::GetInstance().LoadTexture2D(path);
                    
                    luaL_getmetatable(L, Texture2DName);
                    lua_setmetatable(L, -2);
                    
                    return 1;
            }
            else if(type == mugg::core::LoadableType::Mesh) {
            }
            else if(type == mugg::core::LoadableType::Shader) {
            }
            
            return 0;
        }

        luaL_Reg contentManagerFuncs[] = {
            {"load", contentManagerLoad},
            
            {NULL, NULL},
        };
    }
}

#endif
