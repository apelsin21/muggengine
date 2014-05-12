#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <vector>

#include <GL/glew.h>

#include "defs.hpp"
#include "log.hpp"

namespace mugg {
    class Context {
    private:
        GLuint majorVersion, minorVersion;
        bool usesCoreProfile, enabled;
        std::vector<mugg::ContextFlags> flags;
    public:
        Context();
        ~Context();

        std::vector<mugg::ContextFlags> GetFlags();

        void SetMajorVersion(GLuint majorVersion);
        GLuint GetMajorVersion();

        void SetMinorVersion(GLuint minorVersion);
        GLuint GetMinorVersion();

        void UseCoreProfile(bool useCoreProfile);
        bool GetUsesCoreProfile();

        bool Enable();
        bool GetIsEnabled();
    };
}

#endif
