#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "mesh.hpp"

namespace mugg {
    namespace scene {
        class SceneNode {
            private:
                std::vector<mugg::graphics::Mesh> meshVector;
                const char* name;
                glm::vec4 position;
            public:
        };
    }
}

#endif
