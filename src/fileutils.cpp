#include "fileutils.hpp"

bool mugg::io::LoadTextFromFile(const char* filepath, std::string &outString) {
    std::string data;
    std::ifstream textStream(filepath, std::ios::in);

    if(textStream.is_open()) {
        std::string line = "";

        while(std::getline(textStream, line)) {
            data += "\n" + line;
        }

        textStream.close();
    } else {
        return false;
    }

    outString = data;

    return true;
}
