#ifndef ERRORHANDLING_HPP
#define ERRORHANDLING_HPP

#include <iostream>

namespace mugg {
    namespace error {
        static void glfwErrorCallback(int error, const char* description) {
            std::cerr << "GLFW error occurred! Description: \n" << std::endl;
            std::cerr << description << std::endl;
        }
    }
}

#endif
