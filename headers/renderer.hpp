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

namespace mugg {
    namespace graphics {
        class Renderer {
            private:
                std::vector<mugg::graphics::ShaderProgram> programVector;
                mugg::graphics::Color backgroundColor;
                int fbWidth, fbHeight;
            public:
                Renderer();
                ~Renderer();

                void SetBackgroundColor(mugg::graphics::Color color);
                mugg::graphics::Color GetBackgroundColor();

                bool AddShaderProgram(mugg::graphics::ShaderProgram program);
                mugg::graphics::ShaderProgram GetShaderProgramByIndex(int index);
                std::vector<mugg::graphics::ShaderProgram> GetShaderProgramVector();
                
                bool Initialize();
                
                void Render(mugg::Window window);
                void Render(int width, int height);
        };

    }
}

#endif
