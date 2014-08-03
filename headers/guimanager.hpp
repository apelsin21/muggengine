#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <vector>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

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
                #define GLSL(src) "#version 130\n" #src

                std::string vsData = GLSL(
                    in vec2 v_pos;
                    in vec2 v_uv;

                    in mat4 v_model;

                    out vec2 f_uv;

                    void main() {
                        f_uv = v_uv;
                        gl_Position = vec4(v_pos, 0.0, 1.0);
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

                std::vector<GLuint> textures;
                std::vector<glm::vec2> positions;

                GLuint vboID, vaoID, ibID;
                GLuint vsID, fsID, programID;

                int posLocation, uvLocation, modelLocation;

                mugg::core::Device* creator;
            public:
                GUIManager(mugg::core::Device*);
                ~GUIManager();

                virtual void SetObjectPosition(unsigned int, glm::vec2);
                virtual glm::vec2 GetObjectPosition(unsigned int);

                virtual void SetObjectTexture(unsigned int texture, GLuint);
                virtual GLuint GetObjectTexture(unsigned int);

                virtual mugg::gui::Image* CreateImage();

                virtual void Render();
        };
    }
}

#endif
