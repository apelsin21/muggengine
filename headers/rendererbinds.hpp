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
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            delete renderer;

            return 0;
        }

        int rendererSetBackgroundColor(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            renderer->SetBackgroundColor(*checkColor(L, 2));

            return 0;
        }

        int rendererGetBackgroundColor(lua_State* L) {
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

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
            mugg::graphics::Renderer* renderer = checkRenderer(L, 1);

            mugg::graphics::ShaderProgram* shaderProgram = checkShaderProgram(L, 2);
        
            renderer->AddShaderProgram(*shaderProgram);

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

            {"add_shader_program", rendererAddShaderProgram},

            {"initialize", rendererInitialize},

            {"draw", rendererDraw},

            {"__gc", rendererDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
