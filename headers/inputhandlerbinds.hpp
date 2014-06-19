#ifndef INPUTHANDLERBINDS_HPP
#define INPUTHANDLERBINDS_HPP

#include <lua.hpp>

#include "keydefs.hpp"
#include "inputhandler.hpp"

namespace mugg {
    namespace binds {
        static const char* InputHandlerPrivateName = "mugg_InputHandler";
        static const char* InputHandlerPublicName = "InputHandler";

        mugg::input::InputHandler* input = new mugg::input::InputHandler();
        
        mugg::input::InputHandler* checkInputHandler(lua_State* L, int n) {
            return *(mugg::input::InputHandler**)luaL_checkudata(L, n, InputHandlerPrivateName);
        }

        int inputHandlerDeconstructor(lua_State* L) {
            delete input;
            
            return 0;
        }

        int inputHandlerIsKeyDown(lua_State* L) {
            int key = luaL_checkoption(L, 1, NULL, mugg::input::KeyString);
   
            //It's minus one because Lua begins arrays with 1 instead of 0
            bool isPressed = input->IsKeyDown((mugg::input::Key)(key - 1));

            lua_pushboolean(L, isPressed);

            return 1;
        }

        luaL_Reg inputHandlerFuncs[] = {
            {"is_key_down", inputHandlerIsKeyDown},

            {"__gc", inputHandlerDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
