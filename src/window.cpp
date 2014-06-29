#include "window.hpp"

mugg::Window::Window(int width, int height, const char* title) {
    this->Open(width, height, title);
}
mugg::Window::Window() {
    this->framerateLimit = 0;
    this->vsync = false;
    this->fullscreen = false;
    this->open = false;
    this->title = "";
    this->changed = false;
    this->width = 0;
    this->height = 0;
    this->posX = 0;
    this->posY = 0;
}
mugg::Window::~Window() {
    this->Close();
}

bool mugg::Window::Open(int width, int height, const char* title) {
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwSetKeyCallback(this->window, mugg::input::glfwKeyCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    GLenum error = glewInit();
    if(error != GLEW_OK) {
        std::cerr << "GLEW failed to initialize! Error:\n";
        std::cerr << glewGetErrorString(error) << std::endl;
        return false;
    }

    this->iconified = false;
    this->focused = true;
    this->fullscreen = false;
    this->title = title;
    this->width = width;
    this->height = height;
    this->open = true;

    return true;
}
void mugg::Window::Close() {
    if(this->open) {
        glfwDestroyWindow(this->window);
        this->open = false;
    }
}
bool mugg::Window::IsOpen() {
    return this->open;
}

void mugg::Window::SetPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
    
    glfwSetWindowPos(this->window, x, y);
}
int mugg::Window::GetPositionX() {
    return this->posX;
}
int mugg::Window::GetPositionY() {
    return this->posY;
}

void mugg::Window::SetSize(int width, int height) {
    glfwSetWindowSize(this->window, width, height);
}
void mugg::Window::GetSize(int &out_width, int &out_height) {
    int temp_width, temp_height;

    glfwGetWindowSize(this->window, &temp_width, &temp_height);

    out_width = temp_width;
    out_height = temp_height;
}

void mugg::Window::SetIconified(bool iconified) {
    this->iconified = true;
}
bool mugg::Window::IsIconified() {
    return this->iconified;
}

void mugg::Window::SetResolution(int width, int height) {
    this->width = width;
    this->height = height;
}
int mugg::Window::GetWidth() {
    return this->width;
}
int mugg::Window::GetHeight() {
    return this->height;
}

void mugg::Window::GetFramebufferSize(int &out_width, int &out_height) {
    if(!this->open) {
        std::cerr << "Tried to get framebuffer size of an unopened window!\n";
        out_width = 0;
        out_height = 0;
    }

    int temp_width = 0, temp_height = 0;
    glfwGetFramebufferSize(this->window, &temp_width, &temp_height);

    out_width = temp_width;
    out_height = temp_height;
}

void mugg::Window::SetFullscreen(bool fullscreen, int monitor) {
    this->fullscreen = fullscreen;
    this->changed = true;
}
bool mugg::Window::GetFullscreen() {
    return this->fullscreen;
}

void mugg::Window::SetVsync(bool enabled) {
    this->vsync = enabled;
}
bool mugg::Window::GetVsync() {
    return this->vsync;
}

void mugg::Window::SetTitle(const char* title) {
    this->title = title;
    glfwSetWindowTitle(this->window, title);
}
const char* mugg::Window::GetTitle() {
    return this->title;
}

bool mugg::Window::Recreate() {
    return true;
}

bool mugg::Window::IsFocused() {
    return this->focused;
}

