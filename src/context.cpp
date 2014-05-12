#include "context.hpp"

mugg::Context::Context() {
    this->majorVersion = DefaultGLMajorVersion;
    this->minorVersion = DefaultGLMinorVersion;
    this->usesCoreProfile = UseCoreProfileByDefault;
    this->enabled = false;
}

mugg::Context::~Context() {
}

void mugg::Context::SetMajorVersion(GLuint majorVersion) {
    this->majorVersion = majorVersion;
}
GLuint mugg::Context::GetMajorVersion() {
    return this->majorVersion;
}

void mugg::Context::SetMinorVersion(GLuint minorVersion) {
    this->minorVersion = minorVersion;
}
GLuint mugg::Context::GetMinorVersion() {
    return this->minorVersion;
}

void mugg::Context::UseCoreProfile(bool useCoreProfile) {
    this->usesCoreProfile = useCoreProfile;
}
bool mugg::Context::GetUsesCoreProfile() {
    return this->usesCoreProfile;
}

bool mugg::Context::Enable() {
    if(this->enabled) {
        mugg::WriteToLog(mugg::INFO, "Recreating context");
    }

    if(this->flags.size() <= 0) {
        mugg::WriteToLog(mugg::WARNING, "Tried to enable empty context");
        return false;
    }

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        std::string error_msg("GLEW failed to initialize! GLEW error string:\n");
        error_msg += (const char*)glewGetErrorString(err);

        mugg::WriteToLog(mugg::FATAL_ERROR, error_msg);
        return false;
    }

    for(unsigned int i = 0; i <= this->flags.size(); i++) {
        switch(this->flags[i]) {
        case mugg::COLOR_BUFFER_BIT:
            glEnable(GL_COLOR_BUFFER_BIT);
            break;
        case mugg::DEPTH_BUFFER_BIT:
            glEnable(DEPTH_BUFFER_BIT);
            break;
        default:
            break;
        }
    }

    this->enabled = true;
    return true;
}

std::vector<mugg::ContextFlags> mugg::Context::GetFlags() {
    return this->flags;
}

void mugg::Context::AddFlag(mugg::ContextFlags flag) {
    this->flags.push_back(flag);
}

bool mugg::Context::GetIsEnabled() {
    return this->enabled;
}
