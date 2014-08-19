#include "window.hpp"

mugg::core::Window::Window(mugg::core::Engine* p) {
    this->parent = p;

    if(SDL_WasInit(SDL_INIT_VIDEO) != SDL_INIT_VIDEO) {
        if(SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL failed to initialize! Error:\n";
            this->CheckSDLError(__LINE__);
        }
    }

    this->open = false;
    this->fullscreen = false;
    this->maximized = false;
    this->hidden = false;
    this->focus = false;

    this->width = 0;
    this->height = 0;
    this->windowID = 0;

    this->Open(800, 600, "MuggEngine Window");
}
mugg::core::Window::~Window() {
}

bool mugg::core::Window::HasFocus() {
    return this->focus;
}

bool mugg::core::Window::Open(int w, int h, const std::string& t) {
    this->width = w;
    this->height = h;
    this->title = t;
    
    if(this->open) {
        std::cout << "Reopening an already opened window!\n";
        return false;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    this->CheckSDLError(__LINE__);
    
    this->sdlWindow = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!this->sdlWindow) {
        std::cout << "Failed to create SDL Window!\n";
        this->CheckSDLError(__LINE__);
        return false;
    }

    this->CheckSDLError(__LINE__);

    this->sdlContext = SDL_GL_CreateContext(this->sdlWindow);
    this->CheckSDLError(__LINE__);

    glewExperimental = true;
    GLenum error = glewInit();
    if(error != GLEW_OK) {
        std::cout << "GLEW failed to initialize! Error:\n";
        std::cout << glewGetErrorString(error);
        return false;
    }

    this->windowID = SDL_GetWindowID(this->sdlWindow);
    this->open = true;
    
    return true;
}
bool mugg::core::Window::IsOpen() {
    return this->open;
}
void mugg::core::Window::Close() {
    this->open = false;
    
    SDL_GL_DeleteContext(this->sdlContext);
    if(this->sdlWindow != nullptr)
        SDL_DestroyWindow(this->sdlWindow);
}

void mugg::core::Window::Restore() {
    SDL_RestoreWindow(this->sdlWindow);
}
void mugg::core::Window::Maximize() {
    SDL_MaximizeWindow(this->sdlWindow);
    this->maximized = true;
}
void mugg::core::Window::Minimize() {
    SDL_MinimizeWindow(this->sdlWindow);
    this->maximized = false;
}
bool mugg::core::Window::IsMaximized() {
    return this->maximized;
}

void mugg::core::Window::SetPosition(int x, int y) {
    SDL_SetWindowPosition(this->sdlWindow, x, y);
}
void mugg::core::Window::SetPositionX(int x) {
    SDL_SetWindowPosition(this->sdlWindow, x, this->GetPositionY());
}
void mugg::core::Window::SetPositionY(int y) {
    SDL_SetWindowPosition(this->sdlWindow, this->GetPositionX(), y);
}
int mugg::core::Window::GetPositionX() {
    int x, y;

    SDL_GetWindowPosition(this->sdlWindow, &x, &y);

    return x;
}
int mugg::core::Window::GetPositionY() {
    int x, y;

    SDL_GetWindowPosition(this->sdlWindow, &x, &y);

    return y;
}

void mugg::core::Window::CheckSDLError(int line = -1) {
    const char* error = SDL_GetError();

    if(*error != '\0') {
        std::cout << "SDL Error: " << error << std::endl;

        if(line != -1) {
            std::cout << " + line " << line << std::endl;
        }

        SDL_ClearError();
    }
}

void mugg::core::Window::SetResolution(int w, int h) {
    this->width = w;
    this->height = h;

    if(this->open) {
        SDL_SetWindowSize(this->sdlWindow, w, h);
        this->CheckSDLError(__LINE__);
    }
}
void mugg::core::Window::SetWidth(int w) {
    this->width = w;
    
    if(this->open) {
        SDL_SetWindowSize(this->sdlWindow, w, this->height);
        this->CheckSDLError(__LINE__);
    }
}
void mugg::core::Window::SetHeight(int h) {
    this->height = h;
    
    if(this->open) {
        SDL_SetWindowSize(this->sdlWindow, this->width, h);
        this->CheckSDLError(__LINE__);
    }
}
int mugg::core::Window::GetWidth() {
    return this->width;
}
int mugg::core::Window::GetHeight() {
    return this->height;
}

