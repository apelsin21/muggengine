#include "context.hpp"

mugg::Context::Context() {
    this->majorVersion = DefaultGLMajorVersion;
    this->minorVersion = DefaultGLMinorVersion;
    this->usesCoreProfile = UseCoreProfileByDefault;
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
