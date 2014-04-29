#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
#include <ctime>

namespace mugg {
    enum LOG_LEVEL {
        FATAL_ERROR,
        ERROR,
        WARNING,
        DEBUG,
        INFO
    };

    static std::string filepath = "log.txt";
    static void WriteToLog(LOG_LEVEL lvl, std::string message) {
        
    }
    static std::vector<char> GetLogContents();
}

#endif
