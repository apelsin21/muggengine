#ifndef WINDOWBINDS_HPP
#define WINDOWBINDS_HPP

#include "window.hpp"

#include <lua.hpp>
#include <glm/glm.hpp>

namespace mugg {
    namespace binds {
        mugg::Window* checkWindow(lua_State* L, int n) {
            return *(mugg::Window**)luaL_checkudata(L, n, "mugg_Window");
        }

        int windowConstructor(lua_State* L) {
            double x = luaL_checknumber(L, 1);
            double y = luaL_checknumber(L, 2);
            const char* title = luaL_checkstring(L, 3);

            mugg::Window** window = (Window**)lua_newuserdata(L, sizeof(mugg::Window*));
            *window = new mugg::Window(glm::vec2(x, y), glm::vec2(0, 0), title);

            luaL_getmetatable(L, "mugg_Window");
            lua_setmetatable(L, -2);

            return 1;
        }

        int windowDeconstructor(lua_State* L) {
            mugg::Window* window = checkWindow(L, 1);
            delete window;

            return 0;
        }

        int windowSetPosition(lua_State* L) {
            mugg::Window* window = checkWindow(L, 1);
            
            double x = luaL_checknumber(L, 2);
            double y = luaL_checknumber(L, 3);

            window->SetPosition(glm::vec2(x, y));

            return 0;
        }
        int windowGetPositionX(lua_State* L) {
            mugg::Window* window = checkWindow(L, 1);

            lua_pushnumber(L, window->GetPosition().x);
            return 1;
        }
        int windowGetPositionY(lua_State* L) {
            mugg::Window* window = checkWindow(L, 1);

            lua_pushnumber(L, window->GetPosition().y);
            return 1;
        }

        int windowSetResolution(lua_State* L) {
            mugg::Window* window = checkWindow(L, 1);

            double x = luaL_checknumber(L, 2);
            double y = luaL_checknumber(L, 3);

            window->SetResolution(glm::vec2(x, y));

            return 0;
        }
        int windowGetResolutionX(lua_State* L) {
            mugg::Window* window = checkWindow(L, 1);

            lua_pushnumber(L, window->GetResolution().x);
            return 1;
        }
        int windowGetResolutionY(lua_State* L) {
            mugg::Window* window = checkWindow(L, 1);

            lua_pushnumber(L, window->GetResolution().y);
            return 1;
        }

        int windowSetFullscreen(lua_State* L) {
            mugg::Window* window = checkWindow(L, 1);
    
            bool arg;

            if(lua_isboolean(L, 2)) {
                arg = lua_toboolean(L, 2);
            } else {
                luaL_error(L, "Argument to set_fullscreen wasn't a boolean\n");
            }

            window->SetFullscreen(arg);
            return 0;
        }
        int windowGetFullscreen(lua_State* L) {
            mugg::Window* window = checkWindow(L, 1);

            lua_pushboolean(L, window->GetFullscreen());
            return 1;
        }

        luaL_Reg windowFuncs[] = {
            {"new", windowConstructor},

            {"set_position", windowSetPosition},
            {"get_position_x", windowGetPositionX},
            {"get_position_y", windowGetPositionY},

            {"set_resolution", windowSetResolution},
            {"get_resolution_x", windowGetResolutionX},
            {"get_resolution_y", windowGetResolutionY},

            {"set_fullscreen", windowSetFullscreen},
            {"get_fullscreen", windowGetFullscreen},

            {"__gc", windowDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
