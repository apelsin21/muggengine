#ifndef SHADERPROGRAMBINDS_HPP
#define SHADERPROGRAMBINDS_HPP

#include <lua.hpp>

#include "shaderprogram.hpp"

namespace mugg {
    namespace binds {
        static const char* ShaderProgramPrivateName = "mugg_ShaderProgram";
        static const char* ShaderProgramPublicName = "ShaderProgram";

        mugg::core::ShaderProgram* checkShaderProgram(lua_State* L, int n) {
            return *(mugg::core::ShaderProgram**)luaL_checkudata(L, n, ShaderProgramPrivateName);
        }

        int shaderProgramConstructor(lua_State* L) {
            mugg::core::ShaderProgram** program = (mugg::core::ShaderProgram**)lua_newuserdata(L, sizeof(mugg::core::ShaderProgram*));

            const char* vsFilepath = luaL_checkstring(L, 1);
            const char* fsFilepath = luaL_checkstring(L, 2);

            *program = new mugg::core::ShaderProgram(vsFilepath, fsFilepath);

            luaL_getmetatable(L, ShaderProgramPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int shaderProgramDestructor(lua_State* L) {
            mugg::core::ShaderProgram* program = checkShaderProgram(L, 1);

            delete program;

            return 0;
        }

        int shaderProgramLink(lua_State* L) {
            mugg::core::ShaderProgram* program = checkShaderProgram(L, 1);

            lua_pushboolean(L, program->Link());

            return 1;
        }

        luaL_Reg shaderProgramFuncs[] = {
            {"new", shaderProgramConstructor},

            {"link", shaderProgramLink},
            
            {"__gc", shaderProgramDestructor},
            {NULL, NULL}
        };
    }
}

#endif
