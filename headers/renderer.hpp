#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "shaderprogram.hpp"
#include "color.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <vector>
#include <iostream>

namespace mugg {
    namespace graphics {
        class Renderer {
            private:
                std::vector<mugg::core::ShaderProgram> programVector;
                mugg::graphics::Color backgroundColor;
                glm::vec2 viewportResolution;
            public:
                Renderer();
                ~Renderer();

                void SetBackgroundColor(mugg::graphics::Color color);
                mugg::graphics::Color GetBackgroundColor();

                void AddShaderProgram(mugg::core::ShaderProgram program);
                mugg::core::ShaderProgram GetShaderProgramByIndex(int index);
                std::vector<mugg::core::ShaderProgram> GetShaderProgramVector();
                
                bool Initialize();
                
                void BeginRender(glm::vec2 viewportResolution);
                void EndRender();
        };

    }
}

#endif
