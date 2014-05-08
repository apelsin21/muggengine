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

void error_callback(int error, const char* message) {
    mugg::WriteToLog(mugg::ERROR, std::string(message));
}

int main() {
    int width = 800, height = 600;
    int major_ver = 3, minor_ver = 0;
    
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if(!glfwInit()) {
        mugg::WriteToLog(mugg::FATAL_ERROR, "Failed to initialize GLFW!");
        return -1;
    }

    window = glfwCreateWindow(width, height, "Muggengine Window", NULL, NULL);

    if(!window) {
        mugg::WriteToLog(mugg::FATAL_ERROR, "Failed to create GLFW window!");
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_ver);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_ver);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        mugg::WriteToLog(mugg::FATAL_ERROR, "Failed to initialize GLEW!");
        return -1;
    }

    glEnable(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if(glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
            window = glfwCreateWindow(1680, 1050, "Muggengine Window", glfwGetPrimaryMonitor(), NULL);
            glfwMakeContextCurrent(window);
            glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	return 0;
}
