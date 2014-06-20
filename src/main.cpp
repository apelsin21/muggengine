#include <string>
#include <iostream>

#include <lua.hpp>
#include <glm/glm.hpp>
#include <SFML/System.hpp>

#include <GL/glew.h>

#include "scriptsystem.hpp"
#include "texture2d.hpp"
#include "shader.hpp"

#include "windowbinds.hpp"
#include "inputhandlerbinds.hpp"
#include "colorbinds.hpp"
#include "shaderprogrambinds.hpp"
#include "shaderbinds.hpp"
#include "rendererbinds.hpp"

void checkForError() {
    GLenum errorCode;    

    std::string error;
    std::string description;

    do {
        errorCode = glGetError();
        
        switch (errorCode) {
            case GL_INVALID_ENUM:
                error = "GL_INVALID_ENUM";
                description = "an unacceptable value has been specified for an enumerated argument";
                break;

            case GL_INVALID_VALUE:
                error = "GL_INVALID_VALUE";
                description = "a numeric argument is out of range";
                break;

            case GL_INVALID_OPERATION:
                error = "GL_INVALID_OPERATION";
                description = "the specified operation is not allowed in the current state";
                break;

            case GL_STACK_OVERFLOW:
                error = "GL_STACK_OVERFLOW";
                description = "this command would cause a stack overflow";
                break;

            case GL_STACK_UNDERFLOW:
                error = "GL_STACK_UNDERFLOW";
                description = "this command would cause a stack underflow";
                break;

            case GL_OUT_OF_MEMORY:
                error = "GL_OUT_OF_MEMORY";
                description = "there is not enough memory left to execute the command";
                break;
        }

        if(errorCode != GL_NO_ERROR) {
            std::cout << "OPENGL ERROR!\n";
            std::cout << "ERROR: " << error << std::endl;
            std::cout << "DESCRIPTION: " << description << std::endl;
        }
    } while(errorCode != GL_NO_ERROR);
}

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
    system.RegisterMetatable(mugg::binds::shaderFuncs, mugg::binds::ShaderPrivateName, mugg::binds::ShaderPublicName);

    system.DoFile("main.lua");

    checkForError();

    return 0;
}
