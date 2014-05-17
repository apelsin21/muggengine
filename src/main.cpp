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
#include "shaderprogram.hpp"
#include "engine.hpp"

int main() {
    mugg::Window window;
    mugg::Context context;
    context.SetMajorVersion(3);
    context.SetMinorVersion(0);
    context.UseCoreProfile(false);
    context.AddFlag(mugg::COLOR_BUFFER_BIT);
    context.AddFlag(mugg::DEPTH_BUFFER_BIT);
    mugg::Engine engine(context);

    mugg::ShaderProgram shaderProgram;
    shaderProgram.AddShader("data/shaders/vertex.glsl", mugg::VERTEX_SHADER);
    shaderProgram.AddShader("data/shaders/fragment.glsl", mugg::FRAGMENT_SHADER);

    engine.AddShaderProgram(shaderProgram);

    window.Create("MuggEngine Window", glm::vec2(800, 600), glm::vec2(0, 0));
    if(!engine.Initialize()) {
        mugg::WriteToLog(mugg::FATAL_ERROR, "Failed to initialize engine");
        return -1;
    }

    while(window.IsOpen()) {
        engine.Render();

        window.SwapBuffers();
        glfwPollEvents();
    }

	return 0;
}
