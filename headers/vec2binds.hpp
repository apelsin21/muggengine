#ifndef VEC2BINDS_HPP
#define VEC2BINDS_HPP

#include <lua.hpp>
#include <glm/glm.hpp>

namespace mugg {
    namespace binds {
        static const char* Vec2Name = "Vector2D";

        glm::vec2* checkVec2(lua_State* L, int n) {
            return *(glm::vec2**)luaL_checkudata(L, n, Vec2Name);
        }

        int vec2Constructor(lua_State* L) {
            glm::vec2** vec = (glm::vec2**)lua_newuserdata(L, sizeof(glm::vec2*));
            *vec = new glm::vec2();

            luaL_getmetatable(L, Vec2Name);
            lua_setmetatable(L, -2);

            return 1;
        }
        int vec2Deconstructor(lua_State* L) {
            glm::vec2* vec = checkVec2(L, 1);

            delete vec;

            return 0;
        }

        int vec2SetX(lua_State* L) {
            glm::vec2* vec = checkVec2(L, 1);

            vec->x = luaL_checknumber(L, 2);

            return 0;
        }
        int vec2SetY(lua_State* L) {
            glm::vec2* vec = checkVec2(L, 1);

            vec->y = luaL_checknumber(L, 2);

            return 0;
        }
        int vec2SetXY(lua_State* L) {
            glm::vec2* vec = checkVec2(L, 1);

            vec->x = luaL_checknumber(L, 2);
            vec->y = luaL_checknumber(L, 3);

            return 0;
        }

        int vec2GetX(lua_State* L) {
            glm::vec2* vec = checkVec2(L, 1);

            lua_pushnumber(L, vec->x);

            return 1;
        }
        int vec2GetY(lua_State* L) {
            glm::vec2* vec = checkVec2(L, 1);

            lua_pushnumber(L, vec->y);

            return 1;
        }

        luaL_Reg vec2Funcs[] = {
            {"new", vec2Constructor},

            {"set_x", vec2SetX},
            {"set_y", vec2SetY},
            {"set_xy", vec2SetXY},

            {"get_x", vec2GetX},
            {"get_y", vec2GetY},

            {"__gc", vec2Deconstructor},
            {NULL, NULL}
        };
    }
}

#endif
