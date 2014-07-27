#ifndef GUIMANAGERBINDS_HPP
#define GUIMANAGERBINDS_HPP

#include <lua.hpp>

#include "imagebinds.hpp"
#include "guimanager.hpp"

namespace mugg {
    namespace binds {
        static const char* GUIManagerName = "GUIManager";

        mugg::gui::GUIManager* checkGUIManager(lua_State* L, int n) {
            return *(mugg::gui::GUIManager**)luaL_checkudata(L, n, GUIManagerName);
        }

        int guiManagerGetImage(lua_State* L) {
            mugg::gui::GUIManager* mgr = checkGUIManager(L, 1);
            
            mugg::gui::Image** img = (mugg::gui::Image**)lua_newuserdata(L, sizeof(mugg::gui::Image*));
            *img = mgr->GetImage();

            luaL_getmetatable(L, ImageName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int guiManagerRender(lua_State* L) {
            mugg::gui::GUIManager* mgr = checkGUIManager(L, 1);

            mgr->Render();

            return 0;
        }

        luaL_Reg guiManagerFuncs[] = {
            {"get_image", guiManagerGetImage},
            {"render", guiManagerRender},

            {NULL, NULL}
        };
    }
}

#endif
