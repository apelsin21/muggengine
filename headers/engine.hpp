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

                virtual mugg::gui::GUIManager* GetGUIManager();

                virtual mugg::core::ContentManager* GetContentManager();

                virtual mugg::core::Window* GetWindow();

                virtual mugg::graphics::Renderer* GetRenderer();
           
                virtual mugg::scene::SceneManager* GetSceneManager();

                virtual mugg::net::NetManager* GetNetManager();
            
                virtual void Render();
        };
    }
}

#endif
