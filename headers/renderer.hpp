#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "log.hpp"
#include "context.hpp"
#include "shaderprogram.hpp"

namespace mugg {
    class Renderer {
    private:
        mugg::Context context; 
        std::vector<mugg::ShaderProgram> shaderPrograms;
    public:
        Renderer(mugg::Context context);
        ~Renderer();

        void Initialize();

        void AddShaderProgram(mugg::ShaderProgram, int index);
        std::vector<mugg::ShaderProgram> GetShaderPrograms();

        void Render();
    };
}

#endif
