#include "headers/window.hpp"

Window::Window(int resX = 800, int resY = 600, bool fullscreen = false, const char* title = "Default") {
    this->isFullscreen = fullscreen;
    this->resX = resX;
    this->resY = resY;
    this->title = title;

    this->recreate();

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cerr << "Err: Window:: GLEW failed to initialize!\n";
    }
}

Window::Window(int resX = 800, int resY = 600, bool fullscreen = false, const char* title = "Default", int glMajor = 3, int glMinor = 0,
               int depthbits = 24, int stencilbits = 8, int aa = 0) {
    this->isFullscreen = fullscreen;
    this->resX = resX;
    this->resY = resY;
    this->title = title;

    this->settings.majorVersion = glMajor;
    this->settings.minorVersion = glMinor;
    this->settings.depthBits = depthbits;
    this->settings.stencilBits = stencilbits;
    this->settings.antialiasingLevel = aa;

    this->recreate();
}

void Window::recreate() {
    if(this->isFullscreen) {
        this->sfWindow.create(sf::VideoMode(this->resX, this->resY), this->title, sf::Style::Fullscreen, this->settings);
    } else {
        this->sfWindow.create(sf::VideoMode(this->resX, this->resY), this->title, sf::Style::Default, this->settings);
    }
}

void Window::swapBuffers() {
    this->sfWindow.display();
}

sf::Vector2i Window::getDesktopResolution() {
	return sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
}

void Window::close() {
    this->sfWindow.close();
}

bool Window::isOpen() {
    return this->sfWindow.isOpen();
}

int Window::getResX() {
    return this->resX;
}

int Window::getResY() {
    return this->resY;
}

int Window::pollEvent() {
    while(this->sfWindow.pollEvent(this->event)) {
        if(event.type == sf::Event::Closed) {
            return 1;
        }
        if(event.type == sf::Event::Resized) {
            this->resX = this->sfWindow.getSize().x;
            this->resY = this->sfWindow.getSize().y;
            return 2;
        }
    }

    return 0;
}

void Window::setFullscreen(bool fullscreen) {
    this->isFullscreen = fullscreen;

    this->recreate();
}

bool Window::getFullscreen() {
    return this->isFullscreen;
}

void Window::setAntialiasingLevel(int aa) {
    this->settings.antialiasingLevel = aa;
}

int Window::getAntialiasingLevel() {
    return this->settings.antialiasingLevel;
}

void Window::setDepthBits(int depthBits) {
    this->settings.depthBits = depthBits;
}

int Window::getDepthBits() {
    return this->settings.depthBits;
}

void Window::setGLMajorVersion(int ver) {
    this->settings.majorVersion = ver;
}

int Window::getGLMajorVersion() {
    return this->settings.majorVersion;
}

void Window::setGLMinorVersion(int ver) {
    this->settings.minorVersion = ver;
}

int Window::getGLMinorVersion() {
    return this->settings.minorVersion;
}

void Window::setTitle(const char* title) {
	this->sfWindow.setTitle(title);
}

const char* Window::getTitle() {
	return this->title;
}
