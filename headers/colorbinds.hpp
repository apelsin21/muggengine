#ifndef COLORBINDS_HPP
#define COLORBINDS_HPP

#include <lua.hpp>

#include "color.hpp"

namespace mugg {
    namespace binds {
        static const char* ColorPrivateName = "mugg_Color";
        static const char* ColorPublicName = "Color";

        mugg::graphics::Color* checkColor(lua_State* L, int n) {
            return *(mugg::graphics::Color**)luaL_checkudata(L, n, ColorPrivateName);
        }

        int colorConstructor(lua_State* L) {
            mugg::graphics::Color** color = (mugg::graphics::Color**)lua_newuserdata(L, sizeof(mugg::graphics::Color*));
            *color = new mugg::graphics::Color();

            luaL_getmetatable(L, ColorPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }
        int colorConstructorWithParams(lua_State* L) {
            mugg::graphics::Color** color = (mugg::graphics::Color**)lua_newuserdata(L, sizeof(mugg::graphics::Color*));
            
            float r = luaL_checknumber(L, 1);
            float g = luaL_checknumber(L, 2);
            float b = luaL_checknumber(L, 3);
            float a = luaL_checknumber(L, 4);
            
            *color = new mugg::graphics::Color(r, g, b, a);

            luaL_getmetatable(L, ColorPrivateName);
            lua_setmetatable(L, -2);

            return 1;
        }

        int colorDestructor(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);
            delete color;

            return 0;
        }

        int colorSetColors(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            float r = luaL_checknumber(L, 2);
            float g = luaL_checknumber(L, 3);
            float b = luaL_checknumber(L, 4);
            float a = luaL_checknumber(L, 5);

            color->Set(r, g, b, a);
            return 0;
        }

        int colorGetRed(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            lua_pushnumber(L, color->r);
            return 1;
        }
        int colorSetRed(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            float r = luaL_checknumber(L, 2);
            color->r = r;
            color->Clamp();
            return 0;
        }

        int colorGetGreen(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            lua_pushnumber(L, color->g);
            return 1;
        }
        int colorSetGreen(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            float g = luaL_checknumber(L, 2);
            color->g = g;
            color->Clamp();
            return 0;
        }

        int colorGetBlue(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            lua_pushnumber(L, color->b);
            return 1;
        }
        int colorSetBlue(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            float b = luaL_checknumber(L, 2);
            color->b = b;
            color->Clamp();
            return 0;
        }

        int colorGetAlpha(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            lua_pushnumber(L, color->a);
            return 1;
        }
        int colorSetAlpha(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            float a = luaL_checknumber(L, 2);
            color->a = a;
            color->Clamp();
            return 0;
        }

        int colorClamp(lua_State* L) {
            mugg::graphics::Color* color = checkColor(L, 1);

            color->Clamp();

            return 0;
        }

        luaL_Reg colorFuncs[] = {
            {"new", colorConstructor},
            {"new", colorConstructorWithParams},

            {"set_colors", colorSetColors},

            {"get_red", colorGetRed},
            {"set_red", colorSetRed},

            {"get_green", colorGetGreen},
            {"set_green", colorSetGreen},

            {"get_blue", colorGetBlue},
            {"set_blue", colorSetBlue},

            {"get_alpha", colorGetAlpha},
            {"set_alpha", colorSetAlpha},

            {"clamp", colorClamp},

            {"__gc", colorDestructor},
            {NULL, NULL}
        };
    }
}

#endif
