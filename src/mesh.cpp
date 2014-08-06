#include "mesh.hpp"

mugg::graphics::Mesh::Mesh(mugg::core::ContentManager* parent) {
    this->parent = parent;

    this->loaded = false;
    this->vaoID = -1;
    this->positionBufferID = -1;
    this->uvBufferID = -1;
    this->normalBufferID = -1;
    this->elementBufferID = -1;
    this->texture = nullptr;
}
mugg::graphics::Mesh::~Mesh() {
    this->Clear();
}

mugg::graphics::Texture2D* mugg::graphics::Mesh::GetTexture() {
    return this->texture;
}
void mugg::graphics::Mesh::SetTexture(mugg::graphics::Texture2D* texture) {
    this->texture = texture;
}

GLuint mugg::graphics::Mesh::GetVAOID() {
    return this->vaoID;
}
void mugg::graphics::Mesh::SetVAOID(GLuint vaoID) {
    this->vaoID = vaoID;
}

GLuint mugg::graphics::Mesh::GetPositionBufferID() {
    return this->positionBufferID;
}
void mugg::graphics::Mesh::SetPositionBufferID(GLuint positionBufferID) {
    this->positionBufferID = positionBufferID;
}

GLuint mugg::graphics::Mesh::GetUVBufferID() {
    return this->uvBufferID;
}
void mugg::graphics::Mesh::SetUVBufferID(GLuint uvBufferID) {
    this->uvBufferID = uvBufferID;
}

GLuint mugg::graphics::Mesh::GetNormalBufferID() {
    return this->normalBufferID;
}
void mugg::graphics::Mesh::SetNormalBufferID(GLuint normalBufferID) {
    this->normalBufferID = normalBufferID;
}

GLuint mugg::graphics::Mesh::GetElementBufferID() {
    return this->elementBufferID;
}
void mugg::graphics::Mesh::SetElementBufferID(GLuint elementBufferID) {
    this->elementBufferID = elementBufferID;
}


std::string mugg::graphics::Mesh::GetFilepath() {
    return this->filepath;
}
void mugg::graphics::Mesh::SetFilepath(const std::string& filepath) {
    this->filepath = filepath;
}

void mugg::graphics::Mesh::GenIDS() {
}

void mugg::graphics::Mesh::FillBuffers() {
}

void mugg::graphics::Mesh::SetIndices(const std::vector<unsigned short>& indices) {
    this->indices = indices;
}
int mugg::graphics::Mesh::GetNumberOfIndices() {
    return this->indices.size();
}

void mugg::graphics::Mesh::SetVertices(const std::vector<glm::vec3>& vertices) {
    this->vertices = vertices;
}
int mugg::graphics::Mesh::GetNumberOfVertices() {
    return this->vertices.size();
}

void mugg::graphics::Mesh::SetUVS(const std::vector<glm::vec2>& uvs) {
    this->uvs = uvs;
}
int mugg::graphics::Mesh::GetNumberOfUVS() {
    return this->uvs.size();
}

void mugg::graphics::Mesh::SetNormals(const std::vector<glm::vec3>& normals) {
    this->normals = normals;
}
int mugg::graphics::Mesh::GetNumberOfNormals() {
    return this->normals.size();
}


void mugg::graphics::Mesh::Clear() {
    this->indices.clear();
    this->vertices.clear();
    this->normals.clear();
    this->uvs.clear();
    
    this->loaded = false;
}