bool mugg::Window::IsKeyDown(mugg::input::Key key) {
    if(glfwGetKey(this->window, (int)key) == GLFW_PRESS)
        return true;
    else
        return false;
}
bool mugg::Window::IsKeyStringDown(const char* cstring) {
    int key = GLFW_KEY_UNKNOWN;
   
    std::string string = cstring;

    if(string == "space")
    	key = GLFW_KEY_SPACE;
    if(string == "apostrophe")
    	key = GLFW_KEY_APOSTROPHE;
    if(string == "comma")
    	key = GLFW_KEY_COMMA;
    if(string == "minus")
    	key = GLFW_KEY_MINUS;
    if(string == "peroid")
    	key = GLFW_KEY_PERIOD;
    if(string == "slash")
    	key = GLFW_KEY_SLASH;
    if(string == "num_0")
    	key = GLFW_KEY_0;
    if(string == "num_1")
    	key = GLFW_KEY_1;
    if(string == "num_2")
    	key = GLFW_KEY_2;
    if(string == "num_3")
    	key = GLFW_KEY_3;
    if(string == "num_4")
    	key = GLFW_KEY_4;              
    if(string == "num_5")
    	key = GLFW_KEY_5;
    if(string == "num_6")
    	key = GLFW_KEY_6;
    if(string == "num_7")
    	key = GLFW_KEY_7;
    if(string == "num_8")
    	key = GLFW_KEY_8;
    if(string == "num_9")
    	key = GLFW_KEY_9;
    if(string == "semicolon")
    	key = GLFW_KEY_SEMICOLON;
    if(string == "equal")
    	key = GLFW_KEY_EQUAL;
    if(string == "a")
    	key = GLFW_KEY_A;
    if(string == "b")
    	key = GLFW_KEY_B;
    if(string == "c")
    	key = GLFW_KEY_C;
    if(string == "d")
    	key = GLFW_KEY_D;
    if(string == "e")
    	key = GLFW_KEY_E;
    if(string == "f")
    	key = GLFW_KEY_F;
    if(string == "g")
    	key = GLFW_KEY_G;
    if(string == "h")
    	key = GLFW_KEY_H;
    if(string == "i")
    	key = GLFW_KEY_I;
    if(string == "j")
    	key = GLFW_KEY_J;
    if(string == "k")
    	key = GLFW_KEY_K;
    if(string == "l")
    	key = GLFW_KEY_L;
    if(string == "m")
    	key = GLFW_KEY_M;
    if(string == "n")
    	key = GLFW_KEY_N;
    if(string == "o")
    	key = GLFW_KEY_O;
    if(string == "p")
    	key = GLFW_KEY_P;
    if(string == "q")
    	key = GLFW_KEY_Q;
    if(string == "r")
    	key = GLFW_KEY_R;
    if(string == "s")
    	key = GLFW_KEY_S;
    if(string == "t")
    	key = GLFW_KEY_T;
    if(string == "u")
    	key = GLFW_KEY_U;
    if(string == "v")
    	key = GLFW_KEY_V;
    if(string == "w")
    	key = GLFW_KEY_W;
    if(string == "x")
    	key = GLFW_KEY_X;
    if(string == "y")
    	key = GLFW_KEY_Y;
    if(string == "z")
    	key = GLFW_KEY_Z;
    if(string == "left_bracket")
    	key = GLFW_KEY_LEFT_BRACKET;
    if(string == "backslash")
    	key = GLFW_KEY_BACKSLASH;
    if(string == "right_bracket")
    	key = GLFW_KEY_RIGHT_BRACKET;
    if(string == "grave_accent")
    	key = GLFW_KEY_GRAVE_ACCENT;
    if(string == "world_1")
    	key = GLFW_KEY_WORLD_1;
    if(string == "world_2")
    	key = GLFW_KEY_WORLD_2;
    if(string == "escape")
    	key = GLFW_KEY_ESCAPE;
    if(string == "enter")
    	key = GLFW_KEY_ENTER;
    if(string == "tab")
    	key = GLFW_KEY_TAB;
    if(string == "backspace")
    	key = GLFW_KEY_BACKSPACE;
    if(string == "insert")
    	key = GLFW_KEY_INSERT;
    if(string == "delete")
    	key = GLFW_KEY_DELETE;
    if(string == "right")
    	key = GLFW_KEY_RIGHT;
    if(string == "left")
    	key = GLFW_KEY_LEFT;
    if(string == "down")
    	key = GLFW_KEY_DOWN;
    if(string == "up")
    	key = GLFW_KEY_UP;
    if(string == "page_up")
    	key = GLFW_KEY_PAGE_UP;
    if(string == "page_down")
    	key = GLFW_KEY_PAGE_DOWN;
    if(string == "home")
    	key = GLFW_KEY_HOME;
    if(string == "end")
    	key = GLFW_KEY_END;
    if(string == "caps_lock")
    	key = GLFW_KEY_CAPS_LOCK;
    if(string == "scroll_lock")
    	key = GLFW_KEY_SCROLL_LOCK;
    if(string == "num_lock")
    	key = GLFW_KEY_NUM_LOCK;
    if(string == "print_screen")
    	key = GLFW_KEY_PRINT_SCREEN;
    if(string == "pause")
    	key = GLFW_KEY_PAUSE;
    if(string == "f1")
    	key = GLFW_KEY_F1;
    if(string == "f2")
    	key = GLFW_KEY_F2;
    if(string == "f3")
    	key = GLFW_KEY_F3;
    if(string == "f4")
    	key = GLFW_KEY_F4;
    if(string == "f5")
    	key = GLFW_KEY_F5;
    if(string == "f6")
    	key = GLFW_KEY_F6;
    if(string == "f7")
    	key = GLFW_KEY_F7;
    if(string == "f8")
    	key = GLFW_KEY_F8;
    if(string == "f9")
    	key = GLFW_KEY_F9;
    if(string == "f10")
    	key = GLFW_KEY_F10;
    if(string == "f11")
    	key = GLFW_KEY_F11;
    if(string == "f12")
    	key = GLFW_KEY_F12;
    if(string == "f13")
    	key = GLFW_KEY_F13;
    if(string == "f14")
    	key = GLFW_KEY_F14;
    if(string == "f15")
    	key = GLFW_KEY_F15;
    if(string == "f16")
    	key = GLFW_KEY_F16;
    if(string == "f17")
    	key = GLFW_KEY_F17;
    if(string == "f18")
    	key = GLFW_KEY_F18;
    if(string == "f19")
    	key = GLFW_KEY_F19;
    if(string == "f20")
    	key = GLFW_KEY_F20;
    if(string == "f21")
    	key = GLFW_KEY_F21;
    if(string == "f22")
    	key = GLFW_KEY_F22;
    if(string == "f23")
    	key = GLFW_KEY_F23;
    if(string == "f24")
    	key = GLFW_KEY_F24;
    if(string == "f25")
    	key = GLFW_KEY_F25;
    if(string == "kp_0")
    	key = GLFW_KEY_KP_0;
    if(string == "kp_1")
    	key = GLFW_KEY_KP_1;
    if(string == "kp_2")
    	key = GLFW_KEY_KP_2;
    if(string == "kp_3")
    	key = GLFW_KEY_KP_3;
    if(string == "kp_4")
    	key = GLFW_KEY_KP_4;
    if(string == "kp_5")
    	key = GLFW_KEY_KP_5;
    if(string == "kp_6")
    	key = GLFW_KEY_KP_6;
    if(string == "kp_7")
    	key = GLFW_KEY_KP_7;
    if(string == "kp_8")
    	key = GLFW_KEY_KP_8;
    if(string == "kp_9")
    	key = GLFW_KEY_KP_9;
    if(string == "kp_decimal")
    	key = GLFW_KEY_KP_DECIMAL;
    if(string == "kp_divide")
    	key = GLFW_KEY_KP_DIVIDE;
    if(string == "kp_multiply")
    	key = GLFW_KEY_KP_MULTIPLY;
    if(string == "kp_subtract")
    	key = GLFW_KEY_KP_SUBTRACT;
    if(string == "kp_add")
    	key = GLFW_KEY_KP_ADD;
    if(string == "kp_enter")
    	key = GLFW_KEY_KP_ENTER;
    if(string == "kp_equal")
    	key = GLFW_KEY_KP_EQUAL;
    if(string == "left_shift")
    	key = GLFW_KEY_LEFT_SHIFT;
    if(string == "left_control")
    	key = GLFW_KEY_LEFT_CONTROL;
    if(string == "left_alt")
    	key = GLFW_KEY_LEFT_ALT;
    if(string == "left_super")
    	key = GLFW_KEY_LEFT_SUPER;
    if(string == "right_shift")
    	key = GLFW_KEY_RIGHT_SHIFT;
    if(string == "right_control")
    	key = GLFW_KEY_RIGHT_CONTROL;
    if(string == "right_alt")
    	key = GLFW_KEY_RIGHT_ALT;
    if(string == "right_super")
    	key = GLFW_KEY_RIGHT_SUPER;
    if(string == "menu")
    	key = GLFW_KEY_MENU;
    if(string == "last")
        key = GLFW_KEY_LAST;

    if(key != GLFW_KEY_UNKNOWN && glfwGetKey(this->window, key) == GLFW_PRESS) {
        return true;
    }

    return false;
}
mugg::input::Key GetLastPressedKey() {
    return mugg::input::lastPressedKey;
}

void mugg::Window::ReactToEvents() {
    if(glfwGetWindowAttrib(this->window, GLFW_FOCUSED))
        this->focused = true;
    else
        this->focused = false;

    if(glfwGetWindowAttrib(this->window, GLFW_ICONIFIED))
        this->iconified = true;
    else
        this->iconified = false;
    
    if(glfwGetWindowAttrib(this->window, GLFW_VISIBLE))
        this->visible = true;
    else
        this->visible = false;
}

void mugg::Window::SwapBuffers() {
    if(this->open) {
        this->ReactToEvents();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}
