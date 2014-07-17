#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <vector>

#include "mesh.hpp"

namespace mugg {
    namespace scene {
        class SceneNode {
            private:
                std::vector<mugg::graphics::Mesh> meshVector;
                const char* name;
            public:
        };
    }
}

#endif
