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

    static std::string logfilepath = "log.txt";
    static void WriteToLog(LOG_LEVEL lvl, std::string message) {
        std::ofstream stream(mugg::logfilepath.c_str(), std::ios::out | std::ios::app);
        std::string error_msg;
        
        switch(lvl) {
            case FATAL_ERROR:
                error_msg = "\nFatal error: ";
                break;
            case ERROR:
                 error_msg = "\nError: ";
                break;
            case WARNING:
                error_msg = "\nWarning: ";
                break;
            case DEBUG:
                error_msg = "\nDebug: ";
                break;
            case INFO:
                error_msg = "\nInfo: ";
                break;
            default:
                error_msg = "\n";
                break;
        }
        
        message.insert(0, error_msg);
        
        if(stream.is_open()) {
            for(int i = 0; i <= message.length(); i++) {
                stream.put(message[i]);
            }
        }
    }
    static std::vector<char> GetLogContents();
}



#endif
