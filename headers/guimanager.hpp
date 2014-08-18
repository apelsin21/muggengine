#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <vector>
#include <iostream>
#include <string>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_CXX11
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderprogram.hpp"
#include "shader.hpp"

namespace mugg {
    namespace core {
        class Device;
    }
    
    namespace gui {
        class Image;
        
        class GUIManager {
            private:
                #define GLSL(src) "#version 330 core\n" #src

                std::string vsData = GLSL(
                    layout(location = 0) in vec2 v_pos;
                    layout(location = 1) in vec2 v_uv;
                    layout(location = 2) in mat4 v_model;

                    out vec2 f_uv;

                    void main() {
                        f_uv = v_uv;
                        gl_Position = v_model * vec4(v_pos, 0.0, 1.0);
                    }
                );
                
                std::string fsData = GLSL(
                    in vec2 f_uv;
                    out vec4 color;
                    uniform sampler2D sampler;

                    void main() {
                        color = texture(sampler, f_uv);
                    }    
                );

                std::vector<mugg::gui::Image*> images;

                GLuint positionBuffer, vaoID, modelMatrixBuffer;
                GLuint vsID, fsID, programID;

                int posLocation, uvLocation, modelLocation;

                mugg::core::Device* parent;
            public:
                GUIManager(mugg::core::Device*);
                ~GUIManager();

                virtual mugg::gui::Image* CreateImage();
                virtual std::size_t GetNumberOfImages();
                virtual bool GetImageByIndex(int, mugg::gui::Image*&);

                virtual void Render();
        };
    }
}

#endif
