#ifndef DEVICEBINDS_HPP
#define DEVICEBINDS_HPP

#include <lua.hpp>

#include "device.hpp"
#include "guimanagerbinds.hpp"
#include "windowbinds.hpp"
#include "rendererbinds.hpp"
#include "contentmanagerbinds.hpp"

namespace mugg {
    namespace binds {
        static const char* DeviceName = "Device";

        mugg::core::Device* checkDevice(lua_State* L, int n) {
            return *(mugg::core::Device**)luaL_checkudata(L, n, DeviceName);
        }

        int deviceConstructor(lua_State* L) {
            mugg::core::Device** device = (mugg::core::Device**)lua_newuserdata(L, sizeof(mugg::core::Device*));
            *device = new mugg::core::Device();

            luaL_getmetatable(L, DeviceName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int deviceDeconstructor(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);

            delete device;

            return 0;
        }

        int deviceGetGUIManager(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);

            mugg::gui::GUIManager** mgr = (mugg::gui::GUIManager**)lua_newuserdata(L, sizeof(mugg::gui::GUIManager*));
            *mgr = device->GetGUIManager();

            luaL_getmetatable(L, GUIManagerName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int deviceGetContentManager(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);
            
            mugg::core::ContentManager** mgr = (mugg::core::ContentManager**)lua_newuserdata(L, sizeof(mugg::core::ContentManager*));
            *mgr = device->GetContentManager();

            luaL_getmetatable(L, ContentManagerName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int deviceGetWindow(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);

            mugg::core::Window** window = (mugg::core::Window**)lua_newuserdata(L, sizeof(mugg::core::Window*));
            *window = device->GetWindow();

            luaL_getmetatable(L, WindowName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int deviceGetRenderer(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);

            mugg::graphics::Renderer** renderer = (mugg::graphics::Renderer**)lua_newuserdata(L, sizeof(mugg::graphics::Renderer*));
            *renderer = device->GetRenderer();

            luaL_getmetatable(L, RendererName);
            lua_setmetatable(L, -2);

            return 1;
        }

        luaL_Reg deviceFuncs[] = {
            {"new", deviceConstructor},

            {"get_gui_manager", deviceGetGUIManager},
            {"get_content_manager", deviceGetContentManager},
            {"get_window", deviceGetWindow},
            {"get_renderer", deviceGetRenderer},

            {"__gc", deviceDeconstructor},
            {NULL, NULL},
        };
    }
}

#endif
