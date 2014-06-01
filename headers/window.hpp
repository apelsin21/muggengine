#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Window.hpp>
#include <glm/glm.hpp>

namespace mugg {
    class Window {
        private:
            sf::Window window;
            glm::vec2 resolution, position;
            bool fullscreen, vsync, active, open;
            int framerateLimit;
            const char* title;
        public:
            Window(glm::vec2 resolution, glm::vec2 position, const char* title);
            ~Window();

            void SetPosition(glm::vec2 position);
            glm::vec2 GetPosition();

            void SetResolution(glm::vec2 resolution);
            glm::vec2 GetResolution();

            void SetFullscreen(bool fullscreen);
            bool GetFullscreen();
            
            void SetOpen(bool open);
            bool IsOpen();
            void Close();

            void SetVsync(bool enabled);
            bool GetVsync();

            void SetFramerateLimit(int limit);
            int GetFramerateLimit();

            void SetActive(bool active);
            bool GetActive();

            void SetTitle(const char* title);
            const char* GetTitle();

            //Sets new resolution, changes from fullscreen, etc.
            //Returns true on success, else false
            bool Recreate();

            //Swaps front and back buffers
            void SwapBuffers();
    };
}

#endif
