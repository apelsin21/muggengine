#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ostream>

#include "file.hpp"

namespace mugg {
    class Filehandler {
        private:
            std::ifstream in_stream;
            std::ofstream out_stream;
        public:
            std::vector<char> ReadFile(std::string filepath);
            void WriteDataToFile(std::string filepath, std::vector<char> data);
            void AppendDataToFile(std::string filepath, std::vector<char> data);
    
            void AppendStringToFile(std::string filepath, std::string what);
    };
}

#endif
