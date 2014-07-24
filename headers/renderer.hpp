#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "shaderprogram.hpp"
#include "color.hpp"
#include "window.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <vector>
#include <iostream>
#include <memory>

namespace mugg {
    namespace graphics {
        class Renderer {
            private:
                std::vector<std::shared_ptr<mugg::graphics::ShaderProgram>> programVector;
                mugg::graphics::Color backgroundColor;
            public:
                Renderer();
                ~Renderer();

                void SetBackgroundColor(const mugg::graphics::Color&);
                mugg::graphics::Color GetBackgroundColor();

                bool AddShaderProgram(std::shared_ptr<mugg::graphics::ShaderProgram>&);
                std::shared_ptr<mugg::graphics::ShaderProgram> GetShaderProgramByIndex(int);
                std::vector<std::shared_ptr<mugg::graphics::ShaderProgram>> GetShaderProgramVector();
                
                bool Initialize();
                
                void Draw();
        };

    }
}

#endif
