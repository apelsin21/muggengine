#include "scenemanager.hpp"

mugg::scene::SceneManager::SceneManager(mugg::core::Engine* parent) {
    this->parent = parent;
    this->programID = -1;
}
mugg::scene::SceneManager::~SceneManager() {
    for(unsigned int i = 0; i < this->sceneNodes.size(); i++) {
        if(this->sceneNodes[i] != nullptr) {
            delete this->sceneNodes[i];
        }
    }
}

mugg::scene::SceneNode* mugg::scene::SceneManager::CreateSceneNode() {
    mugg::scene::SceneNode* node = new mugg::scene::SceneNode(this);

    this->sceneNodes.push_back(node);

    return node;
}
std::size_t mugg::scene::SceneManager::GetNumberOfSceneNodes() {
    return this->sceneNodes.size();
}
bool mugg::scene::SceneManager::GetSceneNodeByIndex(int index, mugg::scene::SceneNode*& out_node) {
    if(index < 0 || index >= this->sceneNodes.size() || this->sceneNodes.empty()) {
        std::cout << "Tried to get scenenode from scenemanager, with out of bounds index!\n";
        return false;
    }

    out_node = this->sceneNodes[index];
    return true;
}

void mugg::scene::SceneManager::SetShaderProgramID(GLuint id) {
    this->programID = id;
}
GLuint mugg::scene::SceneManager::GetShaderProgramID() {
    return this->programID;
}

//TODO:PLACEHOLDER
void mugg::scene::SceneManager::Render() {
    if(!this->sceneNodes.empty() && glIsProgram(this->programID) == GL_TRUE) {
        for(unsigned int i= 0; i < this->sceneNodes.size(); i++) {
            for(unsigned int u = 0; u < this->sceneNodes[i]->GetNumberOfMeshes(); u++) {
                mugg::graphics::Mesh* mesh = nullptr;
                
                if(!this->sceneNodes[i]->GetMeshByIndex(u, mesh)) {
                    std::cout << "FAILED TO GET MESH BY INDEX\n";
                }
                
                if(mesh == nullptr) {
                    std::cout << "We got a mesh but it's still a pointer to nothing\n";
                }

                glUseProgram(this->programID);

                GLint modelMatrixLocation = glGetUniformLocation(this->programID, "v_model");
                GLint projectionMatrixLocation = glGetUniformLocation(this->programID, "v_projection");

                glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->sceneNodes[i]->GetPosition().x, this->sceneNodes[i]->GetPosition().y, this->sceneNodes[i]->GetPosition().z));
                glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

                glm::mat4 projectionMatrix = glm::perspective(3.1415f / 2.0f, 4.0f / 3.0f, 0.001f, 100000.0f);
                glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
                
                glBindVertexArray(mesh->GetVAOID());

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(2);
                glEnableVertexAttribArray(1);
                
                glBindBuffer(GL_ARRAY_BUFFER, mesh->GetPositionBufferID());
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                
                glBindBuffer(GL_ARRAY_BUFFER, mesh->GetUVBufferID());
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
                
                glBindBuffer(GL_ARRAY_BUFFER, mesh->GetNormalBufferID());
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                
                if(mesh->GetTexture() != nullptr && glIsTexture(mesh->GetTexture()->GetID()) == GL_TRUE) {
                    glBindTexture(GL_TEXTURE_2D, mesh->GetTexture()->GetID());
                }

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->GetElementBufferID());
                glDrawElements(GL_TRIANGLES, mesh->GetNumberOfIndices(), GL_UNSIGNED_SHORT, nullptr);

                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
                glDisableVertexAttribArray(2);
            }
        }
    }
}
