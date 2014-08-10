#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "mesh.hpp"

namespace mugg {
    namespace scene {
        class SceneManager;

        class SceneNode {
            private:
                glm::vec4 position;

                mugg::scene::SceneManager* parent;
                std::vector<mugg::graphics::Mesh*> meshes;
            public:
                SceneNode(mugg::scene::SceneManager*);
                ~SceneNode();

                void AddMesh(mugg::graphics::Mesh*&);
                bool GetMeshByIndex(int, mugg::graphics::Mesh*&);
                int GetNumberOfMeshes();

                void SetPosition(const glm::vec4&);
                glm::vec4 GetPosition();
        };
    }
}

#endif
