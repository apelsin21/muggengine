#include <string>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "filehandler.hpp"
#include "log.hpp"
#include "file.hpp"
#include "shader.hpp"

int main() {
    int width = 800, height = 600;
    int major_ver = 3, minor_ver = 0;

    SDL_Window* window;
    SDL_GLContext context;

    window = SDL_CreateWindow("MuggEngine Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major_ver);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor_ver);

    context = SDL_GL_CreateContext(window);

    std::string error_msg = "Failed to create OpenGL context, with version: ";
    error_msg += major_ver;
    error_msg += ", ";
    error_msg += minor_ver;

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        mugg::WriteToLog(mugg::FATAL_ERROR, error_msg);
        return -1;
    }

    glEnable(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    while(true) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_F11]) {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
        }
        
        SDL_GL_SwapWindow(window);
    }

	return 0;
}
