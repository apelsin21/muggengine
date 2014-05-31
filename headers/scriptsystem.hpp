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

            std::vector<const char*> registredMetatablesPrivateNames;
            std::vector<const char*> registredMetatablesGlobalNames;
            
            std::vector<const char*> registredFunctionsPrivateNames;
            std::vector<const char*> registredFunctionsGlobalNames;

            bool usesStandardLibrary;
        public:
            ScriptSystem(bool useStandardLibrary);
            ScriptSystem(lua_State* state);
            ~ScriptSystem();

            void UseStandardLibrary(bool use);
            bool IsUsingStandardLibrary();

            void SetState(lua_State* state);
            lua_State* GetState();

            void RegisterMetatable(luaL_Reg* functions, const char* privateName, const char* globalName);
            std::vector<const char*> GetRegistredMetatablesPrivateNames();
            std::vector<const char*> GetRegistredMetatablesGlobalNames();
            const char* GetRegistredMetatablesPrivateNamesByIndex(int index);
            const char* GetRegistredMetatablesGlobalNamesByIndex(int index);

            void RegisterFunctions(luaL_Reg* functions);

            void PrintStack();

            void DoFile(const char* filepath);
    };
}

#endif
