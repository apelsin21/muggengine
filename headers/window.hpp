#ifndef WINDOW_HPP
#define WINDOW_HPP

namespace mugg {
    class Window {
    private:
        SDL_Window* window;
    public:
        Window();
        ~Window();
    };
}

#endif
