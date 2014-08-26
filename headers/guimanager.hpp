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

#include "spritebatch.hpp"

namespace mugg {
    namespace core {
        class Engine;
    }
    
    namespace gui {
        class Image;
        
        class GUIManager {
            private:
                #define GLSL(src) "#version 330 core\n" #src

                std::string vsData = GLSL(
                    layout(location = 0) in vec2 v_pos;
                    layout(location = 1) in vec2 v_uv;
                    layout(location = 2) in vec3 v_color;
                    layout(location = 3) in mat4 v_model;

                    out vec2 f_uv;
                    out vec3 f_color;

                    void main() {
                        f_uv = v_uv;
                        f_color = v_color;
                        gl_Position = v_model * vec4(v_pos, 0.0, 1.0);
                    }
                );
                
                std::string fsData = GLSL(
                    in vec2 f_uv;
                    in vec3 f_color;

                    out vec4 color;
                    uniform sampler2D sampler;

                    void main() {
                        color = vec4(f_color.rgb, 1.0);//texture(sampler, f_uv);
                    }    
                );

                std::vector<mugg::gui::Image*> images;
                std::vector<unsigned int> imagesToBeUpdated;
                
                std::vector<mugg::graphics::SpriteBatch*> spriteBatches;
                    
                GLuint vaoID;
                GLuint vsID, fsID, programID;
               
                GLint posLocation, uvLocation, colLocation, modelLocation;

                mugg::core::Engine* parent;
            public:
                GUIManager(mugg::core::Engine*);
                ~GUIManager();

                virtual mugg::gui::Image* CreateImage();
                virtual void UpdateImage(unsigned int);
                virtual std::size_t GetNumberOfImages();
                virtual bool GetImageByIndex(int, mugg::gui::Image*&);

                virtual void Render();
        };
    }
}

#endif
