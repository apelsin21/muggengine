#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "keydefs.hpp"

namespace mugg {
    namespace core {
        class Device;
    
        class Window {
            private:
                int width, height;
                std::string title;
                bool open, fullscreen, maximized, hidden, focus;
                
                SDL_Event event;
                SDL_Window* sdlWindow;
                SDL_GLContext sdlContext;
                Uint32 windowID;

                mugg::core::Device* parent;

                void CheckSDLError(int);
                void CheckForEvents();
            public:
                Window(mugg::core::Device*);
                Window(mugg::core::Device*, int, int, const std::string&);
                ~Window();

                virtual bool HasFocus();

                virtual bool Open(int, int, const std::string&);
                virtual bool IsOpen();
                virtual void Close();

                virtual void Restore();
                virtual void Maximize();
                virtual void Minimize();
                virtual bool IsMaximized();

                virtual void SetResolution(int, int);
                virtual void SetWidth(int);
                virtual void SetHeight(int);
                virtual int GetWidth();
                virtual int GetHeight();

                virtual void SetPosition(int, int);
                virtual void SetPositionX(int);
                virtual void SetPositionY(int);
                virtual int GetPositionX();
                virtual int GetPositionY();

                virtual void SetSwapInterval(int);
                virtual int GetSwapInterval();

                virtual void Show();
                virtual void Hide();
                virtual bool IsHidden();

                virtual bool SetClipboardText(const std::string&);
                virtual bool HasClipboardText();
                virtual std::string GetClipboardText();

                virtual bool SetFullscreen();
                virtual bool SetBorderlessFullscreen();
                virtual bool SetWindowed();
                virtual bool IsFullscreen();

                virtual void SetTitle(const std::string&);
                virtual std::string GetTitle();

                virtual void ShowCursor();
                virtual void HideCursor();
                virtual bool IsCursorHidden();

                virtual void SwapBuffers();
        };
    }
}

#endif
