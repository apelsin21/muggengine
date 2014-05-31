#ifndef INPUTHANDLERBINDS_HPP
#define INPUTHANDLERBINDS_HPP

#include <lua.hpp>

#include "defs.hpp"
#include "inputhandler.hpp"

namespace mugg {
    namespace binds {
        mugg::input::InputHandler* checkInputHandler(lua_State* L, int n) {
            return *(mugg::input::InputHandler**)luaL_checkudata(L, n, "mugg_InputHandler");
        }

        int inputHandlerConstructor(lua_State *L) {
            mugg::input::InputHandler** input = 
                                        (mugg::input::InputHandler**)lua_newuserdata(L, sizeof(mugg::input::InputHandler*));
            
            *input = new mugg::input::InputHandler;

            luaL_getmetatable(L, "mugg_InputHandler");
            lua_setmetatable(L, -2);

            return 1;
        }

        int inputHandlerDeconstructor(lua_State* L) {
            mugg::input::InputHandler* input = checkInputHandler(L, 1);
            delete input;
            
            return 0;
        }

        int inputHandlerIsKeyDown(lua_State* L) {
            mugg::input::InputHandler* input = checkInputHandler(L, 1);

            const char* arg = luaL_checkstring(L, 2);
            lua_pushboolean(L, input->IsKeyDown(arg));

            return 1;
        }

        luaL_Reg inputHandlerFuncs[] = {
            {"new", inputHandlerConstructor},
            
            {"is_key_down", inputHandlerIsKeyDown},

            {"__gc", inputHandlerDeconstructor},
            {NULL, NULL}
        };
    }
}

#endif
