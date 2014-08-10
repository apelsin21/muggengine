#ifndef vec4BINDS_HPP
#define vec4BINDS_HPP

#include <lua.hpp>
#include <glm/glm.hpp>

namespace mugg {
    namespace binds {
        static const char* Vec4Name = "Vector4D";

        glm::vec4* checkvec4(lua_State* L, int n) {
            return *(glm::vec4**)luaL_checkudata(L, n, Vec4Name);
        }

        int vec4Constructor(lua_State* L) {
            glm::vec4** vec = (glm::vec4**)lua_newuserdata(L, sizeof(glm::vec4*));
            *vec = new glm::vec4();

            luaL_getmetatable(L, Vec4Name);
            lua_setmetatable(L, -2);

            return 1;
        }
        int vec4Deconstructor(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            delete vec;

            return 0;
        }

        int vec4SetX(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            vec->x = luaL_checknumber(L, 2);

            return 0;
        }
        int vec4SetY(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            vec->y = luaL_checknumber(L, 2);

            return 0;
        }
        int vec4SetZ(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            vec->z = luaL_checknumber(L, 2);

            return 0;
        }
        int vec4SetW(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            vec->w = luaL_checknumber(L, 2);

            return 0;
        }
        int vec4SetXYZW(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            vec->x = luaL_checknumber(L, 2);
            vec->y = luaL_checknumber(L, 3);
            vec->z = luaL_checknumber(L, 4);
            vec->w = luaL_checknumber(L, 5);

            return 0;
        }

        int vec4GetX(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            lua_pushnumber(L, vec->x);

            return 1;
        }
        int vec4GetY(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            lua_pushnumber(L, vec->y);

            return 1;
        }
        int vec4GetZ(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            lua_pushnumber(L, vec->z);

            return 1;
        }
        int vec4GetW(lua_State* L) {
            glm::vec4* vec = checkvec4(L, 1);

            lua_pushnumber(L, vec->w);

            return 1;
        }

        luaL_Reg vec4Funcs[] = {
            {"new", vec4Constructor},

            {"set_x", vec4SetX},
            {"set_y", vec4SetY},
            {"set_z", vec4SetZ},
            {"set_w", vec4SetW},
            {"set_xyzw", vec4SetXYZW},

            {"get_x", vec4GetX},
            {"get_y", vec4GetY},
            {"get_z", vec4GetZ},
            {"get_w", vec4GetW},

            {"__gc", vec4Deconstructor},
            {NULL, NULL}
        };
    }
}

#endif
