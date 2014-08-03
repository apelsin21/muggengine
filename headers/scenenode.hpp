#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

namespace mugg {
    namespace scene {
        class SceneManager;

        class SceneNode {
            private:
                glm::vec4 position;

                mugg::scene::SceneManager* parent;
            public:
                SceneNode(mugg::scene::SceneManager*);
                ~SceneNode();
        };
    }
}

#endif
