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

        int windowOpen(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            int width = luaL_checknumber(L, 2);
            int height = luaL_checknumber(L, 3);
            std::string title = luaL_checkstring(L, 4);
            
            window->Open(width, height, title);

            return 0;
        }

        int windowSetPosition(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            int x = luaL_checknumber(L, 2);
            int y = luaL_checknumber(L, 3);

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
        int windowSetWidth(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            int width = (int)luaL_checknumber(L, 2);

            window->SetWidth(width);

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
        int windowSetHeight(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            int height = (int)luaL_checknumber(L, 2);

            window->SetHeight(height);

            return 0;
        }

        int windowSetFullscreen(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            window->SetFullscreen();
            return 0;
        }
        int windowSetBorderlessFullscreen(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            window->SetBorderlessFullscreen();

            return 0;
        }
        int windowSetWindowed(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            window->SetWindowed();

            return 0;
        }
        int windowIsFullscreen(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushboolean(L, window->IsFullscreen());
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

            const char* title = luaL_checkstring(L, 2);

            window->SetTitle(title);

            return 0;
        }
        int windowGetTitle(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            lua_pushstring(L, window->GetTitle().c_str());
            return 1;
        }

        int windowSetClipboardText(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            std::string arg = luaL_checkstring(L, 2);

            window->SetClipboardText(arg);

            return 0;
        }
        int windowGetClipboardText(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushstring(L, window->GetClipboardText().c_str());

            return 1;
        }
        int windowHasClipboardText(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushboolean(L, window->HasClipboardText());

            return 1;
        }

        int windowHasFocus(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);

            lua_pushboolean(L, window->HasFocus());

            return 1;
        }

        int windowSwapBuffers(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            window->SwapBuffers();
            return 0;
        }

        int windowShowCursor(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            window->ShowCursor();
            return 0;
        }
        int windowHideCursor(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            window->HideCursor();
            return 0;
        }
        int windowIsCursorHidden(lua_State* L) {
            mugg::core::Window* window = checkWindow(L, 1);
            
            lua_pushboolean(L, window->IsCursorHidden());

            return 1;
        }

        luaL_Reg windowFuncs[] = {
            {"open", windowOpen},
            {"close", windowClose},
            {"is_open", windowIsOpen},

            {"show_cursor", windowShowCursor},
            {"hide_cursor", windowHideCursor},
            {"is_cursor_hidden", windowIsCursorHidden},

            {"set_position", windowSetPosition},
            {"get_position_x", windowGetPositionX},
            {"get_position_y", windowGetPositionY},

            {"set_resolution", windowSetResolution},
            {"set_width", windowSetWidth},
            {"get_width", windowGetWidth},
            {"get_height", windowGetHeight},
            {"set_height", windowSetHeight},

            {"set_fullscreen", windowSetFullscreen},
            {"set_borderless_fullscreen", windowSetBorderlessFullscreen},
            {"set_windowed", windowSetWindowed},
            {"is_fullscreen", windowIsFullscreen},

            {"set_swap_interval", windowSetSwapInterval},
            {"get_swap_interval", windowGetSwapInterval},

            {"set_title", windowSetTitle},
            {"get_title", windowGetTitle},

            {"get_clipboard_text", windowGetClipboardText},
            {"set_clipboard_text", windowSetClipboardText},
            {"has_clipboard_text", windowHasClipboardText},

            {"swap_buffers", windowSwapBuffers},
            {"has_focus", windowHasFocus},
            
            {NULL, NULL}
        };
    }
}

#endif