void mugg::core::Window::SetSwapInterval(int i) {
    if(this->open) {
        SDL_GL_SetSwapInterval(i);
        this->CheckSDLError(__LINE__);
    }
}
int mugg::core::Window::GetSwapInterval() {
    if(this->open)
        return SDL_GL_GetSwapInterval();
    
    return 0;
}

bool mugg::core::Window::SetClipboardText(const std::string& data) {
    if(SDL_SetClipboardText(data.c_str()) == 0)
        return true;
    else {
        this->CheckSDLError(__LINE__);
        return false;
    }
}
bool mugg::core::Window::HasClipboardText() {
    if(SDL_HasClipboardText())
        return true;
    else
        return false;
}
std::string mugg::core::Window::GetClipboardText() {
    std::string text = SDL_GetClipboardText();
    this->CheckSDLError(__LINE__);
    return text;
}

bool mugg::core::Window::SetFullscreen() {
    if(SDL_SetWindowFullscreen(this->sdlWindow, SDL_WINDOW_FULLSCREEN) == 0) {
        this->fullscreen = true;
        return true;
    }

    this->CheckSDLError(__LINE__);
    return false;
}
bool mugg::core::Window::SetBorderlessFullscreen() {
    if(SDL_SetWindowFullscreen(this->sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) == 0) {
        this->fullscreen = true;
        return true;
    }

    this->CheckSDLError(__LINE__);
    return false;
}
bool mugg::core::Window::SetWindowed() {
    if(SDL_SetWindowFullscreen(this->sdlWindow, 0) == 0) {
        this->fullscreen = false;
        return true;
    }

    this->CheckSDLError(__LINE__);
    return false;
}
bool mugg::core::Window::IsFullscreen() {
    return this->fullscreen;
}

void mugg::core::Window::Show() {
    this->hidden = false;
    SDL_HideWindow(this->sdlWindow);
}
void mugg::core::Window::Hide() {
    this->hidden = true;
    SDL_ShowWindow(this->sdlWindow);
}
bool mugg::core::Window::IsHidden() {
    return this->hidden;
}

void mugg::core::Window::SetTitle(const std::string& in_title) {
    this->title = in_title;
    SDL_SetWindowTitle(this->sdlWindow, this->title.c_str());
}
std::string mugg::core::Window::GetTitle() {
    return this->title;
}

void mugg::core::Window::ShowCursor() {
    SDL_ShowCursor(1);
}
void mugg::core::Window::HideCursor() {
    SDL_ShowCursor(0);
}
bool mugg::core::Window::IsCursorHidden() {
    if(SDL_ShowCursor(-1) == 1) {
        return false;
    } else {
        return true;
    }
}

void mugg::core::Window::CheckForEvents() {
    while(SDL_PollEvent(&this->event)) {
        if(this->event.window.windowID == this->windowID) {
            switch(this->event.window.event) {
                case SDL_WINDOWEVENT_SHOWN:
                    this->hidden = false;
                    break;
                case SDL_WINDOWEVENT_HIDDEN:
                    this->hidden = true;
                    break;
                case SDL_WINDOWEVENT_RESIZED:
                    this->width = this->event.window.data1;
                    this->height = this->event.window.data2;
                    glViewport(0, 0, this->width, this->height);
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    this->maximized = false;
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                    this->maximized = true;
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    this->focus = true;
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    this->focus = false;
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    this->Close();
                    break;
                default:
                    break;
            }
        }
    }
}

void mugg::core::Window::SwapBuffers() {
    if(this->open) {
        this->CheckForEvents();
        SDL_GL_SwapWindow(this->sdlWindow);
    }
}
