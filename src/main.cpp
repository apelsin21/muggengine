#include <string>
#include <vector>
#include <ctime>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "filehandler.hpp"
#include "log.hpp"
#include "file.hpp"
#include "shader.hpp"
#include "defs.hpp"
#include "window.hpp"
#include "shaderprogram.hpp"
#include "engine.hpp"

#include <assert.h>
#include <lua.hpp>

void dumpStack(lua_State* L);

class Person {
    private:
        int age;
    public:
        Person(int age) {
            this->age = age;
        }
        ~Person() {
        }

        void SetAge(int age) {
            this->age = age;
        }
        int GetAge() {
            return this->age;
        }
};

Person* checkPerson(lua_State* L, int n) {
    return *(Person**)luaL_checkudata(L, n, "lua_Person");
}

int personConstructor(lua_State* L) {
    int arg = luaL_checknumber(L, 1);

    Person** person = (Person**)lua_newuserdata(L, sizeof(Person*));
    *person = new Person(arg);

    luaL_getmetatable(L, "lua_Person");
    lua_setmetatable(L, -2);

    return 1;
}

int personSetAge(lua_State* L) {
    Person* person = checkPerson(L, 1);
    int arg = luaL_checknumber(L, 2);
    person->SetAge(arg);

    return 0;
}

int personGetAge(lua_State* L) {
    Person* person = checkPerson(L, 1);
    lua_pushnumber(L, person->GetAge());
    return 1;
}

int personDeconstructor(lua_State* L) {
    Person* person = checkPerson(L, 1);
    delete person;
    
    return 0;
}

luaL_Reg personFuncs[] = {
    {"new", personConstructor},
    {"set_age", personSetAge},
    {"get_age", personGetAge},
    {"__gc", personDeconstructor},
    {NULL, NULL}
};

void registerPerson(lua_State* L) {
    luaL_newmetatable(L, "lua_Person");
    luaL_setfuncs(L, personFuncs, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    lua_setglobal(L, "Person");
}

void dumpStack(lua_State* L) {
    int top = lua_gettop(L);
    for(int i = 0; i <= top; i++) {
        std::cout << "At index " << i << " type "<< lua_typename(L, lua_type(L, i)) << std::endl;
    }
}

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    registerPerson(L);

    
    int error = luaL_dofile(L, "main.lua");
    if(error) {
        std::cout << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    lua_close(L);

	return 0;
}
