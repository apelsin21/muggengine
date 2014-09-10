#include "shaderprogram.hpp"

mugg::graphics::ShaderProgram::ShaderProgram(bool createID = true) : GLObject(nullptr) {
    this->linked = false;
    this->compiledSuccessfully = false;

    if(createID)
        this->CreateID();
}
mugg::graphics::ShaderProgram::ShaderProgram(mugg::core::ContentManager* creator) : GLObject(creator) {
    this->linked = false;
    this->compiledSuccessfully = false;
}

mugg::graphics::ShaderProgram::~ShaderProgram() {
}

void mugg::graphics::ShaderProgram::CreateID() {
    this->ID = glCreateProgram();
    this->hasGeneratedID = true;
}
void mugg::graphics::ShaderProgram::DeleteID() {
    if(glIsProgram(this->ID) == GL_TRUE) {
        for(unsigned int i = 0; i < this->shaders.size(); i++) {
            glDetachShader(this->ID, this->shaders[i]);
        }
        
        this->hasGeneratedID = false;
        glDeleteProgram(this->ID);
    } else {
        std::cout << "Tried to delete invalid shaderprogram: " << this->ID << std::endl;
    }
}

bool mugg::graphics::ShaderProgram::AttachShader(mugg::graphics::Shader* shader) {
    if(glIsShader(shader->GetID()) == GL_FALSE) {
        std::cout << "Tried adding an unvalid shader to shaderprogram!\n";
        return false;
    }

    glAttachShader(this->ID, shader->GetID());

    this->shaders.push_back(shader->GetID());

    return true;
}

bool mugg::graphics::ShaderProgram::Link() {
    if(this->GetNumberOfAttachedShaders() <= 0) {
        std::cout << "Tried to link shaderprogram without attaching any shaders!\n";
        return false;
    }

    glLinkProgram(this->ID);
    this->CheckForErrors();

    for(unsigned int i = 0; i < this->shaders.size(); i++) {
        glDetachShader(this->ID, this->shaders[i]);
    }

    if(!this->compiledSuccessfully) {
        this->linked = false;
        std::cout << this->GetLog() << std::endl;
        return false;
    }

    this->compiledSuccessfully = true;
    this->linked = true;

    return true;
}

void mugg::graphics::ShaderProgram::CheckForErrors() {
    GLint result = GL_FALSE;

    glGetProgramiv(this->ID, GL_LINK_STATUS, &result);

    if(result == GL_FALSE) {
        this->compiledSuccessfully = false;
    }

    this->compiledSuccessfully = true;
}

const char* mugg::graphics::ShaderProgram::GetLog() {
    int logLength = 0;
    glGetProgramiv(this->ID, GL_INFO_LOG_LENGTH, &logLength);
    
    GLchar buffer[logLength];
    glGetProgramInfoLog(this->ID, logLength, NULL, buffer);

    std::string returnval;

    for(unsigned int i = 0; i <= logLength; i++) {
        returnval += buffer[i];
    }

    return returnval.c_str();
}

bool mugg::graphics::ShaderProgram::Validate() {
    if(glIsProgram(this->ID) != GL_TRUE) {
        return false;
    }
    
    int result = GL_FALSE;

    glValidateProgram(this->ID);

    glGetProgramiv(this->ID, GL_VALIDATE_STATUS, &result);

    if(result == GL_FALSE) {
        std::cout << "Validation log: " << this->GetLog() << std::endl;

        return false;
    }

    return true;
}

bool mugg::graphics::ShaderProgram::GetCompiledSuccessfully() {
    return this->compiledSuccessfully;
}

bool mugg::graphics::ShaderProgram::AddAttrib(const std::string& name) {
    if(glIsProgram(this->ID) == GL_FALSE) {
        std::cout << "Tried to add attribute to invalid shader program!\n";
        return false;
    }
    
    GLint attribLocation = glGetAttribLocation(this->ID, name.c_str());

    if(attribLocation == -1) {
        std::cout << "Invalid attribute: " << name << " in shaderprogram " << this->ID << std::endl;
        return false;
    }

    this->knownLocations[name] = attribLocation;

    return true;
}
GLint mugg::graphics::ShaderProgram::GetAttrib(const std::string& name) {
    auto it = this->knownLocations.find(name);

    if(it != this->knownLocations.end()) {
        //Search success
        return it->second;
    }

    //Search failed
    return -1;
}

bool mugg::graphics::ShaderProgram::AddUniform(const std::string& name) {
    if(glIsProgram(this->ID) == GL_FALSE) {
        std::cout << "Tried to add attribute to invalid shader program!\n";
        return false;
    }
    
    GLint uniformLocation = glGetUniformLocation(this->ID, name.c_str());

    if(uniformLocation == -1) {
        std::cout << "Invalid uniform: " << name << " in shaderprogram " << this->ID << std::endl;
        return false;
    }

    this->knownLocations[name] = uniformLocation;

    return true;
}
GLint mugg::graphics::ShaderProgram::GetUniform(const std::string& name) {
    auto it = this->knownLocations.find(name);

    if(it != this->knownLocations.end()) {
        //It was found
        return it->second;
    }

    //Search failed
    return -1;
}

GLint mugg::graphics::ShaderProgram::GetNumberOfAttachedShaders() {
    GLint numberOfShaders = 0;

    glGetProgramiv(this->ID, GL_ATTACHED_SHADERS, &numberOfShaders);

    return numberOfShaders;
}

void mugg::graphics::ShaderProgram::Use() {
    if(glIsProgram(this->ID)) {
        glUseProgram(this->ID);
    }
}
