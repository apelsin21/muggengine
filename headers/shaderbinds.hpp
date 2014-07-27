#ifndef SHADERBINDS_HPP
#define SHADERBINDS_HPP

#include <iostream>
#include <lua.hpp>

#include "shader.hpp"
#include "graphicsdefs.hpp"
#include "contentmanager.hpp"

namespace mugg {
    namespace binds {
        static const char* ShaderName = "Shader";

        mugg::graphics::Shader* checkShader(lua_State* L, int n) {
            return *(mugg::graphics::Shader**)luaL_checkudata(L, n, ShaderName);
        }

        int shaderDeconstructor(lua_State* L) {
            std::cout << "shaderDeconstructor\n";

            return 0;
        }

        int shaderGetData(lua_State* L) {
            mugg::graphics::Shader* shader = checkShader(L, 1);

            lua_pushstring(L, shader->GetData().c_str());

            return 1;
        }

        luaL_Reg shaderFuncs[] = {
            {"get_data", shaderGetData},
            
            {"__gc", shaderDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
