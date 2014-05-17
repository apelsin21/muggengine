#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "log.hpp"
#include "context.hpp"
#include "shaderprogram.hpp"
#include "color.hpp"

namespace mugg {
    class Engine {
    private:
        mugg::Context context;
        std::vector<mugg::ShaderProgram> shaderPrograms;
    public:
        Engine(mugg::Context context);
        ~Engine();

        bool Initialize();

        void AddShaderProgram(mugg::ShaderProgram program);
        std::vector<mugg::ShaderProgram> GetShaderPrograms();

        void Render();
    };
}

#endif