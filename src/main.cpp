#include <string>
#include <vector>
#include <ctime>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "filehandler.hpp"
#include "log.hpp"
#include "file.hpp"
#include "shader.hpp"
#include "defs.hpp"
#include "window.hpp"

int main() {
    
    mugg::Window window;

    window.Create("MuggEngine Window", glm::vec2(800, 600), glm::vec2(0, 0));

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        mugg::WriteToLog(mugg::FATAL_ERROR, "Failed to initialize GLEW!");
        return -1;
    }

    glEnable(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    while(window.IsOpen()) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        window.SwapBuffers();
        glfwPollEvents();
    }

	return 0;
}
