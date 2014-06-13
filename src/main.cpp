#include <string>
#include <iostream>

#include <lua.hpp>
#include <glm/glm.hpp>
#include <SFML/System.hpp>

#include "scriptsystem.hpp"

#include "windowbinds.hpp"
#include "inputhandlerbinds.hpp"
#include "colorbinds.hpp"

int main() {
    mugg::ScriptSystem system(true);

    system.RegisterMetatable(mugg::binds::windowFuncs, "mugg_Window", "Window");
    system.RegisterMetatable(mugg::binds::inputHandlerFuncs, "mugg_InputHandler", "InputHandler");
    system.RegisterMetatable(mugg::binds::colorFuncs, "mugg_Color", "Color");

    system.DoFile("main.lua");
    return 0;
}
