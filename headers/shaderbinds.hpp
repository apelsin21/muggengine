#ifndef SHADERBINDS_HPP
#define SHADERBINDS_HPP

#include <iostream>
#include <lua.hpp>

#include "shader.hpp"
#include "graphicsdefs.hpp"

namespace mugg {
    namespace binds {
        static const char* ShaderName = "Shader";

        mugg::graphics::Shader* checkShader(lua_State* L, int n) {
            return *(mugg::graphics::Shader**)luaL_checkudata(L, n, ShaderName);
        }

        int shaderConstructor(lua_State* L) {
            mugg::graphics::Shader** shader = (mugg::graphics::Shader**)lua_newuserdata(L, sizeof(mugg::graphics::Shader*));
            
            *shader = new mugg::graphics::Shader();
            
            luaL_getmetatable(L, ShaderName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int shaderDeconstructor(lua_State* L) {
            mugg::graphics::Shader* shader = checkShader(L, 1);

            delete shader;

            return 0;
        }

        int shaderLoad(lua_State* L) {
            mugg::graphics::Shader* shader = checkShader(L, 1);

            const char* path = luaL_checkstring(L, 2);

            shader->Load(path);

            return 0;
        }

        luaL_Reg shaderFuncs[] = {
            {"new", shaderConstructor},
            
            {"load", shaderLoad},

            {"__gc", shaderDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
