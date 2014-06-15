#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <glm/glm.hpp>

namespace mugg {
    class Window {
        private:
            sf::Window window;
            glm::vec2 resolution, position;
            bool fullscreen, vsync, active, open, focused;
            int framerateLimit;
            const char* title;
            bool changed; //True if window needs to recreate, false if not
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

            bool IsFocused();

            void SetTitle(const char* title);
            const char* GetTitle();

            //Sets new resolution, changes from fullscreen, etc.
            //Returns true on success, else false
            bool Recreate();

            void ReactToEvents();            

            //Swaps front and back buffers
            void SwapBuffers();
    };
}

#endif
