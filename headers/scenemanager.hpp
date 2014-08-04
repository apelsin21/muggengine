#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <vector>

#include "scenenode.hpp"

namespace mugg {
    namespace core {
        class Device;
    }
    
    namespace scene {
        class SceneManager {
            private:
                std::vector<mugg::scene::SceneNode*> sceneNodes;
            
                mugg::core::Device* parent;
            public:
                SceneManager(mugg::core::Device*);
                ~SceneManager();

                virtual mugg::scene::SceneNode* CreateSceneNode();
                virtual std::size_t GetNumberOfSceneNodes();
                virtual bool GetSceneNodeByIndex(int, mugg::scene::SceneNode*&);
        };
    }
}

#endif
