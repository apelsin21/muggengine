#include <string>
#include <iostream>

#include <lua.hpp>

#include "scriptsystem.hpp"

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

void dumpStack(lua_State* L) {
    int top = lua_gettop(L);
    for(int i = 0; i <= top; i++) {
        std::cout << "At index " << i << " type "<< lua_typename(L, lua_type(L, i)) << std::endl;
    }
}

int main() {
    
    mugg::ScriptSystem system(true);
    system.RegisterMetatable(personFuncs, "lua_Person", "Person");

    system.PrintStack();

    int error = luaL_dofile(system.GetState(), "main.lua");
    if(error) {
        std::cout << lua_tostring(system.GetState(), -1) << std::endl;
        lua_pop(system.GetState(), 1);
    }

	return 0;
}
