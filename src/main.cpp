#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include <string>
#include <iostream>

#include "scriptsystem.hpp"

#include "windowbinds.hpp"
#include "colorbinds.hpp"
#include "shaderprogrambinds.hpp"
#include "shaderbinds.hpp"
#include "rendererbinds.hpp"
#include "texture2dbinds.hpp"
#include "serverbinds.hpp"
#include "clientbinds.hpp"
#include "stringpacketbinds.hpp"
#include "netmanagerbinds.hpp"
#include "contentmanagerbinds.hpp"
#include "guimanagerbinds.hpp"
#include "imagebinds.hpp"
#include "devicebinds.hpp"
#include "vec2binds.hpp"
#include "keyboardbinds.hpp"

int main(int argc, char* argv[]) {
    mugg::ScriptSystem system(true);

    system.RegisterMetatable(mugg::binds::windowFuncs, mugg::binds::WindowName);
    system.RegisterMetatable(mugg::binds::colorFuncs, mugg::binds::ColorName);
    system.RegisterMetatable(mugg::binds::shaderProgramFuncs, mugg::binds::ShaderProgramName);
    system.RegisterMetatable(mugg::binds::rendererFuncs, mugg::binds::RendererName);
    system.RegisterMetatable(mugg::binds::shaderFuncs, mugg::binds::ShaderName);
    system.RegisterMetatable(mugg::binds::texture2DFuncs, mugg::binds::Texture2DName);
    system.RegisterMetatable(mugg::binds::serverFuncs, mugg::binds::ServerName);
    system.RegisterMetatable(mugg::binds::clientFuncs, mugg::binds::ClientName);
    system.RegisterMetatable(mugg::binds::stringPacketFuncs, mugg::binds::StringPacketName);
    system.RegisterMetatable(mugg::binds::netManagerFuncs, mugg::binds::NetManagerName);
    system.RegisterMetatable(mugg::binds::contentManagerFuncs, mugg::binds::ContentManagerName);
    system.RegisterMetatable(mugg::binds::guiManagerFuncs, mugg::binds::GUIManagerName);
    system.RegisterMetatable(mugg::binds::imageFuncs, mugg::binds::ImageName);
    system.RegisterMetatable(mugg::binds::deviceFuncs, mugg::binds::DeviceName);
    system.RegisterMetatable(mugg::binds::vec2Funcs, mugg::binds::Vec2Name);
    system.RegisterMetatable(mugg::binds::keyboardFuncs, mugg::binds::KeyboardName);

    if(argc > 2) {
        std::cout << "Got too many arguments. (Expected one)\n";
        std::cout << "Usage: " << argv[0] << " \"filename\"" << std::endl;
        std::cout << "If there are no arguments, it tries to open \"main.lua\" in the local directory.\n";
        std::cout << "Exiting.\n";
        return -1;
    }
    else if(argc == 2) {
        system.DoFile(argv[1]);
    } else {
        system.DoFile("main.lua");
    }

    SDL_Quit();

    /*
    SDL_Window *mainwindow;
    SDL_GLContext maincontext;
 
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "Unable to initialize SDL\n";
 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
 
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
 
    mainwindow = SDL_CreateWindow("bajs", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow)
        std::cout << "Unable to create window\n";
 
 
    maincontext = SDL_GL_CreateContext(mainwindow);

    glewExperimental = GL_TRUE;
    glewInit(); 
 
    SDL_GL_SetSwapInterval(1);
 
    glClearColor ( 1.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(2000);
 
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
    */

    return 0;
}
