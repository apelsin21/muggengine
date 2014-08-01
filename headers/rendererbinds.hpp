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

        int rendererSetWireframe(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            if(lua_isboolean(L, 2)) {
                renderer->SetWireframe(lua_toboolean(L, 2));
            } else {
                luaL_error(L, "Renderer:set_wireframe expected boolean");
            }

            return 0;
        }
        int rendererGetWireframe(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            lua_pushboolean(L, renderer->GetWireframe());
            
            return 1;
        }

        int rendererAddShaderProgram(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            mugg::graphics::ShaderProgram* shaderProgram = checkShaderProgram(L, 2);
        
            renderer->AddShaderProgram(shaderProgram->GetID());

            return 0;
        }

        int rendererInitialize(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            renderer->Initialize();

            return 0;
        }

        int rendererGetDeltatime(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);
            
            lua_pushnumber(L, renderer->GetDeltatime());

            return 1;
        }
        int rendererGetFrametime(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);
            
            lua_pushnumber(L, renderer->GetFrametime());

            return 1;
        }

        int rendererDraw(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            renderer->Draw();

            return 0;
        }

        luaL_Reg rendererFuncs[] = {
            {"set_background_color", rendererSetBackgroundColor},
            {"get_background_color", rendererGetBackgroundColor},

            {"set_wireframe", rendererSetWireframe},
            {"get_wireframe", rendererGetWireframe},

            {"add_shaderprogram", rendererAddShaderProgram},

            {"initialize", rendererInitialize},

            {"get_deltatime", rendererGetDeltatime},
            {"get_frametime", rendererGetFrametime},

            {"draw", rendererDraw},

            {NULL, NULL}
        };
    }
}

#endif
