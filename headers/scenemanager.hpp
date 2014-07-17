#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <vector>

#include "scenenode.hpp"

namespace mugg {
    namespace scene {
        class SceneManager {
            private:
                std::vector<mugg::scene::SceneNode> sceneNodeVector;
            public:
        };
    }
}

#endif
