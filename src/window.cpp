#include "window.hpp"

static void mugg::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

mugg::Window::Window(int width, int height, const char* title) {
    //Numeric values
    this->width = 0;
    this->height = 0;
    this->posX = 0;
    this->posY = 0;
    this->swapInterval = 0;

    //Strings
    this->title = "";

    //Boolean values
    this->fullscreen = false;
    this->changed = false;
    this->open = false;
    this->focused = false;
    this->iconified = false;
    this->visible = false;
    
    this->Open(width, height, title);
}
mugg::Window::Window() {
    //Numeric values
    this->width = 0;
    this->height = 0;
    this->posX = 0;
    this->posY = 0;
    this->swapInterval = 0;
    
    //Strings
    this->title = "";

    //Boolean values
    this->fullscreen = false;
    this->changed = false;
    this->open = false;
    this->focused = false;
    this->iconified = false;
    this->visible = false;
}
mugg::Window::~Window() {
    this->Close();

    if(this->width != 0 || this->height != 0)
        glfwTerminate();
}

bool mugg::Window::Open(int width, int height, const char* title) {
    glfwSetErrorCallback(mugg::error::glfwErrorCallback);

    if(!glfwInit()) {
        std::cerr << "GLFW failed to initialize!\n";
        return false;
    }
    
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if(!window) {
        std::cerr << "Failed to create a GLFW window!\n";
        glfwTerminate();
        return false;
    }

    glfwSetKeyCallback(this->window, mugg::input::glfwKeyCallback);
    glfwSetFramebufferSizeCallback(this->window, mugg::framebufferSizeCallback);

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
    this->open = false;
    glfwSetWindowShouldClose(this->window, true);
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
    this->changed = true;
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

void mugg::Window::SetFullscreen(bool fullscreen) {
    if(fullscreen) {
        this->window = glfwCreateWindow(this->width, this->height, this->title, glfwGetPrimaryMonitor(), NULL);
        this->changed = true;
        this->fullscreen = fullscreen;
    } else {
        this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
        this->fullscreen = fullscreen;
    }
}
bool mugg::Window::GetFullscreen() {
    return this->fullscreen;
}

void mugg::Window::SetSwapInterval(int interval) {
    this->swapInterval = interval;
}
int mugg::Window::GetSwapInterval() {
    return this->swapInterval;
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
    else if(string == "apostrophe")
    	key = GLFW_KEY_APOSTROPHE;
    else if(string == "comma")
    	key = GLFW_KEY_COMMA;
    else if(string == "minus")
    	key = GLFW_KEY_MINUS;
    else if(string == "peroid")
    	key = GLFW_KEY_PERIOD;
    else if(string == "slash")
    	key = GLFW_KEY_SLASH;
    else if(string == "num_0")
    	key = GLFW_KEY_0;
    else if(string == "num_1")
    	key = GLFW_KEY_1;
    else if(string == "num_2")
    	key = GLFW_KEY_2;
    else if(string == "num_3")
    	key = GLFW_KEY_3;
    else if(string == "num_4")
    	key = GLFW_KEY_4;              
    else if(string == "num_5")
    	key = GLFW_KEY_5;
    else if(string == "num_6")
    	key = GLFW_KEY_6;
    else if(string == "num_7")
    	key = GLFW_KEY_7;
    else if(string == "num_8")
    	key = GLFW_KEY_8;
    else if(string == "num_9")
    	key = GLFW_KEY_9;
    else if(string == "semicolon")
    	key = GLFW_KEY_SEMICOLON;
    else if(string == "equal")
    	key = GLFW_KEY_EQUAL;
    else if(string == "a")
    	key = GLFW_KEY_A;
    else if(string == "b")
    	key = GLFW_KEY_B;
    else if(string == "c")
    	key = GLFW_KEY_C;
    else if(string == "d")
    	key = GLFW_KEY_D;
    else if(string == "e")
    	key = GLFW_KEY_E;
    else if(string == "f")
    	key = GLFW_KEY_F;
    else if(string == "g")
    	key = GLFW_KEY_G;
    else if(string == "h")
    	key = GLFW_KEY_H;
    else if(string == "i")
    	key = GLFW_KEY_I;
    else if(string == "j")
    	key = GLFW_KEY_J;
    else if(string == "k")
    	key = GLFW_KEY_K;
    else if(string == "l")
    	key = GLFW_KEY_L;
    else if(string == "m")
    	key = GLFW_KEY_M;
    else if(string == "n")
    	key = GLFW_KEY_N;
    else if(string == "o")
    	key = GLFW_KEY_O;
    else if(string == "p")
    	key = GLFW_KEY_P;
    else if(string == "q")
    	key = GLFW_KEY_Q;
    else if(string == "r")
    	key = GLFW_KEY_R;
    else if(string == "s")
    	key = GLFW_KEY_S;
    else if(string == "t")
    	key = GLFW_KEY_T;
    else if(string == "u")
    	key = GLFW_KEY_U;
    else if(string == "v")
    	key = GLFW_KEY_V;
    else if(string == "w")
    	key = GLFW_KEY_W;
    else if(string == "x")
    	key = GLFW_KEY_X;
    else if(string == "y")
    	key = GLFW_KEY_Y;
    else if(string == "z")
    	key = GLFW_KEY_Z;
    else if(string == "left_bracket")
    	key = GLFW_KEY_LEFT_BRACKET;
    else if(string == "backslash")
    	key = GLFW_KEY_BACKSLASH;
    else if(string == "right_bracket")
    	key = GLFW_KEY_RIGHT_BRACKET;
    else if(string == "grave_accent")
    	key = GLFW_KEY_GRAVE_ACCENT;
    else if(string == "world_1")
    	key = GLFW_KEY_WORLD_1;
    else if(string == "world_2")
    	key = GLFW_KEY_WORLD_2;
    else if(string == "escape")
    	key = GLFW_KEY_ESCAPE;
    else if(string == "enter")
    	key = GLFW_KEY_ENTER;
    else if(string == "tab")
    	key = GLFW_KEY_TAB;
    else if(string == "backspace")
    	key = GLFW_KEY_BACKSPACE;
    else if(string == "insert")
    	key = GLFW_KEY_INSERT;
    else if(string == "delete")
    	key = GLFW_KEY_DELETE;
    else if(string == "right")
    	key = GLFW_KEY_RIGHT;
    else if(string == "left")
    	key = GLFW_KEY_LEFT;
    else if(string == "down")
    	key = GLFW_KEY_DOWN;
    else if(string == "up")
    	key = GLFW_KEY_UP;
    else if(string == "page_up")
    	key = GLFW_KEY_PAGE_UP;
    else if(string == "page_down")
    	key = GLFW_KEY_PAGE_DOWN;
    else if(string == "home")
    	key = GLFW_KEY_HOME;
    else if(string == "end")
    	key = GLFW_KEY_END;
    else if(string == "caps_lock")
    	key = GLFW_KEY_CAPS_LOCK;
    else if(string == "scroll_lock")
    	key = GLFW_KEY_SCROLL_LOCK;
    else if(string == "num_lock")
    	key = GLFW_KEY_NUM_LOCK;
    else if(string == "print_screen")
    	key = GLFW_KEY_PRINT_SCREEN;
    else if(string == "pause")
    	key = GLFW_KEY_PAUSE;
    else if(string == "f1")
    	key = GLFW_KEY_F1;
    else if(string == "f2")
    	key = GLFW_KEY_F2;
    else if(string == "f3")
    	key = GLFW_KEY_F3;
    else if(string == "f4")
    	key = GLFW_KEY_F4;
    else if(string == "f5")
    	key = GLFW_KEY_F5;
    else if(string == "f6")
    	key = GLFW_KEY_F6;
    else if(string == "f7")
    	key = GLFW_KEY_F7;
    else if(string == "f8")
    	key = GLFW_KEY_F8;
    else if(string == "f9")
    	key = GLFW_KEY_F9;
    else if(string == "f10")
    	key = GLFW_KEY_F10;
    else if(string == "f11")
    	key = GLFW_KEY_F11;
    else if(string == "f12")
    	key = GLFW_KEY_F12;
    else if(string == "f13")
    	key = GLFW_KEY_F13;
    else if(string == "f14")
    	key = GLFW_KEY_F14;
    else if(string == "f15")
    	key = GLFW_KEY_F15;
    else if(string == "f16")
    	key = GLFW_KEY_F16;
    else if(string == "f17")
    	key = GLFW_KEY_F17;
    else if(string == "f18")
    	key = GLFW_KEY_F18;
    else if(string == "f19")
    	key = GLFW_KEY_F19;
    else if(string == "f20")
    	key = GLFW_KEY_F20;
    else if(string == "f21")
    	key = GLFW_KEY_F21;
    else if(string == "f22")
    	key = GLFW_KEY_F22;
    else if(string == "f23")
    	key = GLFW_KEY_F23;
    else if(string == "f24")
    	key = GLFW_KEY_F24;
    else if(string == "f25")
    	key = GLFW_KEY_F25;
    else if(string == "kp_0")
    	key = GLFW_KEY_KP_0;
    else if(string == "kp_1")
    	key = GLFW_KEY_KP_1;
    else if(string == "kp_2")
    	key = GLFW_KEY_KP_2;
    else if(string == "kp_3")
    	key = GLFW_KEY_KP_3;
    else if(string == "kp_4")
    	key = GLFW_KEY_KP_4;
    else if(string == "kp_5")
    	key = GLFW_KEY_KP_5;
    else if(string == "kp_6")
    	key = GLFW_KEY_KP_6;
    else if(string == "kp_7")
    	key = GLFW_KEY_KP_7;
    else if(string == "kp_8")
    	key = GLFW_KEY_KP_8;
    else if(string == "kp_9")
    	key = GLFW_KEY_KP_9;
    else if(string == "kp_decimal")
    	key = GLFW_KEY_KP_DECIMAL;
    else if(string == "kp_divide")
    	key = GLFW_KEY_KP_DIVIDE;
    else if(string == "kp_multiply")
    	key = GLFW_KEY_KP_MULTIPLY;
    else if(string == "kp_subtract")
    	key = GLFW_KEY_KP_SUBTRACT;
    else if(string == "kp_add")
    	key = GLFW_KEY_KP_ADD;
    else if(string == "kp_enter")
    	key = GLFW_KEY_KP_ENTER;
    else if(string == "kp_equal")
    	key = GLFW_KEY_KP_EQUAL;
    else if(string == "left_shift")
    	key = GLFW_KEY_LEFT_SHIFT;
    else if(string == "left_control")
    	key = GLFW_KEY_LEFT_CONTROL;
    else if(string == "left_alt")
    	key = GLFW_KEY_LEFT_ALT;
    else if(string == "left_super")
    	key = GLFW_KEY_LEFT_SUPER;
    else if(string == "right_shift")
    	key = GLFW_KEY_RIGHT_SHIFT;
    else if(string == "right_control")
    	key = GLFW_KEY_RIGHT_CONTROL;
    else if(string == "right_alt")
    	key = GLFW_KEY_RIGHT_ALT;
    else if(string == "right_super")
    	key = GLFW_KEY_RIGHT_SUPER;
    else if(string == "menu")
    	key = GLFW_KEY_MENU;
    else if(string == "last")
        key = GLFW_KEY_LAST;
    else {
        std::cout << "Checked for keypress that doesn't exist!\n";
        return false;
    }

    if(key != GLFW_KEY_UNKNOWN && glfwGetKey(this->window, key) == GLFW_PRESS) {
        return true;
    }

    return false;
}
mugg::input::Key GetLastPressedKey() {
    return mugg::input::lastPressedKey;
}

void mugg::Window::PollEvents() {
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

void mugg::Window::ReactToEvents() {
}

const char* mugg::Window::GetClipboard() {
    if(glfwGetClipboardString(this->window) == NULL)
        return "";
    else
        return glfwGetClipboardString(this->window);
}
void mugg::Window::SetClipboard(const char* string) {
    glfwSetClipboardString(this->window, string);
}

void mugg::Window::SwapBuffers() {
    if(this->open) {
        this->PollEvents();
        this->ReactToEvents();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}
