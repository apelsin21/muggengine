#include "window.hpp"

mugg::core::Window::Window(mugg::core::Device* p) {
    this->parent = p;

    this->open = false;
    this->fullscreen = false;
    this->maximized = false;
    this->hidden = false;

    this->width = 0;
    this->height = 0;
}
mugg::core::Window::Window(mugg::core::Device* p, int w, int h, const std::string& t) {
    this->parent = p;

    this->open = false;
    this->fullscreen = false;
    this->maximized = false;
    this->hidden = false;

    this->width = 0;
    this->height = 0;

    this->Open(w, h, t);
}
mugg::core::Window::~Window() {
    this->Close();

    if(this->sdlWindow != nullptr) {
        SDL_DestroyWindow(this->sdlWindow);
    }
}

bool mugg::core::Window::Open(int w, int h, const std::string& t) {
    if(this->open) {
        std::cout << "Reopening an already opened window!\n";
        return false;
    }
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL!\n";
        this->CheckSDLError(__LINE__);
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    this->CheckSDLError(__LINE__);
    
    this->sdlWindow = SDL_CreateWindow(t.c_str(), SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!this->sdlWindow) {
        std::cout << "Failed to create SDL Window!\n";
        this->CheckSDLError(__LINE__);
        return false;
    }

    this->CheckSDLError(__LINE__);

    this->sdlContext = SDL_GL_CreateContext(this->sdlWindow);
    this->CheckSDLError(__LINE__);

    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        std::cout << "GLEW failed to initialize!\n";
        return false;
    }

    this->open = true;
    this->width = w;
    this->height = h;
    this->title = t;
    
    return true;
}
bool mugg::core::Window::IsOpen() {
    return this->open;
}
void mugg::core::Window::Close() {
    std::cout << "Close\n";
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
    else
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

void mugg::core::Window::SetTitle(const std::string& title) {
    this->title = title;
    SDL_SetWindowTitle(this->sdlWindow, title.c_str());
}
std::string mugg::core::Window::GetTitle() {
    return this->title;
}

void mugg::core::Window::SwapBuffers() {
    SDL_GL_SwapWindow(this->sdlWindow);
}
