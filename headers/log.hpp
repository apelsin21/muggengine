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
                error_msg = "Fatal error: ";
                break;
            case ERROR:
                 error_msg = "Error: ";
                break;
            case WARNING:
                error_msg = "Warning: ";
                break;
            case DEBUG:
                error_msg = "Debug: ";
                break;
            case INFO:
                error_msg = "Info: ";
                break;
            default:
                error_msg = "";
                break;
        }
        
        message.insert(0, error_msg);
        
        if(stream.is_open()) {
            int position = stream.tellp();
            if(position > 0) {
                message.insert(0, "\n");
            }

            for(int i = 0; i <= message.length() - 1; i++) {
                stream.put(message[i]);
            }
        }
    }
    static std::vector<char> GetLogContents();
}



#endif
