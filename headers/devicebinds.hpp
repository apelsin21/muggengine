#ifndef DEVICEBINDS_HPP
#define DEVICEBINDS_HPP

#include <lua.hpp>

#include "device.hpp"
#include "guimanagerbinds.hpp"
#include "windowbinds.hpp"
#include "rendererbinds.hpp"
#include "contentmanagerbinds.hpp"
#include "scenemanagerbinds.hpp"

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

        int deviceCreateGUIManager(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);

            mugg::gui::GUIManager** mgr = (mugg::gui::GUIManager**)lua_newuserdata(L, sizeof(mugg::gui::GUIManager*));
            *mgr = device->CreateGUIManager();

            luaL_getmetatable(L, GUIManagerName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int deviceCreateContentManager(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);
            
            mugg::core::ContentManager** mgr = (mugg::core::ContentManager**)lua_newuserdata(L, sizeof(mugg::core::ContentManager*));
            *mgr = device->CreateContentManager();

            luaL_getmetatable(L, ContentManagerName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int deviceCreateWindow(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);

            mugg::core::Window** window = (mugg::core::Window**)lua_newuserdata(L, sizeof(mugg::core::Window*));
            *window = device->CreateWindow();

            luaL_getmetatable(L, WindowName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int deviceCreateRenderer(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);

            mugg::graphics::Renderer** renderer = (mugg::graphics::Renderer**)lua_newuserdata(L, sizeof(mugg::graphics::Renderer*));
            *renderer = device->CreateRenderer();

            luaL_getmetatable(L, RendererName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int deviceCreateSceneManager(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);

            mugg::scene::SceneManager** mgr = (mugg::scene::SceneManager**)lua_newuserdata(L, sizeof(mugg::scene::SceneManager*));
            *mgr = device->CreateSceneManager();

            luaL_getmetatable(L, SceneManagerName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int deviceRender(lua_State* L) {
            mugg::core::Device* device = checkDevice(L, 1);

            device->Render();

            return 0;
        }

        luaL_Reg deviceFuncs[] = {
            {"new", deviceConstructor},

            {"create_gui_manager", deviceCreateGUIManager},
            {"create_content_manager", deviceCreateContentManager},
            {"create_window", deviceCreateWindow},
            {"create_renderer", deviceCreateRenderer},
            {"create_scene_manager", deviceCreateSceneManager},

            {"render", deviceRender},

            {"__gc", deviceDeconstructor},
            {NULL, NULL},
        };
    }
}

#endif
