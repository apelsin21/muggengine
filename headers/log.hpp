#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string>
#include <ctime>

#include <GL/glew.h>

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
    
    static void glCheckError(const char* file, unsigned int line) {
        GLenum err = glGetError();
        std::string err_msg = "";
        err_msg += file;
        err_msg += line;

        if(err != GL_NO_ERROR) {
        	switch (err) {
            	case GL_INVALID_ENUM: {
                    err_msg = "GL_INVALID_ENUM";
                    err_msg +="\nan unacceptable value has been specified for an enumerated argument";
                    break;
                }
                case GL_INVALID_VALUE: {
                    err_msg = "GL_INVALID_VALUE";
                    err_msg += "\na numeric argument is out of range";
                    break;
                }
                case GL_INVALID_OPERATION: {
                    err_msg = "GL_INVALID_OPERATION";
                    err_msg += "\nthe specified operation is not allowed in the current state";
                    break;
                }
                case GL_STACK_OVERFLOW: {
                    err_msg = "GL_STACK_OVERFLOW";
                    err_msg += "\nthis command would cause a stack overflow";
                    break;
                }
                case GL_STACK_UNDERFLOW: {
                    err_msg = "GL_STACK_UNDERFLOW";
                    err_msg += "\nthis command would cause a stack underflow";
                    break;
                }
                case GL_OUT_OF_MEMORY: {
                    err_msg = "GL_OUT_OF_MEMORY";
                    err_msg += "\nthere is not enough memory left to execute the command";
                    break;
                }
                case GL_INVALID_FRAMEBUFFER_OPERATION: {
                    err_msg = "GL_INVALID_FRAMEBUFFER_OPERATION";
                    err_msg += "\nthe object bound to FRAMEBUFFER_BINDING is not \"framebuffer complete\"";
                    break;
                }
            }
            mugg::WriteToLog(mugg::ERROR, err_msg);
        }
    }
}



#endif
