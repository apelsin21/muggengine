#ifndef RENDERERBINDS_HPP
#define RENDERERBINDS_HPP

#include <lua.hpp>

#include <glm/glm.hpp>

#include "renderer.hpp"

#include "colorbinds.hpp"
#include "shaderprogrambinds.hpp"

#include <iostream> 

namespace mugg {
    namespace binds {
        static const char* RendererPrivateName = "mugg_Renderer";
        static const char* RendererPublicName = "Renderer";

        mugg::graphics::Renderer* renderer = new mugg::graphics::Renderer();
        
        mugg::graphics::Renderer* checkRenderer(lua_State* L, int n) {
            return *(mugg::graphics::Renderer**)luaL_checkudata(L, n, RendererPrivateName);
        }

        int rendererConstructor(lua_State* L) {
            mugg::graphics::Renderer** renderer = (mugg::graphics::Renderer**)lua_newuserdata(L, sizeof(mugg::graphics::Renderer*));
            *renderer = new mugg::graphics::Renderer();

            luaL_getmetatable(L, RendererPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int rendererDeconstructor(lua_State* L) {
            delete renderer;

            return 0;
        }

        int rendererSetBackgroundColor(lua_State* L) {
            renderer->SetBackgroundColor(*checkColor(L, 1));

            return 0;
        }

        int rendererGetBackgroundColor(lua_State* L) {
            mugg::graphics::Color** color = (mugg::graphics::Color**)lua_newuserdata(L, sizeof(mugg::graphics::Color*));
            *color = new mugg::graphics::Color(renderer->GetBackgroundColor().r,
                                              renderer->GetBackgroundColor().g,
                                              renderer->GetBackgroundColor().b,
                                              renderer->GetBackgroundColor().a);
            luaL_getmetatable(L, ColorPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int rendererAddShaderProgram(lua_State* L) {
            mugg::graphics::ShaderProgram* shaderProgram = checkShaderProgram(L, 1);
        
            renderer->AddShaderProgram(*shaderProgram);

            return 0;
        }

        int rendererInitialize(lua_State* L) {
            renderer->Initialize();

            return 0;
        }

        int rendererBeginRender(lua_State* L) {
            int resX = luaL_checknumber(L, 1);
            int resY = luaL_checknumber(L, 2);

            renderer->BeginRender(glm::vec2(resX, resY));

            return 0;
        }

        int rendererEndRender(lua_State* L) {
            renderer->EndRender();

            return 0;
        }

        luaL_Reg rendererFuncs[] = {
            {"set_background_color", rendererSetBackgroundColor},
            {"get_background_color", rendererGetBackgroundColor},

            {"add_shader_program", rendererAddShaderProgram},

            {"initialize", rendererInitialize},

            {"begin_render", rendererBeginRender},
            {"end_render", rendererEndRender},

            {"__gc", rendererDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
