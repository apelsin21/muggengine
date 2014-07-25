#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "keydefs.hpp"
#include "errorhandling.hpp"

namespace mugg {
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void closeCallback(GLFWwindow* window);

    class Window {
        private:
            GLFWwindow* window;
            int width, height, posX, posY;
            bool fullscreen, open, focused, iconified, visible;
            int swapInterval;
            const char* title;
            bool changed; //True if window needs to recreate, false if not
        public:
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

            void SetFullscreen(bool fullscreen);
            bool GetFullscreen();

            void SetIconified(bool iconified);
            bool IsIconified();

            void SetSwapInterval(int interval);
            int GetSwapInterval();

            void SetFramerateLimit(int limit);
            int GetFramerateLimit();

            bool IsFocused();

            void SetTitle(const char* title);
            const char* GetTitle();

            //Sets new resolution, changes from fullscreen, etc.
            //Returns true on success, else false
            bool Recreate();

            void PollEvents();
            void ReactToEvents();            

            const char* GetClipboard();
            void SetClipboard(const char* string);

            bool IsKeyDown(mugg::input::Key key);
            bool IsKeyStringDown(const char* string);
            mugg::input::Key GetLastPressedKey();

            //Swaps front and back buffers
            void SwapBuffers();
    };
}

#endif
