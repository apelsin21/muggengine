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
        class Engine;
    
        class Window {
            private:
                int width, height;
                std::string title;
                bool open, fullscreen, maximized, hidden, focus;
                
                SDL_Event event;
                SDL_Window* sdlWindow;
                SDL_GLContext sdlContext;
                Uint32 windowID;

                mugg::core::Engine* parent;

                void CheckSDLError(int);
                void CheckForEvents();
            public:
                Window(mugg::core::Engine*);
                Window(mugg::core::Engine*, int, int, const std::string&);
                ~Window();

                bool HasFocus();

                bool Open(int, int, const std::string&);
                bool IsOpen();
                void Close();

                void Restore();
                void Maximize();
                void Minimize();
                bool IsMaximized();

                void SetResolution(int, int);
                void SetWidth(int);
                void SetHeight(int);
                int GetWidth();
                int GetHeight();

                void SetPosition(int, int);
                void SetPositionX(int);
                void SetPositionY(int);
                int GetPositionX();
                int GetPositionY();

                void SetSwapInterval(int);
                int GetSwapInterval();

                void Show();
                void Hide();
                bool IsHidden();

                bool SetClipboardText(const std::string&);
                bool HasClipboardText();
                std::string GetClipboardText();

                bool SetFullscreen();
                bool SetBorderlessFullscreen();
                bool SetWindowed();
                bool IsFullscreen();

                void SetTitle(const std::string&);
                std::string GetTitle();

                void ShowCursor();
                void HideCursor();
                bool IsCursorHidden();

                void SwapBuffers();
        };
    }
}

#endif
