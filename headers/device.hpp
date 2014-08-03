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
                virtual std::size_t GetNumberOfGUIManagers();
                virtual bool GetGUIManagerByIndex(int, mugg::gui::GUIManager*&);

                virtual mugg::core::ContentManager* CreateContentManager();
                virtual std::size_t GetNumberOfContentManagers();
                virtual bool GetContentManagerByIndex(int, mugg::core::ContentManager*&);

                virtual mugg::core::Window* CreateWindow();
                virtual std::size_t GetNumberOfWindows();
                virtual bool GetWindowByIndex(int, mugg::core::Window*&);

                virtual mugg::graphics::Renderer* CreateRenderer();
                virtual std::size_t GetNumberOfRenderers();
                virtual bool GetRendererByIndex(int, mugg::graphics::Renderer*&);
            
                virtual mugg::scene::SceneManager* CreateSceneManager();
                virtual std::size_t GetNumberOfSceneManagers();
                virtual bool GetSceneManagerByIndex(int, mugg::scene::SceneManager*&);
        };
    }
}

#endif
