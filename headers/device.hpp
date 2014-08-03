#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <vector>
#include <string>

#include "guimanager.hpp"
#include "window.hpp"
#include "contentmanager.hpp"
#include "renderer.hpp"
#include "scenemanager.hpp"

namespace mugg {
    namespace core {
        class Device {
            private:
                std::vector<mugg::gui::GUIManager*> guiManagers;
                std::vector<mugg::core::ContentManager*> contentManagers;
                std::vector<mugg::scene::SceneManager*> sceneManagers;
                std::vector<mugg::core::Window*> windows;
                std::vector<mugg::graphics::Renderer*> renderers;
            public:
                Device();
                ~Device();

                virtual mugg::gui::GUIManager* CreateGUIManager();

                virtual mugg::core::ContentManager* CreateContentManager();

                virtual mugg::core::Window* CreateWindow();

                virtual mugg::graphics::Renderer* CreateRenderer();
            
                virtual mugg::scene::SceneManager* CreateSceneManager();
        };
    }
}

#endif
