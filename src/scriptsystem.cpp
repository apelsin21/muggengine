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

void mugg::ScriptSystem::RegisterMetatable(luaL_Reg* functions, const char* name) {
    luaL_newmetatable(this->state, name);
    luaL_setfuncs(this->state, functions, 0);
    lua_pushvalue(this->state, -1);
    lua_setfield(this->state, -2, "__index");

    lua_setglobal(this->state, name);

    this->registredMetatableNames.push_back(name);
}
std::vector<const char*> mugg::ScriptSystem::GetRegistredMetatableNames() {
    return this->registredMetatableNames;
}
const char* mugg::ScriptSystem::GetRegistredMetatableNamesByIndex(int index) {
    return this->registredMetatableNames[index];
}

void mugg::ScriptSystem::PrintStack() {
    std::cout << "### LUA STACK DUMP BEGIN ###\n";
    
    int top = lua_gettop(this->state);
    for(int i = 0; i <= top; i++) {
        int current = lua_type(this->state, i);
        
        std::cout << "Index: " << i << " type: " << lua_typename(this->state, current) << " value: ";

        switch(current) {
            case LUA_TNUMBER:
                std::cout << lua_tonumber(this->state, i);
            break;
            case LUA_TSTRING:
                std::cout << lua_tostring(this->state, i);
            break;
            case LUA_TBOOLEAN:
                std::cout << lua_toboolean(this->state, i) ? "true" : "false";
            break;
        }

        std::cout << std::endl;
    }

    std::cout << "### LUA STACK DUMP END ###\n";
}

void mugg::ScriptSystem::DoFile(const char* filepath) {
    int error = luaL_dofile(this->state, filepath);

    if(error) {
        std::cout << lua_tostring(this->state, -1) << std::endl;
        lua_pop(this->state, 1);
    }
}
