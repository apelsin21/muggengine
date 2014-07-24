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

std::vector<std::shared_ptr<mugg::graphics::Texture2D>> mugg::graphics::Mesh::GetTextures() {
    return this->textures;
}
bool mugg::graphics::Mesh::GetTextureByIndex(int index, std::shared_ptr<mugg::graphics::Texture2D> &out_texture) {
    if(this->textures.size() != 0 && this->textures.size() <= index) {
        out_texture = this->textures[index];
        return true;
    }

    std::cout << "Tried to get texture by out of bounds index from mesh!\n";

    return false;
}
void mugg::graphics::Mesh::AddTexture(std::shared_ptr<mugg::graphics::Texture2D>& texture) {
    this->textures.push_back(texture);
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

/*
bool Load(std::string filepath) {
    this->Clear();
    this->GenIDS();
    this->loaded = false;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filepath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

    if(!scene) {
        std::cout << "Loading mesh " << filepath << " failed, error message:\n" << importer.GetErrorString();
        return false;
    }

    this->filepath = filepath;
    this->ProcessAssimpScene(scene);

    importer.FreeScene();
    this->loaded = true;
    return true;
}
*/
void mugg::graphics::Mesh::GenIDS() {
    if(glIsBuffer(this->VBOID) == GL_FALSE) {
        glGenBuffers(1, &this->VBOID);
    }
    if(glIsBuffer(this->IBID) == GL_FALSE) {
        glGenBuffers(1, &this->IBID);
    }
}

/*
void mugg::graphics::Mesh::ProcessAssimpScene(const aiScene* scene) {
    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        this->ProcessAssimpMesh(i, mesh);
    }

    this->ProcessAssimpMaterials(scene);
}
void mugg::graphics::Mesh::ProcessAssimpMaterials(const aiScene* scene) {
    for(unsigned int i = 0; i < scene->mNumMaterials; i++) {
        const aiMaterial* material = scene->mMaterials[i];
        
        if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString path;

            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string fullpath(path.data);
                this->textures.push_back(mugg::graphics::Texture2D(fullpath));
            }
        }
    }

    if(this->textures.size() == 0) {
        this->textures.push_back(mugg::graphics::Texture2D("data/textures/error.png"));
    }
}
void mugg::graphics::Mesh::ProcessAssimpMesh(unsigned int index, const aiMesh* mesh) {
    this->materialIndices.push_back(mesh->mMaterialIndex);
    
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        const aiVector3D* pos = &(mesh->mVertices[i]);
        const aiVector3D* normal = mesh->HasNormals() ? &(mesh->mNormals[i]) : &Zero3D;
        const aiVector3D* texcoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;

        this->vertices.push_back(glm::vec3(pos->x, pos->y, pos->z));
        this->uvs.push_back(glm::vec2(texcoord->x, texcoord->y));
        this->normals.push_back(glm::vec3(normal->x, normal->y, normal->z));
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace& face = mesh->mFaces[i];
        assert(face.mNumIndices == 3);
        this->indices.push_back(face.mIndices[0]);
        this->indices.push_back(face.mIndices[1]);
        this->indices.push_back(face.mIndices[2]);
    }

    this->FillBuffers();
}
*/

void mugg::graphics::Mesh::FillBuffers() {
}

int mugg::graphics::Mesh::GetNumberOfTextures() {
    return this->textures.size();
}
int mugg::graphics::Mesh::GetNumberOfVertices() {
    return this->vertices.size();
}
int mugg::graphics::Mesh::GetNumberOfIndices() {
    return this->indices.size();
}
int mugg::graphics::Mesh::GetNumberOfUVS() {
    return this->uvs.size();
}
int mugg::graphics::Mesh::GetNumberOfNormals() {
    return this->normals.size();
}


void mugg::graphics::Mesh::Clear() {
    this->textures.clear();
    this->indices.clear();
    this->vertices.clear();
    this->normals.clear();
    this->uvs.clear();
    
    if(glIsBuffer(this->VBOID) == GL_TRUE) {
        glDeleteBuffers(1, &this->VBOID);
    }
    if(glIsBuffer(this->IBID) == GL_TRUE) {
        glDeleteBuffers(1, &this->IBID);
    }
    
    this->loaded = false;
}
