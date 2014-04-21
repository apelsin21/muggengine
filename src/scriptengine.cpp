#include "scriptengine.hpp"

ScriptEngine::ScriptEngine() {
	this->L = luaL_newstate();
    luaL_openlibs(this->L);
}

ScriptEngine::~ScriptEngine() {
    lua_close(this->L);
}

void ScriptEngine::RunScript(Script* script) {
    int status = luaL_dostring(this->L, script->GetContent());

    ReportErrors(status);
}

void ScriptEngine::ReportErrors(int status) {
    if(status != 0) {
        std::cout << "Lua error: " << this->ToString(-1) << std::endl;
        this->Pop(1);
    }
}

void ScriptEngine::SetLuaState(lua_State* L) {
    this->L = L;
}
lua_State* ScriptEngine::GetLuaState() {
    return this->L;
}

void ScriptEngine::RegisterFunction(lua_CFunction function, const char* name) {
    lua_pushcfunction(this->L, function);
    lua_setglobal(this->L, name);
}

int ScriptEngine::GetTop() {
	return lua_gettop(this->L);
}
void ScriptEngine::SetTop(int index) {
	lua_settop(this->L, index);
}
void ScriptEngine::DumpStack() {
	int i, t;
	int top = this->GetTop();
	
	for(i = 1; i <= top; i++) {
		t = lua_type(this->L, i);
		
		switch(t) {
			case LUA_TSTRING:
				std::cout << this->ToString(i) << std::endl;
				break;
			case LUA_TBOOLEAN:
				std::cout << this->ToBoolean(i) << std::endl;
				break;
			case LUA_TNUMBER:
				std::cout << this->ToNumber(i) << std::endl;
				break;
			default:
				std::cout << this->TypeName(t) << std::endl;
				break;
		}
	}
}

void ScriptEngine::Pop(int index) {
    lua_pop(this->L, index);
}

const char* ScriptEngine::TypeName(int tp) {
	return lua_typename(this->L, tp);
}

void ScriptEngine::PushValue(int index) {
	lua_pushvalue(this->L, index);
}
void ScriptEngine::Remove(int index) {
	lua_remove(this->L, index);
}
void ScriptEngine::Insert(int index) {
	lua_insert(this->L, index);
}
void ScriptEngine::Replace(int index) {
	lua_replace(this->L, index);
}
void ScriptEngine::Copy(int fromIndex, int toIndex) {
	lua_copy(this->L, fromIndex, toIndex);
}

bool ScriptEngine::ToBoolean(int index) {
	return lua_toboolean(this->L, index);
}
const char* ScriptEngine::ToLString(int index, std::size_t &str_len) {
	return lua_tostring(this->L, str_len);
}
const char* ScriptEngine::ToString(int index) {
	return lua_tostring(this->L, index);
}
double ScriptEngine::ToNumber(int index) {
	return lua_tonumber(this->L, index);
}
int ScriptEngine::ToInteger(int index) {
	return lua_tointeger(this->L, index);
}
unsigned int ScriptEngine::ToUnsigned(int index) {
	return lua_tounsigned(this->L, index);
}

void ScriptEngine::PushNil() {
	lua_pushnil(this->L);
}
void ScriptEngine::PushBoolean(bool boolean) {
	lua_pushboolean(this->L, boolean);
}
void ScriptEngine::PushDouble(double number) {
	lua_pushnumber(this->L, number);
}
void ScriptEngine::PushInteger(int integer) {
	lua_pushinteger(this->L, integer);
}
void ScriptEngine::PushUnsigned(unsigned int unsigned_integer) {
	lua_pushunsigned(this->L, unsigned_integer);
}
void ScriptEngine::PushLString(const char* string, std::size_t len) {
	lua_pushlstring(this->L, string, len);
}
void ScriptEngine::PushString(const char* string) {
	lua_pushstring(this->L, string);
}
