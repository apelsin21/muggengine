#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
#include <ctime>

#include "filehandler.hpp"
#include "defs.hpp"

namespace mugg {
    static mugg::LogLevel MIN_LEVEL_TO_PRINT = WARNING;
    static std::string logfilepath = "log.txt";
    static void WriteToLog(mugg::LogLevel lvl, std::string message) {
        std::ofstream stream(mugg::logfilepath.c_str(), std::ios::out | std::ios::app);
        
        std::time_t now = std::time(0);
        std::string dt = ctime(&now);
        message.insert(0, dt);

        switch(lvl) {
            case mugg::FATAL_ERROR:
                message.insert(0, "Fatal error: ");
                break;
            case mugg::ERROR:
                message.insert(0, "Error: ");
                break;
            case mugg::WARNING:
                message.insert(0, "Warning: ");
                break;
            case mugg::DEBUG:
                message.insert(0, "Debug: ");
                break;
            case mugg::INFO:
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
