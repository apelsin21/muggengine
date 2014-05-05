#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>

#include "vector2i.hpp"

namespace mugg {
    class Window {
    private:
        void framebuffer_size_callback();
        GLFWwindow* window;
        mugg::Vector2i resolution, position;
        bool fullscreen, open;
    public:
        Window();
        ~Window();

        void SetWidth(int width);
        int GetWidth();

        void SetHeight(int height);
        int GetHeight();

        void SetResolution(mugg::Vector2i what);
        mugg::Vector2i GetResolution();

        void SetPositionX(int posx);
        int GetPositionX();

        void SetPositionY(int posy);
        int GetPositionY();

        void SetPosition(mugg::Vector2i what);
        mugg::Vector2i GetPosition();

        void SetFullscreen(bool what);
        bool GetFullscreen();

        void SetHidden(bool what);
        bool GetHidden();

        void SwapBuffers();
    };
}

#endif
