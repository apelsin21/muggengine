#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <GL/glew.h>

#include "defs.hpp"

namespace mugg {
    class Context {
    private:
        GLuint majorVersion, minorVersion;
        bool usesCoreProfile;
    public:
        Context();
        ~Context();

        void SetMajorVersion(GLuint majorVersion);
        GLuint GetMajorVersion();

        void SetMinorVersion(GLuint minorVersion);
        GLuint GetMinorVersion();

        void UseCoreProfile(bool useCoreProfile);
        bool GetUsesCoreProfile();

        void Enable();
    };
}

#endif
