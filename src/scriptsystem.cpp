#include "scriptsystem.hpp"

mugg::ScriptSystem::ScriptSystem(bool useStandardLibrary = false) {
    this->state = luaL_newstate();

    this->UseStandardLibrary(useStandardLibrary);
}

mugg::ScriptSystem::ScriptSystem(lua_State* state) {
    this->state = state;
}

mugg::ScriptSystem::~ScriptSystem() {
    lua_close(this->state);
}

void mugg::ScriptSystem::UseStandardLibrary(bool use) {
    this->usesStandardLibrary = use;
    luaL_openlibs(this->state);
}
bool mugg::ScriptSystem::IsUsingStandardLibrary() {
    return this->usesStandardLibrary;
}

void mugg::ScriptSystem::SetState(lua_State* state) {
    this->state = state;
}
lua_State* mugg::ScriptSystem::GetState() {
    return this->state;
}

void mugg::ScriptSystem::RegisterMetatable(luaL_Reg* functions, const char* privateName, const char* globalName) {
    luaL_newmetatable(this->state, privateName);
    luaL_setfuncs(this->state, functions, 0);
    lua_pushvalue(this->state, -1);
    lua_setfield(this->state, -2, "__index");

    lua_setglobal(this->state, globalName);

    this->registredMetatablesPrivateNames.push_back(privateName);
    this->registredMetatablesGlobalNames.push_back(globalName);
}
std::vector<const char*> mugg::ScriptSystem::GetRegistredMetatablesPrivateNames() {
    return this->registredMetatablesPrivateNames;
}
std::vector<const char*> mugg::ScriptSystem::GetRegistredMetatablesGlobalNames() {
    return this->registredMetatablesGlobalNames;
}
const char* mugg::ScriptSystem::GetRegistredMetatablesPrivateNamesByIndex(int index) {
    return this->registredMetatablesPrivateNames[index];
}
const char* mugg::ScriptSystem::GetRegistredMetatablesGlobalNamesByIndex(int index) {
    return this->registredMetatablesGlobalNames[index];
}

void mugg::ScriptSystem::PrintStack() {
    int top = lua_gettop(this->state);
    for(int i = 0; i <= top; i++) {
        int current = lua_gettype(this->state, i);
        
        switch(current) {
            case LUA_NUMBER
        }
    }
}
