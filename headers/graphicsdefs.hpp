#ifndef GRAPHICSDEFS_HPP
#define GRAPHICSDEFS_HPP

#include <GL/glew.h>

namespace mugg {
    namespace graphics {
        enum TextureFilter {            
        };
        enum ShaderType {
            VertexShader = GL_VERTEX_SHADER,
            FragmentShader = GL_FRAGMENT_SHADER,
            GeometryShader = GL_GEOMETRY_SHADER,
        }

        static const char* ShaderTypeString[] = {
            "VertexShader",
            "FragmentShader",
            "GeometryShader",
            NULL
        };
    }
}

#endif
