#include <string>
#include <iostream>

#include <lua.hpp>
#include <glm/glm.hpp>
#include <SFML/System.hpp>

#include "scriptsystem.hpp"

#include "window.hpp"
#include "windowbinds.hpp"
#include "inputhandler.hpp"
#include "inputhandlerbinds.hpp"
#include "defs.hpp"

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

int main() {
    mugg::ScriptSystem system(true);

    system.RegisterMetatable(mugg::binds::windowFuncs, "mugg_Window", "Window");
    system.RegisterMetatable(mugg::binds::inputHandlerFuncs, "mugg_InputHandler", "InputHandler");

    mugg::input::InputHandler input;
    mugg::Window window(glm::vec2(1, 1), glm::vec2(1024, 1), "bajskorv");

    while(!input.IsKeyDown("Escape")) {
    }

	system.DoFile("main.lua");

    return 0;
}
