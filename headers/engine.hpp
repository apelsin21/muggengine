#ifndef Engine_HPP
#define Engine_HPP

#include <iostream>
#include <vector>
#include <string>

#include "guimanager.hpp"
#include "window.hpp"
#include "contentmanager.hpp"
#include "renderer.hpp"
#include "scenemanager.hpp"
#include "netmanager.hpp"

#include <SDL2/SDL.h>

namespace mugg {
    namespace core {
        class Engine {
            private:
                mugg::gui::GUIManager* guiManager;
                mugg::core::ContentManager* contentManager;
                mugg::scene::SceneManager* sceneManager;
                mugg::core::Window* window;
                mugg::graphics::Renderer* renderer;
                mugg::net::NetManager* netManager;
            public:
                Engine();
                ~Engine();

                mugg::gui::GUIManager* GetGUIManager();

                mugg::core::ContentManager* GetContentManager();

                mugg::core::Window* GetWindow();

                mugg::graphics::Renderer* GetRenderer();
           
                mugg::scene::SceneManager* GetSceneManager();

                mugg::net::NetManager* GetNetManager();
            
                void Render();
        };
    }
}

#endif
