#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "context.hpp"
#include "log.hpp"

namespace mugg {
    class Window {
    private:
        GLFWwindow* window;
        bool fullscreen, open, created, focused, minimized;
        glm::vec2 resolution, position;
        std::string title;

        static void ErrorCallback(int error, const char* message);
    public:
        Window();
        ~Window();

        void Create(std::string title, glm::vec2 resolution, glm::vec2 position);
        bool GetIsCreated();

        void Recreate();

        void Close();
        bool IsOpen();

        void SetWidth(int width);
        int GetWidth();

        void SetHeight(int height);
        int GetHeight();

        void SetResolution(glm::vec2 what);
        glm::vec2 GetResolution();

        void SetPositionX(int posx);
        int GetPositionX();

        void SetPositionY(int posy);
        int GetPositionY();

        void SetPosition(glm::vec2 what);
        glm::vec2 GetPosition();

        void SetFullscreen(bool what);
        bool GetFullscreen();

        void SetHidden(bool what);
        bool GetHidden();

        void SetCurrent(bool what);
        bool GetCurrent();

        void SwapBuffers();
    };
}

#endif
