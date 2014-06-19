#ifndef WINDOWBINDS_HPP
#define WINDOWBINDS_HPP

#include "window.hpp"

#include <lua.hpp>
#include <glm/glm.hpp>

namespace mugg {
    namespace binds {
        static const char* WindowPrivateName = "mugg_Window";
        static const char* WindowPublicName = "Window";

        mugg::Window* window = new mugg::Window();

        mugg::Window* checkWindow(lua_State* L, int n) {
            return *(mugg::Window**)luaL_checkudata(L, n, WindowPrivateName);
        }

        int windowConstructor(lua_State* L) {
            double x = luaL_checknumber(L, 1);
            double y = luaL_checknumber(L, 2);
            const char* title = luaL_checkstring(L, 3);

            mugg::Window** window = (Window**)lua_newuserdata(L, sizeof(mugg::Window*));
            *window = new mugg::Window(glm::vec2(x, y), glm::vec2(0, 0), title);

            luaL_getmetatable(L, WindowPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int windowDeconstructor(lua_State* L) {
            delete window;

            return 0;
        }

        int windowCreate(lua_State* L) {
            int resX = luaL_checknumber(L, 1);
            int resY = luaL_checknumber(L, 2);
            int posX = luaL_checknumber(L, 3);
            int posY = luaL_checknumber(L, 4);
            const char* title = luaL_checkstring(L, 5);
            
            bool fullscreen;

            if(lua_isboolean(L, 6)) {
                fullscreen = lua_toboolean(L, 6);
            } else {
                luaL_error(L, "Argument to set_fullscreen wasn't a boolean\n");
            }
            
            window->Create(glm::vec2(resX, resY), glm::vec2(posX, posY), title, fullscreen);

            return 0;
        }

        int windowSetPosition(lua_State* L) {
            double x = luaL_checknumber(L, 1);
            double y = luaL_checknumber(L, 2);

            window->SetPosition(glm::vec2(x, y));

            return 0;
        }
        int windowGetPositionX(lua_State* L) {
            lua_pushnumber(L, window->GetPosition().x);
            return 1;
        }
        int windowGetPositionY(lua_State* L) {
            lua_pushnumber(L, window->GetPosition().y);
            return 1;
        }

        int windowSetResolution(lua_State* L) {
            double x = luaL_checknumber(L, 1);
            double y = luaL_checknumber(L, 2);

            window->SetResolution(glm::vec2(x, y));

            return 0;
        }
        int windowGetResolutionX(lua_State* L) {
            lua_pushnumber(L, window->GetResolution().x);
            return 1;
        }
        int windowGetResolutionY(lua_State* L) {
            lua_pushnumber(L, window->GetResolution().y);
            return 1;
        }

        int windowSetFullscreen(lua_State* L) {
            bool arg;

            if(lua_isboolean(L, 1)) {
                arg = lua_toboolean(L, 1);
            } else {
                luaL_error(L, "Argument to set_fullscreen wasn't a boolean\n");
            }

            window->SetFullscreen(arg);
            return 0;
        }
        int windowGetFullscreen(lua_State* L) {
            lua_pushboolean(L, window->GetFullscreen());
            return 1;
        }

        int windowIsOpen(lua_State* L) {
            lua_pushboolean(L, window->IsOpen());
            return 1;
        }
       
        int windowClose(lua_State* L) {
            window->Close();
            return 0;
        }

        int windowSetVsync(lua_State* L) {
            bool arg;

            if(lua_isboolean(L, 1)) {
                arg = lua_toboolean(L, 1);
            } else {
                luaL_error(L, "Argument to function set_vsync() wasn't a boolean");
            }

            window->SetVsync(arg);
            return 0;
        }
        int windowGetVsync(lua_State* L) {
            lua_pushboolean(L, window->GetVsync());
            return 1;
        }

        int windowSetTitle(lua_State* L) {
            const char* arg = luaL_checkstring(L, 1);

            window->SetTitle(arg);

            return 0;
        }
        int windowGetTitle(lua_State* L) {
            lua_pushstring(L, window->GetTitle());
            return 1;
        }

        int windowIsFocused(lua_State *L) {
            lua_pushboolean(L, window->IsFocused());
            return 1;
        }

        int windowSwapBuffers(lua_State* L) {
            window->SwapBuffers();
            return 0;
        }

        int windowSetActive(lua_State* L) {
            bool arg;

            if(lua_isboolean(L, 1)) {
                arg = lua_toboolean(L, 1);
            } else {
                luaL_error(L, "Argument to function set_active() wasn't a boolean");
            }

            window->SetActive(arg);
            return 0;
        }
        int windowGetActive(lua_State* L) {
            lua_pushboolean(L, window->GetActive());
            return 1;
        }

        luaL_Reg windowFuncs[] = {
            {"create", windowCreate},

            {"set_position", windowSetPosition},
            {"get_position_x", windowGetPositionX},
            {"get_position_y", windowGetPositionY},

            {"set_resolution", windowSetResolution},
            {"get_resolution_x", windowGetResolutionX},
            {"get_resolution_y", windowGetResolutionY},

            {"set_fullscreen", windowSetFullscreen},
            {"get_fullscreen", windowGetFullscreen},

            {"set_vsync", windowSetVsync},
            {"get_vsync", windowGetVsync},

            {"set_active", windowSetActive},
            {"get_active", windowGetActive},

            {"set_title", windowSetTitle},
            {"get_title", windowGetTitle},

            {"is_open", windowIsOpen},
            {"close", windowClose},
    
            {"is_focused", windowIsFocused},

            {"swap_buffers", windowSwapBuffers},

            {"__gc", windowDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
