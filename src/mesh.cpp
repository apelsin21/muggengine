#include "mesh.hpp"

mugg::graphics::Mesh::Mesh() {
    this->loaded = false;
    this->VBOID = 0;
    this->IBID = 0;
    this->numberOfIndices = 0;

    this->GenIDS();
}
mugg::graphics::Mesh::~Mesh() {
    this->Clear();
}

std::vector<mugg::graphics::Texture2D> mugg::graphics::Mesh::GetDiffuseTextures() {
    return this->diffuseTextures;
}
bool mugg::graphics::Mesh::GetDiffuseTextureByIndex(int index, mugg::graphics::Texture2D &out_texture) {
    if(this->diffuseTextures.size() != 0 && this->diffuseTextures.size() <= index) {
        out_texture = this->diffuseTextures[index];
        return true;
    }

    std::cout << "Tried to get texture by out of bounds index from mesh!\n";

    return false;
}
void mugg::graphics::Mesh::AddDiffuseTexture(mugg::graphics::Texture2D texture) {
    this->diffuseTextures.push_back(texture);
}

GLuint mugg::graphics::Mesh::GetVBOID() {
    return this->VBOID;
}
void mugg::graphics::Mesh::SetVBOID(GLuint VBOID) {
    this->VBOID = VBOID;
}

GLuint mugg::graphics::Mesh::GetIBID() {
    return this->IBID;
}
void mugg::graphics::Mesh::SetIBID(GLuint IBID) {
    this->IBID = IBID;
}

std::string mugg::graphics::Mesh::GetFilepath() {
    return this->filepath;
}

bool mugg::graphics::Mesh::Load(std::string filepath) {
    this->Clear();
    this->GenIDS();

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filepath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

    if(!scene) {
        std::cout << "Mesh loading failed, Assimp error:\n" << importer.GetErrorString();
        return false;
    }

    this->ProcessAssimpScene(scene);

    this->loaded = true;
    this->filepath = filepath;
    return true;
}

void mugg::graphics::Mesh::GenIDS() {
    glGenBuffers(1, &this->VBOID);
    glGenBuffers(1, &this->IBID);
}

void mugg::graphics::Mesh::ProcessAssimpScene(const aiScene* scene) {
    //TODO Add diffuse textures, specular textures and normal textures
    //TODO Add vertices, uv coordinates and materials
    //TODO Fill VBO and IBO with vertices and indices
}

void mugg::graphics::Mesh::Clear() {
    if(this->loaded) {
        this->diffuseTextures.clear();
        this->normalTextures.clear();
        this->specularTextures.clear();
        this->vertices.clear();
        this->uvs.clear();
        this->colors.clear();

        if(glIsBuffer(this->VBOID) == GL_TRUE) {
            glDeleteBuffers(1, &this->VBOID);
        }
    
        this->loaded = false;
    }
}
