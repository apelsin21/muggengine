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
    namespace core {
        class Device;
    }

    namespace graphics {
        class Renderer {
            private:
                std::vector<GLuint> programVector;
                mugg::graphics::Color backgroundColor;

                bool wireframe;
                
                mugg::core::Device* creator;
            public:
                Renderer(mugg::core::Device*);
                ~Renderer();

                void SetBackgroundColor(const mugg::graphics::Color&);
                mugg::graphics::Color GetBackgroundColor();

                bool AddShaderProgram(GLuint);
                GLuint GetShaderProgramByIndex(int);
                std::vector<GLuint> GetShaderProgramVector();
                
                void SetWireframe(bool);
                bool GetWireframe();

                bool Initialize();
                
                void Draw();
        };

    }
}

#endif
