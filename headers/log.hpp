#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
#include <ctime>

#include "filehandler.hpp"

namespace mugg {
    enum LOG_LEVEL {
        FATAL_ERROR,
        ERROR,
        WARNING,
        DEBUG,
        INFO
    };

    static LOG_LEVEL MIN_LEVEL_TO_PRINT = WARNING;
    static std::string logfilepath = "log.txt";
    static void WriteToLog(LOG_LEVEL lvl, std::string message) {
        std::ofstream stream(mugg::logfilepath.c_str(), std::ios::out | std::ios::app);
        
        std::time_t now = std::time(0);
        std::string dt = ctime(&now);
        message.insert(0, dt);

        switch(lvl) {
            case FATAL_ERROR:
                message.insert(0, "Fatal error: ");
                break;
            case ERROR:
                message.insert(0, "Error: ");
                break;
            case WARNING:
                message.insert(0, "Warning: ");
                break;
            case DEBUG:
                message.insert(0, "Debug: ");
                break;
            case INFO:
                message.insert(0, "Info: ");
                break;
            default:
                break;
        }
        
        if(lvl <= mugg::MIN_LEVEL_TO_PRINT) {
            std::cout << message << std::endl;
        }

        if(stream.is_open()) {
            if(stream.tellp() > 0)
                message.insert(0, "\n");
            
            for(unsigned int i = 0; i <= message.length() - 1; i++)
                stream.put(message[i]);
        }

        stream.close();
    }
    static std::vector<char> GetLogContents();
}



#endif
