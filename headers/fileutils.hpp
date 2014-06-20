#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <string>
#include <fstream>
#include <iostream>

namespace mugg {
    namespace io {
        bool LoadTextFromFile(const char* filepath, std::string &outString);
        bool LoadTextFromFile(const char* filepath, const char* &outString);
    }
}

#endif
