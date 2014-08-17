#ifndef MOUSEBINDS_HPP
#define MOUSEBINDS_HPP

#include <lua.hpp>

#include "mouse.hpp"
#include "vec2binds.hpp"

namespace mugg {
    namespace binds {
        static const char* MouseName = "Mouse";
    
        mugg::core::Mouse* checkMouse(lua_State* L, int n) {
            return *(mugg::core::Mouse**)luaL_checkudata(L, n, MouseName);
        }

        int mouseConstructor(lua_State* L) {
            mugg::core::Mouse** mouse = (mugg::core::Mouse**)lua_newuserdata(L, sizeof(mugg::core::Mouse*));
            *mouse = new mugg::core::Mouse();

            luaL_getmetatable(L, MouseName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int mouseDeconstructor(lua_State* L) {
            mugg::core::Mouse* mouse = checkMouse(L, 1);

            delete mouse;

            return 0;
        }

        int mouseGetPosition(lua_State* L) {
            mugg::core::Mouse* mouse = checkMouse(L, 1);

            glm::vec2** position = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
            *position = new glm::vec2(mouse->GetPosition());

            luaL_getmetatable(L, Vec2Name);
            lua_setmetatable(L, -2);

            return 1;
        }
        int mouseGetX(lua_State* L) {
            mugg::core::Mouse* mouse = checkMouse(L, 1);

            lua_pushnumber(L, mouse->GetX());

            return 1;
        }
        int mouseGetY(lua_State* L) {
            mugg::core::Mouse* mouse = checkMouse(L, 1);

            lua_pushnumber(L, mouse->GetY());

            return 1;
        }

        int mouseIsLeftButtonDown(lua_State* L) {
            mugg::core::Mouse* mouse = checkMouse(L, 1);

            lua_pushboolean(L, mouse->IsLeftButtonDown());

            return 1;
        }
        int mouseIsMiddleButtonDown(lua_State* L) {
            mugg::core::Mouse* mouse = checkMouse(L, 1);

            lua_pushboolean(L, mouse->IsMiddleButtonDown());

            return 1;
        }
        int mouseIsRightButtonDown(lua_State* L) {
            mugg::core::Mouse* mouse = checkMouse(L, 1);

            lua_pushboolean(L, mouse->IsRightButtonDown());

            return 1;
        }

        luaL_Reg mouseFuncs[] = {
            {"new", mouseConstructor},

            {"get_position", mouseGetPosition},
            {"get_x", mouseGetX},
            {"get_y", mouseGetY},

            {"is_left_button_down", mouseIsLeftButtonDown},
            {"is_middle_button_down", mouseIsMiddleButtonDown},
            {"is_right_button_down", mouseIsRightButtonDown},

            {"__gc", mouseDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
