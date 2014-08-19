#ifndef EngineBINDS_HPP
#define EngineBINDS_HPP

#include <lua.hpp>

#include "engine.hpp"
#include "guimanagerbinds.hpp"
#include "windowbinds.hpp"
#include "rendererbinds.hpp"
#include "contentmanagerbinds.hpp"
#include "scenemanagerbinds.hpp"

namespace mugg {
    namespace binds {
        static const char* EngineName = "Engine";

        mugg::core::Engine* checkEngine(lua_State* L, int n) {
            return *(mugg::core::Engine**)luaL_checkudata(L, n, EngineName);
        }

        int engineConstructor(lua_State* L) {
            mugg::core::Engine** engine = (mugg::core::Engine**)lua_newuserdata(L, sizeof(mugg::core::Engine*));
            *engine = new mugg::core::Engine();

            luaL_getmetatable(L, EngineName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int engineDeconstructor(lua_State* L) {
            mugg::core::Engine* engine = checkEngine(L, 1);

            delete engine;

            return 0;
        }

        int engineGetGUIManager(lua_State* L) {
            mugg::core::Engine* engine = checkEngine(L, 1);

            mugg::gui::GUIManager** mgr = (mugg::gui::GUIManager**)lua_newuserdata(L, sizeof(mugg::gui::GUIManager*));
            *mgr = engine->GetGUIManager();

            luaL_getmetatable(L, GUIManagerName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int engineGetContentManager(lua_State* L) {
            mugg::core::Engine* engine = checkEngine(L, 1);
            
            mugg::core::ContentManager** mgr = (mugg::core::ContentManager**)lua_newuserdata(L, sizeof(mugg::core::ContentManager*));
            *mgr = engine->GetContentManager();

            luaL_getmetatable(L, ContentManagerName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int engineGetWindow(lua_State* L) {
            mugg::core::Engine* engine = checkEngine(L, 1);

            mugg::core::Window** window = (mugg::core::Window**)lua_newuserdata(L, sizeof(mugg::core::Window*));
            *window = engine->GetWindow();

            luaL_getmetatable(L, WindowName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int engineGetRenderer(lua_State* L) {
            mugg::core::Engine* engine = checkEngine(L, 1);

            mugg::graphics::Renderer** renderer = (mugg::graphics::Renderer**)lua_newuserdata(L, sizeof(mugg::graphics::Renderer*));
            *renderer = engine->GetRenderer();

            luaL_getmetatable(L, RendererName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int engineGetSceneManager(lua_State* L) {
            mugg::core::Engine* engine = checkEngine(L, 1);

            mugg::scene::SceneManager** mgr = (mugg::scene::SceneManager**)lua_newuserdata(L, sizeof(mugg::scene::SceneManager*));
            *mgr = engine->GetSceneManager();

            luaL_getmetatable(L, SceneManagerName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int engineRender(lua_State* L) {
            mugg::core::Engine* engine = checkEngine(L, 1);

            engine->Render();

            return 0;
        }

        luaL_Reg engineFuncs[] = {
            {"new", engineConstructor},

            {"get_gui_manager",     engineGetGUIManager},
            {"get_content_manager", engineGetContentManager},
            {"get_window",          engineGetWindow},
            {"get_renderer",        engineGetRenderer},
            {"get_scene_manager",   engineGetSceneManager},

            {"render", engineRender},

            {"__gc", engineDeconstructor},
            {NULL, NULL},
        };
    }
}

#endif
