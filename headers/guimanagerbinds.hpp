#ifndef GUIMANAGERBINDS_HPP
#define GUIMANAGERBINDS_HPP

#include <lua.hpp>

#include "texture2dbinds.hpp"
#include "guimanager.hpp"

namespace mugg {
    namespace binds {
        static const char* GUIManagerName = "GUIManager";

        mugg::gui::GUIManager* checkGUIManager(lua_State* L, int n) {
            return *(mugg::gui::GUIManager**)luaL_checkudata(L, n, GUIManagerName);
        }

        int guiManagerConstructor(lua_State* L) {
            mugg::gui::GUIManager** guiMgr = (mugg::gui::GUIManager**)lua_newuserdata(L, sizeof(mugg::gui::GUIManager*));
            *guiMgr = new mugg::gui::GUIManager();

            luaL_getmetatable(L, GUIManagerName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int guiManagerDeconstructor(lua_State* L) {
            mugg::gui::GUIManager* guiMgr = checkGUIManager(L, 1);

            delete guiMgr;

            return 0;
        }

        int guiManagerAddTexture(lua_State* L) {
            mugg::gui::GUIManager* guiMgr = checkGUIManager(L, 1);
            mugg::graphics::Texture2D* texture = checkTexture2D(L, 2);

            guiMgr->AddTexture2D(texture->GetID());

            return 0;
        }

        int guiManagerRender(lua_State* L) {
            mugg::gui::GUIManager* guiMgr = checkGUIManager(L, 1);

            guiMgr->Render();

            return 0;
        }

        luaL_Reg guiManagerFuncs[] = {
            {"new", guiManagerConstructor},

            {"add_texture", guiManagerAddTexture},
            {"render", guiManagerRender},

            {"__gc", guiManagerDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
