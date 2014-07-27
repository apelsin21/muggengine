#ifndef WINDOWBINDS_HPP
#define WINDOWBINDS_HPP

#include "window.hpp"

#include <lua.hpp>

namespace mugg {
    namespace binds {
        static const char* WindowName = "Window";

        mugg::core::Window* checkWindow(lua_State* L, int n) {
            return *(mugg::core::Window**)luaL_checkudata(L, n, WindowName);
        }

        int windowDeconstructor(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            delete window;

            return 0;
        }

        int windowOpen(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            int width = luaL_checknumber(L, 2);
            int height = luaL_checknumber(L, 3);
            const char* title = luaL_checkstring(L, 4);
            
            window->Open(width, height, title);

            return 0;
        }

        int windowSetPosition(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            int x = (int)luaL_checknumber(L, 2);
            int y = (int)luaL_checknumber(L, 3);

            window->SetPosition(x, y);

            return 0;
        }
        int windowGetPositionX(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            lua_pushnumber(L, window->GetPositionX());
            return 1;
        }
        int windowGetPositionY(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushnumber(L, window->GetPositionY());
            return 1;
        }

        int windowSetResolution(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            int width = (int)luaL_checknumber(L, 2);
            int height = (int)luaL_checknumber(L, 3);

            window->SetResolution(width, height);

            return 0;
        }
        int windowGetWidth(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushnumber(L, window->GetWidth());
            return 1;
        }
        int windowGetHeight(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushnumber(L, window->GetHeight());
            return 1;
        }

        int windowSetFullscreen(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
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
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushboolean(L, window->GetFullscreen());
            return 1;
        }

        int windowIsOpen(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushboolean(L, window->IsOpen());
            return 1;
        }
       
        int windowClose(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            window->Close();
            return 0;
        }

        int windowSetSwapInterval(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            window->SetSwapInterval((int)luaL_checknumber(L, 2));
            
            return 0;
        }
        int windowGetSwapInterval(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushnumber(L, window->GetSwapInterval());

            return 1;
        }

        int windowSetTitle(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            std::string arg = luaL_checkstring(L, 2);

            window->SetTitle(arg);

            return 0;
        }
        int windowGetTitle(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            lua_pushstring(L, window->GetTitle().c_str());
            return 1;
        }

        int windowIsKeyDown(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            const char* keystring = luaL_checkstring(L, 2);

            bool isPressed = window->IsKeyStringDown(keystring);

            lua_pushboolean(L, isPressed);

            return 1;
        }

        int windowSetClipboard(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            const char* arg = luaL_checkstring(L, 2);

            window->SetClipboard(arg);

            return 0;
        }
        int windowGetClipboard(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushstring(L, window->GetClipboard().c_str());

            return 1;
        }

        int windowIsFocused(lua_State *L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushboolean(L, window->IsFocused());
            return 1;
        }

        int windowSwapBuffers(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            window->SwapBuffers();
            return 0;
        }

        luaL_Reg windowFuncs[] = {
            {"open", windowOpen},

            {"is_key_down", windowIsKeyDown},

            {"set_position", windowSetPosition},
            {"get_position_x", windowGetPositionX},
            {"get_position_y", windowGetPositionY},

            {"set_resolution", windowSetResolution},
            {"get_width", windowGetWidth},
            {"get_height", windowGetHeight},

            {"set_fullscreen", windowSetFullscreen},
            {"get_fullscreen", windowGetFullscreen},

            {"set_swap_interval", windowSetSwapInterval},
            {"get_swap_interval", windowGetSwapInterval},

            {"set_title", windowSetTitle},
            {"get_title", windowGetTitle},

            {"is_open", windowIsOpen},
            {"close", windowClose},
    
            {"get_clipboard", windowGetClipboard},
            {"set_clipboard", windowSetClipboard},

            {"is_focused", windowIsFocused},

            {"swap_buffers", windowSwapBuffers},

            {"__gc", windowDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
