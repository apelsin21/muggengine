#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>

#include "keydefs.hpp"
#include "errorhandling.hpp"

namespace mugg {
    namespace core {
        class Device;
        
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void closeCallback(GLFWwindow* window);
    
        class Window {
            private:
                GLFWwindow* window;
                int width, height, posX, posY;
                bool fullscreen, open, focused, iconified, visible;
                int swapInterval;
                std::string title;
                bool changed; //True if window needs to recreate, false if not
   
                mugg::core::Device* creator;
            public:
                Window(mugg::core::Device*);
                ~Window();
    
                virtual bool Open(int width, int height, std::string title);
                virtual bool IsOpen();
                virtual void Close();
                
                virtual void SetPosition(int x, int y);
                virtual int GetPositionX();
                virtual int GetPositionY();
    
                virtual void SetSize(int width, int height);
                virtual void GetSize(int &out_width, int &out_height);
    
                virtual void SetResolution(int width, int height);
                virtual int GetWidth();
                virtual int GetHeight();
                
                virtual void GetFramebufferSize(int &out_width, int &out_height);
    
                virtual void SetFullscreen(bool fullscreen);
                virtual bool GetFullscreen();
    
                virtual void SetIconified(bool iconified);
                virtual bool IsIconified();
    
                virtual void SetSwapInterval(int interval);
                virtual int GetSwapInterval();
    
                virtual bool IsFocused();
    
                virtual void SetTitle(std::string);
                virtual std::string GetTitle();
    
                virtual bool Recreate();
    
                virtual void PollEvents();
                virtual void ReactToEvents();            
    
                virtual std::string GetClipboard();
                virtual void SetClipboard(std::string string);
    
                virtual bool IsKeyDown(mugg::input::Key key);
                virtual bool IsKeyStringDown(std::string string);
    
                virtual void SwapBuffers();
        };
    }
}

#endif
