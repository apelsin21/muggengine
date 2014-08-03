#ifndef KEYBOARDBINDS_HPP
#define KEYBOARDBINDS_HPP

#include <lua.hpp>

#include "keydefs.hpp"
#include "keyboard.hpp"

namespace mugg {
    namespace binds {
        static const char* KeyboardName = "Keyboard";

        mugg::core::Keyboard* checkKeyboard(lua_State* L, int n) {
            return *(mugg::core::Keyboard**)luaL_checkudata(L, n, KeyboardName);
        }

        int keyboardConstructor(lua_State* L) {
            mugg::core::Keyboard** keyboard = (mugg::core::Keyboard**)lua_newuserdata(L, sizeof(mugg::core::Keyboard*));
            *keyboard = new mugg::core::Keyboard();

            luaL_getmetatable(L, KeyboardName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int keyboardDeconstructor(lua_State* L) {
            mugg::core::Keyboard* keyboard = checkKeyboard(L, 1);

            delete keyboard;

            return 0;
        }

        int keyboardIsKeyDown(lua_State* L) {
            mugg::core::Keyboard* keyboard = checkKeyboard(L, 1);

            lua_pushboolean(L, keyboard->IsKeyDown(luaL_checkstring(L, 2)));
            
            return 1;
        }
        int keyboardIsKeyUp(lua_State* L) {
            mugg::core::Keyboard* keyboard = checkKeyboard(L, 1);

            //mugg::core::Key key = (mugg::core::Key)luaL_checkoption(L, 2, NULL, mugg::core::KeyString);

            lua_pushboolean(L, keyboard->IsKeyUp(luaL_checkstring(L, 2)));
            
            return 1;
        }
        
        luaL_Reg keyboardFuncs[] = {
            {"new", keyboardConstructor},

            {"is_key_down", keyboardIsKeyDown},
            {"is_key_up", keyboardIsKeyUp},

            {"__gc", keyboardDeconstructor},
            {NULL, NULL},
        };
    }
}

#endif
