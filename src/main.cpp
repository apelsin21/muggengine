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
    //24 depth bits
    //8 stencil bits
    //0 antialiasing
    //OpenGL version 3.0
    sf::ContextSettings settings(24, 8, 0, 3, 0);
    sf::Context context(settings, 800, 600);

    glewExperimental = true;
    GLenum errorMessage = glewInit();
    if(errorMessage != GLEW_OK) {
        std::cout << "Failed to create a valid OpenGL context! Please fix your graphics drivers.\n";
        std::cout << "GLEW error message:\n";
        std::cout << glewGetErrorString(errorMessage) << std::endl;
        return -1;
    }

    mugg::ScriptSystem system(true);

    system.RegisterMetatable(mugg::binds::windowFuncs, mugg::binds::WindowPrivateName, mugg::binds::WindowPublicName);
    system.RegisterMetatable(mugg::binds::inputHandlerFuncs, mugg::binds::InputHandlerPrivateName, mugg::binds::InputHandlerPublicName);
    system.RegisterMetatable(mugg::binds::colorFuncs, mugg::binds::ColorPrivateName, mugg::binds::ColorPublicName);
    system.RegisterMetatable(mugg::binds::shaderProgramFuncs, mugg::binds::ShaderProgramPrivateName, mugg::binds::ShaderProgramPublicName);
    system.RegisterMetatable(mugg::binds::rendererFuncs, mugg::binds::RendererPrivateName, mugg::binds::RendererPublicName);

    system.DoFile("main.lua");

    return 0;
}
