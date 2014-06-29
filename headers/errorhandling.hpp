#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <iostream>

namespace mugg {
    namespace error {
        static void glfwErrorCallback(int error, const char* description) {
            std::cerr << "### GLFW ERROR BEGIN! ###" << std::endl;
            std::cerr << description << std::endl;
            std::cerr << "### GLFW ERROR END! ###" << std::endl;
        }
    }
}

#endif
