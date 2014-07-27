#ifndef SHADERPROGRAMBINDS_HPP
#define SHADERPROGRAMBINDS_HPP

#include <lua.hpp>
#include <memory>

#include "shaderbinds.hpp"
#include "contentmanager.hpp"
#include "shaderprogram.hpp"

namespace mugg {
    namespace binds {
        static const char* ShaderProgramName = "ShaderProgram";

        mugg::graphics::ShaderProgram* checkShaderProgram(lua_State* L, int n) {
            return *(mugg::graphics::ShaderProgram**)luaL_checkudata(L, n, ShaderProgramName);
        }

        int shaderProgramDeconstructor(lua_State* L) {

            std::cout << "shaderProgramDeconstructor\n";

            return 0;
        }

        int shaderProgramAddShader(lua_State* L) {
            mugg::graphics::ShaderProgram* program = checkShaderProgram(L, 1);

            mugg::graphics::Shader* shader = checkShader(L, 2);

            program->AddShader(shader->GetID());

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
            {"add", shaderProgramAddShader},
            {"link", shaderProgramLink},
            
            {"get_number_of_attached_shaders", shaderProgramGetNumberOfAttachedShaders},

            {"__gc", shaderProgramDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
