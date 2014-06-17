#include <string>
#include <iostream>

#include <lua.hpp>
#include <glm/glm.hpp>
#include <SFML/System.hpp>

#include <GL/glew.h>

#include "scriptsystem.hpp"
#include "texture2d.hpp"

#include "windowbinds.hpp"
#include "inputhandlerbinds.hpp"
#include "colorbinds.hpp"
#include "shaderprogrambinds.hpp"
#include "rendererbinds.hpp"

int main() {
    sf::Context context;

    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        std::cout << "GLEW failed to initialize! Please fix your graphics drivers.\n";
        return -1;
    }

    mugg::ScriptSystem system(true);

    system.RegisterMetatable(mugg::binds::windowFuncs, "mugg_Window", "Window");
    system.RegisterMetatable(mugg::binds::inputHandlerFuncs, "mugg_InputHandler", "InputHandler");
    system.RegisterMetatable(mugg::binds::colorFuncs, "mugg_Color", "Color");
    system.RegisterMetatable(mugg::binds::shaderProgramFuncs, "mugg_ShaderProgram", "ShaderProgram");
    system.RegisterMetatable(mugg::binds::rendererFuncs, "mugg_Renderer", "Renderer");

    system.DoFile("main.lua");

    return 0;

}
