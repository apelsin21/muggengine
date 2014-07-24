#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP

#include <iostream>
#include <vector>
#include <string>

#include "lua.hpp"

namespace mugg {
    class ScriptSystem {
        private:
            lua_State* state;

            std::vector<const char*> registredMetatableNames;
            
            std::vector<const char*> registredFunctionNames;

            bool usesStandardLibrary;
        public:
            ScriptSystem(bool useStandardLibrary);
            ScriptSystem(lua_State* state);
            ~ScriptSystem();

            void UseStandardLibrary(bool use);
            bool IsUsingStandardLibrary();

            void SetState(lua_State* state);
            lua_State* GetState();

            void RegisterMetatable(luaL_Reg* functions, const char* name);
            std::vector<const char*> GetRegistredMetatableNames();
            const char* GetRegistredMetatableNamesByIndex(int index);

            void PrintStack();

            void DoFile(const char* filepath);
    };
}

#endif
