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
#include <chrono>

namespace mugg {
    namespace core {
        class Device;
    }

    namespace graphics {
        class Renderer {
            private:
                std::vector<GLuint> programVector;
                mugg::graphics::Color backgroundColor;

                int frames;
                double frametime;
                double deltatime;
                std::chrono::system_clock::time_point lastTime;

                bool wireframe;
                
                void UpdateTime();
                mugg::core::Device* creator;
            public:
                Renderer(mugg::core::Device*);
                ~Renderer();

                //Get time between frames
                double GetDeltatime();
                //Get milliseconds per frame, averaged over one second
                double GetFrametime();
                double GetFPS();

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
