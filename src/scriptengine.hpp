#ifndef SCRIPTENGINE_HPP
#define SCRIPTENGINE_HPP

#include <lua.hpp>
#include <vector>
#include <iostream>

#include "script.hpp"

class ScriptEngine {
private:
	std::vector<Script> scripts;
	lua_State *L;

    void ReportErrors(int status);
public:
	ScriptEngine();
	~ScriptEngine();

    void RegisterFunction(lua_CFunction function, const char* name);

    void Run();

    void RunScript(Script* script);
	
	void DumpStack();

    void SetLuaState(lua_State* L);
    lua_State* GetLuaState();

	int GetTop();
	void SetTop(int index);
	
    void Pop(int index);

	const char* TypeName(int tp);
	
	void PushValue(int index);
	void Remove(int index);
	void Insert(int index);
	void Replace(int index);
	void Copy(int fromIndex, int toIndex);
	
	bool ToBoolean(int index);
	const char* ToLString(int index, std::size_t &length);
	const char* ToString(int index);
	double ToNumber(int index);
	int ToInteger(int index);
	unsigned int ToUnsigned(int index);
	
	void PushNil();
	void PushBoolean(bool boolean);
	void PushDouble(double number);
	void PushInteger(int integer);
	void PushUnsigned(unsigned int unsigned_integer);
	void PushLString(const char* string, std::size_t len);
	void PushString(const char* string);
};

#endif
