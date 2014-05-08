#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "log.hpp"
#include "context.hpp"
#include "shaderprogram.hpp"
#include "color.hpp"

namespace mugg {
    class Engine {
    private:
        mugg::Context context;
        mugg::Color backgroundColor;
        std::vector<mugg::ShaderProgram> shaderPrograms;
    public:
        Engine(mugg::Context context);
        ~Engine();

        void Initialize();

        void SetBackgroundColor(mugg::Color color);
        mugg::Color GetBackgroundColor();

        void AddShaderProgram(mugg::ShaderProgram program);
        std::vector<mugg::ShaderProgram> GetShaderPrograms();

        void Render();
    };
}

#endif
