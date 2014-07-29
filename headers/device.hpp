#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <vector>
#include <string>

#include "guimanager.hpp"
#include "window.hpp"
#include "contentmanager.hpp"
#include "renderer.hpp"

#include <GL/glew.h>

namespace mugg {
    namespace core {
        class Device {
            private:
                std::vector<mugg::gui::GUIManager*> guiManagers;
                std::vector<mugg::core::ContentManager*> contentManagers;
                std::vector<mugg::core::Window*> windows;
                std::vector<mugg::graphics::Renderer*> renderers;

            public:
                Device();
                ~Device();

                mugg::gui::GUIManager* GetGUIManager();

                mugg::core::ContentManager* GetContentManager();

                mugg::core::Window* GetWindow();

                mugg::graphics::Renderer* GetRenderer();
        };
    }
}

#endif