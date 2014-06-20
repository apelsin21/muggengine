#ifndef SHADERBINDS_HPP
#define SHADERBINDS_HPP

#include <iostream>
#include <lua.hpp>

#include "shader.hpp"
#include "graphicsdefs.hpp"

namespace mugg {
    namespace binds {
        static const char* ShaderPrivateName = "mugg_Shader";
        static const char* ShaderPublicName = "Shader";

        mugg::graphics::Shader* checkShader(lua_State* L, int n) {
            return *(mugg::graphics::Shader**)luaL_checkudata(L, n, ShaderPrivateName);
        }

        int shaderConstructor(lua_State* L) {
            mugg::graphics::Shader** shader = (mugg::graphics::Shader**)lua_newuserdata(L, sizeof(mugg::graphics::Shader*));
            
            mugg::graphics::ShaderType type = (mugg::graphics::ShaderType)(luaL_checkoption(L, 1, NULL, mugg::graphics::ShaderTypeString));

            const char* filepath = luaL_checkstring(L, 2);

            *shader = new mugg::graphics::Shader(type, filepath);
            
            luaL_getmetatable(L, ShaderPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int shaderDeconstructor(lua_State* L) {
            mugg::graphics::Shader* shader = checkShader(L, 1);

            delete shader;

            return 0;
        }

        luaL_Reg shaderFuncs[] = {
            {"new", shaderConstructor},

            {"__gc", shaderDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
