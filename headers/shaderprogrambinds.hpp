#ifndef SHADERPROGRAMBINDS_HPP
#define SHADERPROGRAMBINDS_HPP

#include <lua.hpp>
#include <memory>

#include "shaderbinds.hpp"

#include "shaderprogram.hpp"

namespace mugg {
    namespace binds {
        static const char* ShaderProgramName = "ShaderProgram";

        mugg::graphics::ShaderProgram* checkShaderProgram(lua_State* L, int n) {
            return *(mugg::graphics::ShaderProgram**)luaL_checkudata(L, n, ShaderProgramName);
        }

        int shaderProgramConstructor(lua_State* L) {
            mugg::graphics::ShaderProgram** program = (mugg::graphics::ShaderProgram**)lua_newuserdata(L, sizeof(mugg::graphics::ShaderProgram*));

            *program = new mugg::graphics::ShaderProgram();

            luaL_getmetatable(L, ShaderProgramName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int shaderProgramDestructor(lua_State* L) {
            mugg::graphics::ShaderProgram* program = checkShaderProgram(L, 1);

            delete program;

            return 0;
        }

        int shaderProgramAddShader(lua_State* L) {
            mugg::graphics::ShaderProgram* program = checkShaderProgram(L, 1);

            std::shared_ptr<mugg::graphics::Shader> shader(checkShader(L, 2));

            program->AddShader(shader);

            return 0;
        }
        
        int shaderProgramGetNumberOfAttachedShaders(lua_State* L) {
            mugg::graphics::ShaderProgram* program = checkShaderProgram(L, 1);

            lua_pushnumber(L, program->GetNumberOfAttachedShaders());

            return 1;
        }

        int shaderProgramLink(lua_State* L) {
            mugg::graphics::ShaderProgram* program = checkShaderProgram(L, 1);

            program->Link();
            
            return 1;
        }

        luaL_Reg shaderProgramFuncs[] = {
            {"new", shaderProgramConstructor},

            {"add", shaderProgramAddShader},
            {"link", shaderProgramLink},
            
            {"get_number_of_attached_shaders", shaderProgramGetNumberOfAttachedShaders},

            {"__gc", shaderProgramDestructor},
            {NULL, NULL}
        };
    }
}

#endif
