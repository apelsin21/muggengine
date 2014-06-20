#ifndef SHADERPROGRAMBINDS_HPP
#define SHADERPROGRAMBINDS_HPP

#include <lua.hpp>

#include "shaderbinds.hpp"

#include "shaderprogram.hpp"

namespace mugg {
    namespace binds {
        static const char* ShaderProgramPrivateName = "mugg_ShaderProgram";
        static const char* ShaderProgramPublicName = "ShaderProgram";

        mugg::graphics::ShaderProgram* checkShaderProgram(lua_State* L, int n) {
            return *(mugg::graphics::ShaderProgram**)luaL_checkudata(L, n, ShaderProgramPrivateName);
        }

        int shaderProgramConstructor(lua_State* L) {
            mugg::graphics::ShaderProgram** program = (mugg::graphics::ShaderProgram**)lua_newuserdata(L, sizeof(mugg::graphics::ShaderProgram*));

            *program = new mugg::graphics::ShaderProgram();

            luaL_getmetatable(L, ShaderProgramPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int shaderProgramAddShader(lua_State* L) {
            mugg::graphics::ShaderProgram* program = checkShaderProgram(L, 1);

            mugg::graphics::Shader* shader = checkShader(L, 2);

            program->AddShader(*shader);

            return 0;
        }

        int shaderProgramAddShaderFromFile(lua_State* L) {
            mugg::graphics::ShaderProgram* program = checkShaderProgram(L, 1);

            mugg::graphics::ShaderType type = (mugg::graphics::ShaderType)luaL_checkoption(L, 2, NULL, mugg::graphics::ShaderTypeString);
            const char* filepath = luaL_checkstring(L, 3);

            program->AddShader(type, filepath);

            return 0;
        }

        int shaderProgramDestructor(lua_State* L) {
            mugg::graphics::ShaderProgram* program = checkShaderProgram(L, 1);

            delete program;

            return 0;
        }

        int shaderProgramLink(lua_State* L) {
            mugg::graphics::ShaderProgram* program = checkShaderProgram(L, 1);

            program->Link();
            
            return 1;
        }

        luaL_Reg shaderProgramFuncs[] = {
            {"new", shaderProgramConstructor},

            {"load_shader", shaderProgramAddShaderFromFile},
            {"add_shader", shaderProgramAddShader},
            {"link", shaderProgramLink},
            
            {"__gc", shaderProgramDestructor},
            {NULL, NULL}
        };
    }
}

#endif
