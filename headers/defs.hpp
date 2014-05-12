#ifndef DEFS_HPP
#define DEFS_HPP

#define DefaultGLMajorVersion 3
#define DefaultGLMinorVersion 0
#define UseCoreProfileByDefault false
#define DefaultWindowTitle "MuggEngine Window"
#define DefaultWindowWidth 800
#define DefaultWindowHeight 600

namespace mugg {
	enum ShaderType {
	    VERTEX_SHADER,
	    FRAGMENT_SHADER,
	    GEOMETRY_SHADER,
        TESSELATION_SHADER,
        COMPUTE_SHADER,
	};

    enum LogLevel {
    	FATAL_ERROR,
    	ERROR,
   		WARNING,
   		DEBUG,
  		INFO,
    };

    enum ContextFlags {
        COLOR_BUFFER_BIT,
        DEPTH_BUFFER_BIT,
        BLEND,
        ALPHA_TEST,
        AUTO_NORMAL,
        COLOR_MATERIAL,
        CULL_FACE,
        DITHER,
        FOG,
        LIGHT,
        LINE_SMOOTH,
        LIGHTING,
        NORMALIZE,
        MULTISAMPLE,
        MINMAX,
        TEXTURE_2D,
        TEXTURE_3D,
        TEXTURE_CUBE_MAP,
    };
}
#endif
