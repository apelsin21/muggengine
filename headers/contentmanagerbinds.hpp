#ifndef CONTENTMANAGERBINDS_HPP
#define CONTENTMANAGERBINDS_HPP

#include "contentmanager.hpp"

#include <lua.hpp>
#include <iostream>
#include <string>
#include <memory>

#include "texture2dbinds.hpp"
#include "shaderbinds.hpp"
#include "shaderprogrambinds.hpp"

namespace mugg {
    namespace binds {
        static const char* ContentManagerName = "ContentManager";
        
        int contentManagerLoadTexture2D(lua_State* L) {
            std::string path = lua_tostring(L, 1);

            mugg::graphics::Texture2D** texture = (mugg::graphics::Texture2D**)lua_newuserdata(L, sizeof(mugg::graphics::Texture2D*));
            *texture = mugg::core::ContentManager::GetInstance().LoadTexture2D(path);

            luaL_getmetatable(L, Texture2DName);
            lua_setmetatable(L, -2);
            
            return 1;
        }

        int contentManagerLoadShader(lua_State* L) {
            mugg::graphics::ShaderType type = (mugg::graphics::ShaderType)luaL_checkoption(L, 1, NULL, mugg::graphics::ShaderTypeString);
            std::string path = lua_tostring(L, 2);

            mugg::graphics::Shader** shader = (mugg::graphics::Shader**)lua_newuserdata(L, sizeof(mugg::graphics::Shader*));
            *shader = mugg::core::ContentManager::GetInstance().LoadShader(type, path);
        
            luaL_getmetatable(L, ShaderName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int contentManagerLoadShaderProgram(lua_State* L) {
            mugg::graphics::ShaderProgram** program = (mugg::graphics::ShaderProgram**)lua_newuserdata(L, sizeof(mugg::graphics::ShaderProgram*));
            *program = mugg::core::ContentManager::GetInstance().LoadShaderProgram();

            luaL_getmetatable(L, ShaderProgramName);
            lua_setmetatable(L, -2);

            return 1;
        }

        luaL_Reg contentManagerFuncs[] = {
            {"load_texture2d", contentManagerLoadTexture2D},
            {"load_shader", contentManagerLoadShader},
            {"load_shaderprogram", contentManagerLoadShaderProgram},

            {NULL, NULL},
        };
    }
}

#endif
