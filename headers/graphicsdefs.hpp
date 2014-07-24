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
        static GLenum TextureFilterToGLEnum(TextureFilter filter) {
            switch(filter) {
                case Nearest:
                    return GL_NEAREST;
                case Linear:
                    return GL_LINEAR;
                default:
                    return 0;
            }
        }

        enum TextureWrap {
            Repeat,
            ClampToEdge
        };
        static const char* TextureWrapString[] = {
            "Repeat",
            "ClampToEdge",
            NULL
        };
        static GLenum TextureWrapToGLEnum(TextureWrap wrap) {
            switch(wrap) {
                case Repeat:
                    return GL_REPEAT;
                case ClampToEdge:
                    return GL_CLAMP_TO_EDGE;
                default:
                    return 0;
            }
        }

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
        static GLenum ShaderTypeToGLEnum(ShaderType type) {
            switch(type) {
                case VertexShader:
                    return GL_VERTEX_SHADER;
                case FragmentShader:
                    return GL_FRAGMENT_SHADER;
                case GeometryShader:
                    return GL_GEOMETRY_SHADER;
                default:
                    return 0;
            }
        }
    }
}

#endif
