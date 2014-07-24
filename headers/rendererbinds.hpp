#ifndef RENDERERBINDS_HPP
#define RENDERERBINDS_HPP

#include <lua.hpp>

#include <glm/glm.hpp>

#include "renderer.hpp"

#include "colorbinds.hpp"
#include "shaderprogrambinds.hpp"

#include <iostream> 
#include <memory>
#include <algorithm>
#include <utility>

namespace mugg {
    namespace binds {
        static const char* RendererName = "Renderer";

        mugg::graphics::Renderer* checkRenderer(lua_State* L, int n) {
            return *(mugg::graphics::Renderer**)luaL_checkudata(L, n, RendererName);
        }

        int rendererConstructor(lua_State* L) {
            mugg::graphics::Renderer** renderer = (mugg::graphics::Renderer**)lua_newuserdata(L, sizeof(mugg::graphics::Renderer*));
            *renderer = new mugg::graphics::Renderer();

            luaL_getmetatable(L, RendererName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int rendererDeconstructor(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);
        
            delete renderer;

            return 0;
        }

        int rendererSetBackgroundColor(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            mugg::graphics::Color color = *checkColor(L, 2);

            renderer->SetBackgroundColor(color);

            return 0;
        }

        int rendererGetBackgroundColor(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            mugg::graphics::Color* color = new mugg::graphics::Color(renderer->GetBackgroundColor());
            luaL_getmetatable(L, ColorName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int rendererAddShaderProgram(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            std::shared_ptr<mugg::graphics::ShaderProgram> shaderProgram(checkShaderProgram(L, 2));
        
            renderer->AddShaderProgram(shaderProgram);

            return 0;
        }

        int rendererInitialize(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            renderer->Initialize();

            return 0;
        }

        int rendererDraw(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            renderer->Draw();

            return 0;
        }

        luaL_Reg rendererFuncs[] = {
            {"new", rendererConstructor},

            {"set_background_color", rendererSetBackgroundColor},
            {"get_background_color", rendererGetBackgroundColor},

            {"add_shaderprogram", rendererAddShaderProgram},

            {"initialize", rendererInitialize},

            {"draw", rendererDraw},

            {"__gc", rendererDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
