#include "file.hpp"

void mugg::File::SetFilepath(std::string filepath) {
    this->filepath = filepath;
}
std::string mugg::File::GetFilepath() {
    return this->filepath;
}

std::size_t mugg::File::GetSize() {
    return this->data.size();
}

void mugg::File::SetData(std::string data) {
    this->data = data;
}
std::string mugg::File::GetData() {
    return this->data;
}
