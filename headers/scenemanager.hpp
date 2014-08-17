#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <vector>

#include "scenenode.hpp"
#include "errorhandling.hpp"

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace mugg {
    namespace core {
        class Device;
    }
    
    namespace scene {
        class SceneManager {
            private:
                std::vector<mugg::scene::SceneNode*> sceneNodes;
            
                mugg::core::Device* parent;
            
                GLuint programID;
            public:
                SceneManager(mugg::core::Device*);
                ~SceneManager();

                virtual mugg::scene::SceneNode* CreateSceneNode();
                virtual std::size_t GetNumberOfSceneNodes();
                virtual bool GetSceneNodeByIndex(int, mugg::scene::SceneNode*&);

                virtual void SetShaderProgramID(GLuint id);
                virtual GLuint GetShaderProgramID();

                virtual void Render();
        };
    }
}

#endif
