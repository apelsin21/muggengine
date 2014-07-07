#ifndef GRAPHICSDEFS_HPP
#define GRAPHICSDEFS_HPP

#include <GL/glew.h>

namespace mugg {
    namespace graphics {
        enum TextureFilter {            
            Nearest,
            Linear,
        };
        static const char* TextureFilterString[] = {
            "Nearest",
            "Linear",
            NULL
        };

        enum TextureRepeatPattern {
            Repeat,
        };
        static const char* TextureRepeatPatternString[] = {
            "Repeat",
            NULL
        };

        enum ShaderType {
            VertexShader,
            FragmentShader,
            GeometryShader,
        };
        static const char* ShaderTypeString[] = {
            "VertexShader",
            "FragmentShader",
            "GeometryShader",
            NULL
        };
    }
}

#endif
