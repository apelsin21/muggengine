#ifndef GUIMANAGERBINDS_HPP
#define GUIMANAGERBINDS_HPP

#include <lua.hpp>

#include "spritebinds.hpp"
#include "guimanager.hpp"

namespace mugg {
    namespace binds {
        static const char* GUIManagerName = "GUIManager";

        mugg::gui::GUIManager* checkGUIManager(lua_State* L, int n) {
            return *(mugg::gui::GUIManager**)luaL_checkudata(L, n, GUIManagerName);
        }

        int guiManagerCreateSprite(lua_State* L) {
            mugg::gui::GUIManager* mgr = checkGUIManager(L, 1);
            
            mugg::gui::Sprite** sprite = (mugg::gui::Sprite**)lua_newuserdata(L, sizeof(mugg::gui::Sprite*));
            *sprite = mgr->CreateSprite();

            luaL_getmetatable(L, SpriteName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int guiManagerRender(lua_State* L) {
            mugg::gui::GUIManager* mgr = checkGUIManager(L, 1);

            mgr->Render();

            return 0;
        }

        luaL_Reg guiManagerFuncs[] = {
            {"create_sprite", guiManagerCreateSprite},
            {"render", guiManagerRender},

            {NULL, NULL}
        };
    }
}

#endif
