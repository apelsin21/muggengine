#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "keydefs.hpp"

namespace mugg {
    class Window {
        private:
            GLFWwindow* window;
            int width, height, posX, posY;
            bool fullscreen, vsync, open, focused, iconified, visible;
            int framerateLimit;
            const char* title;
            bool changed; //True if window needs to recreate, false if not
        public:
            Window(int width, int height, const char* title);
            Window();
            ~Window();

            bool Open(int width, int height, const char* title);
            bool IsOpen();
            void Close();
            
            void SetPosition(int x, int y);
            int GetPositionX();
            int GetPositionY();

            void SetSize(int width, int height);
            void GetSize(int &out_width, int &out_height);

            void SetResolution(int width, int height);
            int GetWidth();
            int GetHeight();
            
            void GetFramebufferSize(int &out_width, int &out_height);

            void SetFullscreen(bool fullscreen, int monitor);
            bool GetFullscreen();

            void SetIconified(bool iconified);
            bool IsIconified();

            void SetVsync(bool enabled);
            bool GetVsync();

            void SetFramerateLimit(int limit);
            int GetFramerateLimit();

            bool IsFocused();

            void SetTitle(const char* title);
            const char* GetTitle();

            //Sets new resolution, changes from fullscreen, etc.
            //Returns true on success, else false
            bool Recreate();

            void ReactToEvents();            

            bool IsKeyDown(mugg::input::Key key);
            bool IsKeyStringDown(const char* string);
            mugg::input::Key GetLastPressedKey();

            //Swaps front and back buffers
            void SwapBuffers();
    };
}

#endif
