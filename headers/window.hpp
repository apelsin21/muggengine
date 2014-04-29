#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Window.hpp>

#include <iostream>

class Window {
private:
    sf::Event event;
    sf::ContextSettings settings;
    sf::Window sfWindow;
    bool isFullscreen;
    int resX, resY;
    const char* title;
public:
    Window(int resX, int resY, bool fullscreen, const char* title);
    Window(int resX, int resY, bool fullscreen, const char* title, int glMajor, int glMinor,
        int depthbits, int stencilbits, int aa);
    void swapBuffers();
    bool isOpen();
    int getResX();
    int getResY();
    void close();
    //Returns 0 if no event, 1 for window close event, 2 for resize event, etc.
    int pollEvent();
    void setFullscreen(bool fullscreen);
    bool getFullscreen();

    void setAntialiasingLevel(int aa);
    int getAntialiasingLevel();

    void setDepthBits(int depthBits);
    int getDepthBits();

    void setStencilBits(int stencilBits);
    int getStencilBits();

    void setGLMajorVersion(int ver);
    int getGLMajorVersion();

    void setGLMinorVersion(int ver);
    int getGLMinorVersion();
	
	void setTitle(const char* title);
	const char* getTitle();

	sf::Vector2i getDesktopResolution();

    void recreate();
};

#endif // WINDOW_HPP
