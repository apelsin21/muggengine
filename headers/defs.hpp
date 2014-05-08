#ifndef DEFS_HPP
#define DEFS_HPP

#define DefaultGLMajorVersion 3
#define DefaultGLMinorVersion 0
#define UseCoreProfileByDefault false

namespace mugg {
	enum ShaderType {
	    VERTEX_SHADER,
	    FRAGMENT_SHADER,
	    GEOMETRY_SHADER,
        TESSELATION_SHADER,
        COMPUTE_SHADER
	};

    enum LogLevel {
    	FATAL_ERROR,
    	ERROR,
   		WARNING,
   		DEBUG, 
  		INFO
    };
}
#endif
