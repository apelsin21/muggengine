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
        class Engine;
    }
    
    namespace scene {
        class SceneManager {
            private:
                std::vector<mugg::scene::SceneNode*> sceneNodes;
            
                mugg::core::Engine* parent;
            
                GLuint programID;
                GLint posLocation, uvLocation, normalLocation;
            public:
                SceneManager(mugg::core::Engine*);
                ~SceneManager();

                mugg::scene::SceneNode* CreateSceneNode();
                std::size_t GetNumberOfSceneNodes();
                bool GetSceneNodeByIndex(int, mugg::scene::SceneNode*&);

                void SetShaderProgramID(GLuint id);
                GLuint GetShaderProgramID();

                void Render();
        };
    }
}

#endif
